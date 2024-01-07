/////////////////////////////////////////////////////////////////////////////
// Name:        BeremizProjectManagerApp.cpp
// Purpose:     wxWidget main application class for Beremiz Project Manager
// Author:      Benoit BOUCHEZ
// Created:     12/08/2020
/////////////////////////////////////////////////////////////////////////////

/*
* MIT License
*
* Copyright(c) 2020 - 2024 Benoit BOUCHEZ
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
Release note :
V 0.1 : First release on Google Drive for MERG

14/11/2022 - V0.2.0
	- Added warning messages in TargetPluginClass::LoadPlugin when a DLL function is not found, to help debugging

17/11/2022 - V0.2.1
	- Bug corrected : Browse button in Options / General was not working

02/01/2024 - V0.3.0
	- Update to wxWidgets 3.2.4
	- Update to VS2017
	- Update to MIT license BEB SDK
	- Switch to winsock2 library on Windows platform
*/

#include "BeremizProjectManagerApp.h"
#include "BeremizProjectManagerMainFrame.h"
#include "network.h"

// 'Main program' equivalent: the program execution "starts" here
bool CBeremizProjectManagerApp::OnInit()
{
	wxInitAllImageHandlers();

#ifdef __TARGET_WIN__
	if (OpenNetwork()==false)
	{
		wxMessageBox ("Can not open Winsock layer!\nNo communication with remote target will be possible", "System error", wxOK+wxICON_ERROR);
	}
#endif

    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    CBeremizProjectManagerMainFrame *frame = new CBeremizProjectManagerMainFrame(0);
    frame->Show(true);

    return true;   // Returning false abort immediately application
}  // CBeremizProjectManagerApp::OnInit
// -----------------------------------------------------------

int CBeremizProjectManagerApp::OnExit()
{
#ifdef __TARGET_WIN__
	CloseNetwork();
#endif

    wxApp::OnExit();
    return 0;
}  // CBeremizProjectManagerApp::OnExit
// -----------------------------------------------------------
