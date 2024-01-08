/////////////////////////////////////////////////////////////////////////////
// Name:        RPi_CBUS_PLC_DLLMain.cpp
// Purpose:     Plugin for Beremiz Project Manager for MERG CBUS PLC on Raspberry Pi
// This file provides the support for wxWidgets based Target Plugin
// Author:      Benoit BOUCHEZ
// Created:     12/05/2022
/////////////////////////////////////////////////////////////////////////////

/*
* MIT License
*
* Copyright(c) 2022 - 2024 Benoit BOUCHEZ
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*/

/*
Release notes
0.1.0.0 : First release on Google Drive for MERG

0.2.0.0 - 13/11/2022 :
	- changed TP_GetCompilerMessages export to EXPORT_INTERFACE (was EXPORT_DYNAMIC_LIB)

0.3.0.0 - 02/01/2024
	- Update to wxWidgets 3.2.4
	- Update to VS2017
	- Update to MIT license BEB SDK
	- Switch to winsock2 library
*/

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wx/app.h"
#include "wx/dynlib.h"
#include "wx/thread.h"
#include <wx/stdpaths.h>

#ifdef __TARGET_WIN__
#include <process.h> // for _beginthreadex()
#include "wx/msw/wrapwin.h"
#endif  // __TARGET_WIN__

#include "RPi_CBUS_PLC_DLLMain.h"
#include "CBUSPLC_IOEdit.h"

extern "C"
{
int CMD_SHOW_WINDOW = wxNewId();
int CMD_HIDE_WINDOW = wxNewId();
int CMD_TERMINATE = wxNewId();
}

class MyDllApp : public wxApp
{
public:
    MyDllApp();

private:
    void OnShowWindow(wxThreadEvent& event);
	void OnHideWindow(wxThreadEvent& event);
    void OnTerminate(wxThreadEvent& event);
};

extern CBUSPLC_IOEditFrame* Editor;
extern "C" void OpenEditor (uint32_t EditorIndex);
extern "C" void CloseEditor (int32_t EditorIndex);
extern CSupervisorCommunicator* Supervisor;

MyDllApp::MyDllApp()
{
    // Keep the wx "main" thread running even without windows. This greatly
    // simplifies threads handling, because we don't have to correctly
    // implement wx-thread restarting.
    //
    // Note that this only works if you don't explicitly call ExitMainLoop(),
    // except in reaction to wx_dll_cleanup()'s message. wx_dll_cleanup()
    // relies on the availability of wxApp instance and if the event loop
    // terminated, wxEntry() would return and wxApp instance would be
    // destroyed.
    //
    // Also note that this is efficient, because if there are no windows, the
    // thread will sleep waiting for a new event. We could safe some memory
    // by shutting the thread down when it's no longer needed, though.
    SetExitOnFrameDelete(false);

    Bind(wxEVT_THREAD, &MyDllApp::OnShowWindow, this, CMD_SHOW_WINDOW);
	Bind(wxEVT_THREAD, &MyDllApp::OnHideWindow, this, CMD_HIDE_WINDOW);
    Bind(wxEVT_THREAD, &MyDllApp::OnTerminate, this, CMD_TERMINATE);
}

void MyDllApp::OnShowWindow(wxThreadEvent& event)
{
	int EditorIndex = event.GetInt();

	OpenEditor (EditorIndex);
}

void MyDllApp::OnHideWindow(wxThreadEvent& event)
{
	int EditorIndex = event.GetInt();

	CloseEditor (EditorIndex);
}

void MyDllApp::OnTerminate(wxThreadEvent& WXUNUSED(event))
{
    ExitMainLoop();
}

// we can't have WinMain() in a DLL and want to start the app ourselves
#ifdef __TARGET_WIN__
wxIMPLEMENT_APP_NO_MAIN(MyDllApp);

namespace
{

// Critical section that guards everything related to wxWidgets "main" thread
// startup or shutdown.
wxCriticalSection gs_wxStartupCS;
// Handle of wx "main" thread if running, NULL otherwise
HANDLE gs_wxMainThread = NULL;


//  wx application startup code -- runs from its own thread
unsigned wxSTDCALL MyAppLauncher(void* event)
{
    // Note: The thread that called run_wx_gui_from_dll() holds gs_wxStartupCS
    //       at this point and won't release it until we signal it.

    // We need to pass correct HINSTANCE to wxEntry() and the right value is
    // HINSTANCE of this DLL, not of the main .exe, use this MSW-specific wx
    // function to get it. Notice that under Windows XP and later the name is
    // not needed/used as we retrieve the DLL handle from an address inside it
    // but you do need to use the correct name for this code to work with older
    // systems as well.
    const HINSTANCE
        hInstance = wxDynamicLibrary::MSWGetModuleHandle("RPi_CBUS_PLC",
                                                         &gs_wxMainThread);
    if ( !hInstance )
        return 0; // failed to get DLL's handle

    // wxIMPLEMENT_WXWIN_MAIN does this as the first thing
    wxDISABLE_DEBUG_SUPPORT();

    // We do this before wxEntry() explicitly, even though wxEntry() would
    // do it too, so that we know when wx is initialized and can signal
    // run_wx_gui_from_dll() about it *before* starting the event loop.
    wxInitializer wxinit;
    if ( !wxinit.IsOk() )
        return 0; // failed to init wx

    // Signal TP_OpenEditor() that it can continue
    HANDLE hEvent = *(static_cast<HANDLE*>(event));
    if ( !SetEvent(hEvent) )
        return 0; // failed setting up the mutex

    // Run the app:
    wxEntry(hInstance);

    return 1;
}

} // anonymous namespace
#endif  // __TARGET_WIN__

extern "C"
{
void EXPORT_INTERFACE TP_Initialize(void)
{
	// Create supervisor communication object
	Supervisor = new CSupervisorCommunicator();

#ifdef __TARGET_WIN__
	// In order to prevent conflicts with hosting app's event loop, we
    // launch wx app from the DLL in its own thread.
    //
    // We can't even use wxInitializer: it initializes wxModules and one of
    // the modules it handles is wxThread's private module that remembers
    // ID of the main thread. But we need to fool wxWidgets into thinking that
    // the thread we are about to create now is the main thread, not the one
    // from which this function is called.
    //
    // Note that we cannot use wxThread here, because the wx library wasn't
    // initialized yet. wxCriticalSection is safe to use, though.

	wxCriticalSectionLocker lock(gs_wxStartupCS);

    if ( !gs_wxMainThread )
    {
        HANDLE hEvent = CreateEvent
                        (
                            NULL,  // default security attributes
                            FALSE, // auto-reset
                            FALSE, // initially non-signaled
                            NULL   // anonymous
                        );
        if ( !hEvent )
            return; // error

        // NB: If your compiler doesn't have _beginthreadex(), use CreateThread()
        gs_wxMainThread = (HANDLE)_beginthreadex
                                  (
                                      NULL,           // default security
                                      0,              // default stack size
                                      &MyAppLauncher,
                                      &hEvent,        // arguments
                                      0,              // create running
                                      NULL
                                  );

        if ( !gs_wxMainThread )
        {
            CloseHandle(hEvent);
            return; // error
        }

        // Wait until MyAppLauncher signals us that wx was initialized. This
        // is because we use wxMessageQueue<> and wxString later and so must
        // be sure that they are in working state.
        WaitForSingleObject(hEvent, INFINITE);
        CloseHandle(hEvent);
    }
#endif  // __TARGET_WIN__
#ifdef __TARGET_LINUX__
	wxInitialize();
#endif  // __TARGET_LINUX__
}  // TP_Initialize
// -----------------------------------------------------

void EXPORT_INTERFACE TP_Terminate(void)
{
	if (Supervisor)
	{
		delete Supervisor;
		Supervisor = 0;
	}

#ifdef __TARGET_WIN__
    wxCriticalSectionLocker lock(gs_wxStartupCS);

    if ( !gs_wxMainThread )
        return;

    // If wx main thread is running, we need to stop it. To accomplish this,
    // send a message telling it to terminate the app.
    wxThreadEvent *event =
        new wxThreadEvent(wxEVT_THREAD, CMD_TERMINATE);
    wxQueueEvent(wxApp::GetInstance(), event);

    // We must then wait for the thread to actually terminate.
    WaitForSingleObject(gs_wxMainThread, INFINITE);
    CloseHandle(gs_wxMainThread);
    gs_wxMainThread = NULL;
#endif  // __TARGET_WIN__
#ifdef __TARGET_LINUX__
	CloseEditor (-1);
	wxUninitialize ();
#endif  // __TARGET_LINUX__
}  // TP_Terminate
// -----------------------------------------------------

} // extern "C"
