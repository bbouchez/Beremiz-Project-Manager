/////////////////////////////////////////////////////////////////////////////
// Name:        PixtendV2_Plugin.cpp
// Purpose:     Exposed DLL functions
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

#include "BeremizProjectManager_TargetsAPI.h"
#include "PixtendV2_DLLMain.h"
#include "Pixtend_IOEdit.h"
#include "SupervisorComm.h"

#include <wx/xml/xml.h>
#include <wx/dir.h>

extern "C" int CMD_SHOW_WINDOW;
extern "C" int CMD_HIDE_WINDOW;

wxString RemoteLogin = "";			// SSH login on RPi (from project file since all targets are not remote)
wxString RemotePassword = "";		// SSH password on RPi (from project file)
wxString RemoteTarget = "";			// IP address or hostname of Raspberry (from project file)
wxString RemotePath = "";			// Path on target where PLC source files are copied (from project file)
wxString WinSCPLocation = "";
bool HoldSCPTransfer=false;

static wxString ProjectPath;			// Folder where project is stored on local machine
static wxString TargetsDirectory;			// Folder where target source files are stored

bool DataHasChanged = false;
PixtendV2_IOEditFrame* Editor=0;
CSupervisorCommunicator* Supervisor=0;		// Static instance, so constructor and destructor are called automatically

static void CleanConfiguration (void)
{

}  // CleanConfiguration
// -----------------------------------------------------

extern "C"
{

void __cdecl TP_GetPluginName (char* Name)
{
	strcpy (Name, "PiXtend V2-L / V2-S");
}  // TP_GetPluginName
// -----------------------------------------------------

void __cdecl TP_GetPluginVersion (uint32_t* Major, uint32_t* Minor, uint32_t* Build, uint32_t* Revision)
{
	*Major = 0;
	*Minor = 3;
	*Build = 0;
	*Revision = 0;
}  // TP_GetPluginVersion
// -----------------------------------------------------

void __cdecl TP_SetProjectPath (char* Path, int32_t StrEncoding)
{
	switch (StrEncoding)
	{
		case STRING_ENCODING_C : ProjectPath = Path; break;			// wxWidgets 3.x allows direct conversion from C to wxString
		case STRING_ENCODING_UTF8 : ProjectPath = wxString::FromUTF8 (Path); break;
	}
}  // TP_SetProjectPath
// -----------------------------------------------------

void __cdecl TP_SetTargetsPath (char* Path, int32_t StrEncoding)
{
	switch (StrEncoding)
	{
		case STRING_ENCODING_C : TargetsDirectory = Path; break;			// wxWidgets 3.x allows direct conversion from C to wxString
		case STRING_ENCODING_UTF8 : TargetsDirectory = wxString::FromUTF8 (Path); break;
	}
}  // TP_SetTargetsPath
// -----------------------------------------------------

int32_t __cdecl TP_LoadTargetProjectData (void)
{
	wxXmlDocument doc;
	wxXmlNode* RootNode;
	wxXmlNode* TopNode;
	wxString ProjectFilePath;
	wxString TestString;
	wxString IndexStr;
	wxString LabelStr;

	CleanConfiguration();

	ProjectFilePath=ProjectPath+"/pixtendV2_target.xml";

	if (!doc.Load(ProjectFilePath)) return ERR_TARGET_PLUGIN_FILE_ERROR;  // File does not exist or can not be loaded

	// Check that the XML file is a Beremiz project file
	RootNode=doc.GetRoot();
	if (RootNode->GetName() != "beremiz_project") return ERR_TARGET_PLUGIN_INVALID_FILE;  // Not a Beremiz project file ?
	RootNode->GetAttribute ("type", &TestString);
	if (TestString != "pixtend_v2") return ERR_TARGET_PLUGIN_INVALID_FILE;
	// Check that Beremiz project file version is supported
	RootNode->GetAttribute ("version", &TestString);
	if (TestString != "1") return ERR_TARGET_PLUGIN_INVALID_FILE_VERSION;   // Project file version is not supported

	// TODO : add selection between V2-S and V2-L
	TopNode = RootNode->GetChildren();
	while (TopNode != 0)
	{
		if (TopNode->GetName()=="target")
		{
			RemoteTarget = TopNode->GetAttribute ("ip", "");
			RemoteLogin = TopNode->GetAttribute ("login", "");
			RemotePassword = TopNode->GetAttribute ("password", "");
			RemotePath = TopNode->GetAttribute ("path", "");
		}

		else if (TopNode->GetName()=="winscp")
		{
			WinSCPLocation = TopNode->GetAttribute ("location", "");
		}

		TopNode = TopNode->GetNext();
	}

	DataHasChanged = false;

	return 0;
}  // TP_LoadTargetProjectData
// -----------------------------------------------------

int32_t __cdecl TP_SaveTargetProjectData (void)
{
	FILE* ProjectFile;

	ProjectFile=fopen (ProjectPath+"/pixtendV2_target.xml", "wt");
	if (ProjectFile==0) return ERR_TARGET_PLUGIN_FILE_ERROR;		// Can not create project file

	// Save XML header and create top level tag
	fprintf (ProjectFile, "<?xml version='1.0' encoding='utf-8'?>\n");
	fprintf (ProjectFile, "<beremiz_project type=\"pixtend_v2\" version=\"1\">\n");

	// Save parameters and options
	// Save remote target parameters
	fprintf (ProjectFile, "    <target ip=\""+RemoteTarget+"\" login=\""+RemoteLogin+"\" password=\""+RemotePassword+"\" path=\""+RemotePath+"\" />\n");

	// Save file transfer option
	fprintf (ProjectFile, "    <winscp location=\""+WinSCPLocation+"\" />\n");

	// TODO : add selection between V2-S and V2-L

	// Close project tag
	fprintf (ProjectFile, "</beremiz_project>\n");

	fclose (ProjectFile);

	DataHasChanged = false;

	return 0;
}  // TP_SaveTargetProjectData
// -----------------------------------------------------

void OpenEditor (uint32_t EditorIndex)
{
	if (Editor==0)
		Editor = new PixtendV2_IOEditFrame (NULL);

	if (Editor)
	{
		Editor->Show(true);
		Editor->RefreshView();
		Editor->SetFocus();  // Put on top
	}
}  // OpenEditor
// -----------------------------------------------------

void CloseEditor (int32_t EditorIndex)
{
#ifdef __TARGET_WIN__
	if (Editor)
		Editor->Show(false);
#endif  // __TARGET_WIN__
#ifdef __TARGET_LINUX__
	if (Editor)
	{
		delete Editor;
		Editor = 0;
	}
#endif  // __TARGET_LINUX__
}  // CloseEditor
// -----------------------------------------------------

int32_t __cdecl TP_OpenEditor(void* WXUNUSED(Parent), uint32_t EditorIndex)
{
#ifdef __TARGET_WIN__
	// Send a message to wx thread to show a frame
    wxThreadEvent *event = new wxThreadEvent(wxEVT_THREAD, CMD_SHOW_WINDOW);
    event->SetInt(EditorIndex);
    wxQueueEvent(wxApp::GetInstance(), event);

	return TARGET_PLUGIN_NO_ERROR;
#endif // _TARGET_WIN__
	#ifdef __TARGET_LINUX__
	OpenEditor (EditorIndex);
	return TARGET_PLUGIN_NO_ERROR;
#endif  // __TARGET_LINUX__
}  // TP_OpenEditor
// -----------------------------------------------------

void __cdecl TP_CloseEditor(int32_t EditorIndex)
{
#ifdef __TARGET_WIN__
    wxThreadEvent *event = new wxThreadEvent(wxEVT_THREAD, CMD_HIDE_WINDOW);
	event->SetInt(EditorIndex);
    wxQueueEvent(wxApp::GetInstance(), event);
#endif  // __TARGET_WIN__
#ifdef __TARGET_LINUX__
	CloseEditor (EditorIndex);
#endif  //__TARGET_LINUX__
}  // TP_CloseEditor
// -----------------------------------------------------

int32_t __cdecl TP_CreateBeremizProjectFiles (void)
{
	bool FileOK;

	// Copy XML files from basic project into the new folder (use a basic project that can be compiled)
	FileOK = wxCopyFile (TargetsDirectory+"Targets\\RPi\\PiXtend_V2\\beremiz.xml", ProjectPath+"\\beremiz.xml");
	FileOK &= wxCopyFile (TargetsDirectory+"Targets\\RPi\\PiXtend_V2\\plc.xml", ProjectPath+"\\plc.xml");

	if (FileOK == false) return ERR_TARGET_PLUGIN_FILE_ERROR;

	return 0;
}  // TP_CreateBeremizProjectFiles
// -----------------------------------------------------

int32_t __cdecl TP_GenerateTargetFramework (void)
{
	FILE* CommandFile;
	wxString BaseFilesPath;
	wxString WinSCPCommand;
	//long m_pidLast;		// To use with wxExecute
	int ErrCode;

	// Generate WinSCP command file to copy base project files to remote target
	// TODO : report creation error
	CommandFile=fopen (ProjectPath+"\\scp_copy_framework.txt", "wt");

	fprintf (CommandFile, "option batch on\noption confirm off\n");
	fprintf (CommandFile, "open scp://"+RemoteLogin+":"+RemotePassword+"@"+RemoteTarget+" -hostkey=*\n");

	// Copy first the basic PLC files used by all projects
	BaseFilesPath = TargetsDirectory+"Common\\";
	fprintf (CommandFile, "put "+BaseFilesPath+"accessor.h "+RemotePath+"\n");
	fprintf (CommandFile, "put "+BaseFilesPath+"beremiz.h "+RemotePath+"\n");
	fprintf (CommandFile, "put "+BaseFilesPath+"iec_std_FB.h "+RemotePath+"\n");
	fprintf (CommandFile, "put "+BaseFilesPath+"iec_std_FB.c "+RemotePath+"\n");
	fprintf (CommandFile, "put "+BaseFilesPath+"iec_std_FB_no_ENENO.h "+RemotePath+"\n");
	fprintf (CommandFile, "put "+BaseFilesPath+"iec_std_functions.h "+RemotePath+"\n");
	fprintf (CommandFile, "put "+BaseFilesPath+"iec_std_lib.h "+RemotePath+"\n");
	fprintf (CommandFile, "put "+BaseFilesPath+"iec_std_lib.c "+RemotePath+"\n");
	fprintf (CommandFile, "put "+BaseFilesPath+"iec_types.h "+RemotePath+"\n");
	fprintf (CommandFile, "put "+BaseFilesPath+"iec_types_all.h "+RemotePath+"\n");

	// Copy now CBUS PLC target specific runtime source files
	BaseFilesPath = TargetsDirectory+"Targets\\RPi\\PiXtend_V2\\";
	fprintf (CommandFile, "put "+BaseFilesPath+"pixtend.h "+RemotePath+"\n");
	fprintf (CommandFile, "put "+BaseFilesPath+"pixtend.c "+RemotePath+"\n");
	// TODO : copy V2L or V2S depending on hardware
	fprintf (CommandFile, "put "+BaseFilesPath+"pixtend_v2l_beremiz.h "+RemotePath+"\n");
	fprintf (CommandFile, "put "+BaseFilesPath+"pixtend_v2l_beremiz.c "+RemotePath+"\n");
	fprintf (CommandFile, "put "+BaseFilesPath+"SupervisorComm.h "+RemotePath+"\n");
	fprintf (CommandFile, "put "+BaseFilesPath+"SupervisorComm.c "+RemotePath+"\n");
	fprintf (CommandFile, "put "+BaseFilesPath+"plc_main.c "+RemotePath+"\n");

	if (!HoldSCPTransfer)
		fprintf (CommandFile, "close\nexit\n");

	fclose (CommandFile);

	// Launch WinSCP with generated file
	// Add quotes to WinSCP location (as it is normally in "Program Files (x86)"...)  and to script file (in case there are spaces in the path or project name)
	WinSCPCommand ="\""+WinSCPLocation+"\"" + " /script="+ProjectPath+"\\scp_copy_framework.txt";

	//WinSCPCommand = "\"C:\\Program Files (x86)\\WinSCP\\WinSCP.com\" /script="+ProjectPath+"\\scp_commands_target.txt";		// Hardcoded WinSCP path
	// We can not use wxExecute in the plugin since wxWidgets complains about the fact wxExecute must be started from the main thread
	// The problem is that the DLL uses its own thread, while this function is called from the Project Manager thread
	// We simply use the system() function, which is perfect as it will block the Manager until file transfer is finished
	//m_pidLast = wxExecute(WinSCPCommand, wxEXEC_ASYNC);		// Use wxEXEC_SYNC if the function is used outside the DLL to make the Project Manager wait
	ErrCode = system (WinSCPCommand);

	// TODO : check return value from WinSCP to check if all files have been transferred
	//printf ("%d\n", m_pidLast);		// m_pidLast is return code from WinSCP (allowing to know if there was an error)

	return 0;
}  // TP_GenerateTargetFramework
// -----------------------------------------------------

int32_t __cdecl TP_CopyPLCFilesForCompilation (void)
{
	FILE* CommandFile;
	wxString BuildPath;
	wxString WinSCPCommand;
	//long m_pidLast;		// To use with wxExecute
	int ErrCode;

	BuildPath=ProjectPath+"\\build\\";

	// Generate WinSCP command file to copy base project files to remote target
	CommandFile=fopen (ProjectPath+"\\scp_copy_plc.txt", "wt");
	if (CommandFile==0) return -1;

	fprintf (CommandFile, "option batch on\noption confirm off\n");
	fprintf (CommandFile, "open scp://"+RemoteLogin+":"+RemotePassword+"@"+RemoteTarget+" -hostkey=*\n");

	fprintf (CommandFile, "put "+BuildPath+"Config.c "+RemotePath+" \n");
	fprintf (CommandFile, "put "+BuildPath+"Config.h "+RemotePath+" \n");
	fprintf (CommandFile, "put "+BuildPath+"POUS.h "+RemotePath+" \n");
	fprintf (CommandFile, "put "+BuildPath+"POUS2.h "+RemotePath+" \n");
	fprintf (CommandFile, "put "+BuildPath+"Resource1.c "+RemotePath+" \n");

	// Copy I/O configuration files
	//fprintf (CommandFile, "put "+BuildPath+"cbus_inputs.dat "+RemotePath+" \n");
	//fprintf (CommandFile, "put "+BuildPath+"cbus_outputs.dat "+RemotePath+" \n");

	// TODO : copy C extensions

	if (!HoldSCPTransfer)
		fprintf (CommandFile, "close\nexit\n");

	fclose (CommandFile);

	// Launch WinSCP with generated file
	// Add quotes to WinSCP location (as it is normally in "Program Files (x86)"...) and to script file (in case there are spaces in the path or project name)
	WinSCPCommand = "\""+WinSCPLocation+"\"" + " /script="+ProjectPath+"\\scp_copy_plc.txt";

	//WinSCPCommand = "\"C:\\Program Files (x86)\\WinSCP\\WinSCP.com\" /script="+ProjectPath+"\\build\\scp_copy_plc.txt";		// Hardcoded WinSCP path
	// We can not use wxExecute in the plugin since wxWidgets complains about the fact wxExecute must be started from the main thread
	// The problem is that the DLL uses its own thread, while this function is called from the Project Manager thread
	// We simply use the system() function, which is perfect as it will block the Manager until file transfer is finished
	//m_pidLast = wxExecute(WinSCPCommand, wxEXEC_ASYNC);		// Use wxEXEC_SYNC if the function is used outside the DLL to make the Project Manager wait
	ErrCode = system (WinSCPCommand);

	// TODO : check return value from WinSCP to check if all files have been transferred
	//printf ("%d\n", m_pidLast);		// m_pidLast is return code from WinSCP (allowing to know if there was an error)

	return 0;
}  // TP_CopyPLCFilesForCompilation
// -----------------------------------------------------

int32_t __cdecl TP_GenerateIOConfigurationFiles (void)
{
	return 0;
}  // TP_GenerateIOConfigurationFiles
// -----------------------------------------------------

int32_t TP_CleanForBuild (void)
{
	wxString BuildDir;
	wxDir Directory;
	bool FoundFile;
	wxString Filename;
	FILE* CommandFile;
	wxString WinSCPCommand;
	int ErrCode;

	// Remove all files in build directory on this computer
	BuildDir = ProjectPath+"/build/";
	Directory.Open (BuildDir);
	FoundFile = Directory.GetFirst (&Filename, "*.*");

	while (FoundFile)
	{
		wxRemoveFile (BuildDir + Filename);
		FoundFile = Directory.GetNext (&Filename);
	}

	Directory.Close ();

	// Erase files on remote target by sending command using WinSCP
	CommandFile=fopen (ProjectPath+"\\scp_clean_target.txt", "wt");
	if (CommandFile==0) return ERR_TARGET_PLUGIN_FILE_ERROR;

	fprintf (CommandFile, "option batch on\noption confirm off\n");
	fprintf (CommandFile, "open scp://"+RemoteLogin+":"+RemotePassword+"@"+RemoteTarget+" -hostkey=*\n");
	fprintf (CommandFile, "cd "+RemotePath+"\n");
	fprintf (CommandFile, "rm *.*\n");

	fprintf (CommandFile, "close\nexit\n");
	fclose (CommandFile);

	WinSCPCommand = WinSCPLocation + " /script="+ProjectPath+"\\scp_clean_target.txt";
	ErrCode = system (WinSCPCommand);

	return 0;
}  // TP_CleanForBuild
// -----------------------------------------------------

uint32_t TP_GetNumberOfEditors (void)
{
	// TODO : we can add a Modbus entry later to use the serial port
	return 1;
}  // TP_GetNumberOfEditors
// -----------------------------------------------------

void TP_GetEditorLabel (uint32_t WXUNUSED(EditorIndex), char* EditorName, int32_t* TreeIconIndex)
{
	strcpy (EditorName, "");
	*TreeIconIndex = TP_TREE_ICON_NONE;
}  // TP_GetEditorLabel
// -----------------------------------------------------

int32_t TP_DataHasChanged (void)
{
	if (DataHasChanged) return 1;
	return 0;
}  // TP_DataHasChanged
// -----------------------------------------------------

int32_t TP_IsOptionSupported (uint32_t Option)
{
	switch (Option)
	{
		case TP_OPTION_TARGET_START : return 1;
		case TP_OPTION_TARGET_STOP : return 1;
		case TP_OPTION_TARGET_AUTO_START : return 1;

		case TP_OPTION_COMPILATION_EXTERNAL : return 0;
		case TP_OPTION_PLUGIN_COMPILER : return 1;
		default : return -1;		// Option is not known, assume it is not supported
	}
}  // TP_IsOptionSupported
// -----------------------------------------------------

int32_t TP_StartCompilation (void)
{
	if (Supervisor)
	{
		return Supervisor->StartCompilation (RemoteTarget);
	}
	else return ERR_TARGET_NO_COMMUNICATION;
}  // TP_StartCompilation
// -----------------------------------------------------

int32_t EXPORT_DYNAMIC_LIB TP_GetCompilerMessages (uint8_t* Msg)
{
	if (Supervisor)
	{
		return Supervisor->GetCompilerMessages ((char*)Msg);
	}
	else return ERR_TARGET_NO_COMMUNICATION;
}  // TP_GetCompilerMessages
// -----------------------------------------------------

} // extern "C"
