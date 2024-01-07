/////////////////////////////////////////////////////////////////////////////
// Name:        BeremizProjectManagerMainFrame.h
// Purpose:     Beremiz Project Manager main frame
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include <wx/aboutdlg.h>
#include <wx/xml/xml.h>

#include <stdint.h>

#include "BeremizProjectManagerMainFrame.h"
#include "BeremizProjectManagerApp.h"
#include "GraphicsUtils.h"
#include "CPUSelectionDialog.h"
#include "OptionsDialog.h"
#include "BeremizProjectManager_SDK_Defs.h"

// the application icon (under Windows it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "MainIcon.xpm"
#endif

wxIMPLEMENT_APP(CBeremizProjectManagerApp);

CBeremizProjectManagerMainFrame::CBeremizProjectManagerMainFrame (wxFrame* ParentFrame) : CBaseFrame (ParentFrame)
{
	CompilationInProgress=false;
	Project = 0;
	this->LoadManagerConfiguration();

	EmptyPanel = new NoParamPanel (this->TopRightPanel);

	// Let's do some iconic work...
	this->SetIcon(wxICON(MainIcon));
	InitProjectTreeIcons (*ProjectTree);

	// Create the default entry in the tree
    rootItemId = ProjectTree->AddRoot(wxT("New PLC project"), PROJECT_TREE_ICON_PROJECT, PROJECT_TREE_ICON_PROJECT, 0);

	// Init detection of size change
	UpdateEditorSize ();

	MainTimer.Start(100);
}  // CBeremizProjectManagerMainFrame::CBeremizProjectManagerMainFrame
// -----------------------------------------------------

CBeremizProjectManagerMainFrame::~CBeremizProjectManagerMainFrame()
{
	MainTimer.Stop();

	if (Project)
	{
		delete Project;		// This will also unload the target plugin and supervisor communicator
		Project = 0;
	}
}  // CBeremizProjectManagerMainFrame::~CBeremizProjectManagerMainFrame()
// -----------------------------------------------------

//! Click on close button on window or request to close the window sent by OnQuit
void CBeremizProjectManagerMainFrame::OnClose(wxCloseEvent& event)
{
	int DialogResult;

	// Warn user if project has not been saved
	if (Project)
	{
		if (Project->HasChanged())
		{
			DialogResult = wxMessageBox ("Latest changes in the project have not been saved.\nDo you really want to quit?", "Unsaved changes", wxYES_NO+wxICON_WARNING);
			if (DialogResult == wxNO)
			{
				event.Veto();		// Ignore the close command
				return;
			}
		}
	}

	Destroy();
}  // CBeremizProjectManagerMainFrame::OnClose
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::UpdateEditorSize (void)
{
	CurrentFrameSize = TopRightPanel->GetClientSize();

	if (CurrentFrameSize == LastFrameSize) return;

	// Update all possible PLC element editors
	EmptyPanel->SetClientSize (CurrentFrameSize);			// Always exist : no need to check if pointer is valid

	LastFrameSize = CurrentFrameSize;
}  // CBeremizProjectManagerMainFrame::UpdateEditorSize
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnProjectNewMenu(wxCommandEvent& WXUNUSED(event))
{
	bool EmptyProjectCheck;
	int DialogResult;
	int FileResult;
	CPUSelectionDialog* CPUSelDialog;
	//unsigned int CPUSelected=0;
	wxString ProjectDir;
	wxDir Directory;
	wxString Filename;
	wxString SelectedTargetPlugin;

	// If current project has not been saved, display a warning
	if (Project)
	{
		if (Project->HasChanged())
		{
			DialogResult = wxMessageBox ("Latest changes in current project have not been saved.\nDo you really want to create a new project?", "Unsaved changes", wxYES_NO+wxICON_WARNING);
			if (DialogResult == wxNO) return;
		}
	}

	// Enter name and path for the new project (use the "Create folder" button)
	// TODO : Maybe we should create a more understandable dialog (rather than using the Create Folder button)
	wxDirDialog dlg(NULL, "Create new project directory", "", 0);
	if (dlg.ShowModal() == wxID_CANCEL) return;

	// Check that directory is empty. If not, warn user about consequences
	ProjectDir = dlg.GetPath();
	Directory.Open (ProjectDir);
	EmptyProjectCheck = Directory.GetFirst (&Filename, "*.*");
	if (EmptyProjectCheck==true)
	{
		wxMessageBox ("Project directory is not empty. Can not create Beremiz project here", "Project folder not empty", wxOK+wxICON_ERROR);
		return;
	}

	// Delete previous project in case there was already one in memory
	if (Project!=0)
	{
		delete Project;
		Project = 0;
	}

	// Ask user to select a CPU first
	CPUSelDialog = new CPUSelectionDialog(this);
	CPUSelDialog->ShowModal();

	if (CPUSelDialog->OKClicked==false) return;		// Cancel clicked : abort project creation
	// CPUSelDialog->TargetPluginName now contains the dynamic library needed for the target. This library will give also the display name of the target
	SelectedTargetPlugin = CPUSelDialog->TargetPluginName;

	delete CPUSelDialog;
	CPUSelDialog = 0;

	// Create a new empty project
	Project = new CBeremizProject ();
	if (Project==0)
	{
		wxMessageBox ("Project can not be created!", "Critical error", wxOK+wxICON_ERROR);
		return;
	}

	Project->SetPathAndName (dlg.GetPath());
	Project->SetTargetsPath (TargetsDirectory);
	Project->SetTargetPlugin (SelectedTargetPlugin);
	//Project->SetCPUModel (CPUSelected);		// This call will load the target plugin too
	this->SetTitle ("Beremiz Project Manager - "+Project->GetProjectName());

	// Rebuild completely the project tree
	this->BuildTreeFromProject();

	FileResult = Project->CreateBeremizProjectFiles ();

	if (FileResult != 0)
	{
		wxMessageBox ("An error occured while project was created", "Can not copy base project files", wxOK+wxICON_WARNING);
	}

	this->LogTextCtrl->AppendText ("Project created and saved\n");
	Project->SaveProject();
}  // CBeremizProjectManagerMainFrame::OnProjectNewMenu
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnProjectOpenMenu(wxCommandEvent& WXUNUSED(event))
{
	int DialogResult;
	int LoadResult;
	wxString ErrorMsg;

	// If current project has not been saved, display a warning
	if (Project)
	{
		if (Project->HasChanged())
		{
			DialogResult = wxMessageBox ("Latest changes in current project have not been saved.\nDo you really want to load a project?", "Unsaved changes", wxYES_NO+wxICON_WARNING);
			if (DialogResult == wxNO) return;
		}
	}

	// User shall select a directory (directory name = project name)
	wxDirDialog dlg(NULL, "Select Beremiz project directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)	return;

	// Delete previous project in case there was already one in memory
	if (Project!=0)
	{
		delete Project;
		Project = 0;
	}

	// Create a new empty project
	Project = new CBeremizProject ();
	if (Project==0)
	{
		wxMessageBox ("Project can not be created in memory!\nCan not load project file", "Critical error", wxOK+wxICON_ERROR);
		return;
	}

	// If we find default files, make manager point to the directory
	Project->SetPathAndName(dlg.GetPath());
	Project->SetTargetsPath (TargetsDirectory);

	// Load project file (this will clear project structure)
	LoadResult = Project->LoadProject ();		// This call instanciate the target plugin
	if (LoadResult!=0)
	{
		switch (LoadResult)
		{
			case ERR_TARGET_PLUGIN_FILE_ERROR : ErrorMsg = "Target plugin file can not be found or loaded"; break;
			case ERR_TARGET_PLUGIN_INVALID_FILE : ErrorMsg = "Project file is invalid"; break;
			case ERR_TARGET_PLUGIN_INVALID_FILE_VERSION : ErrorMsg = "Project file version is not compatible with the Project Manager"; break;
			default : ErrorMsg = "An error occured while loading project file";
		}
		wxMessageBox (ErrorMsg, "Can not load Beremiz project", wxOK+wxICON_ERROR);
		// TODO : clear project / reset project name in case of error ?

		return;
	}

	// Update title bar with project name
	this->SetTitle ("Beremiz Project Manager - "+Project->GetProjectName());

	// Rebuild completely the project tree
	this->BuildTreeFromProject();
}  // CBeremizProjectManagerMainFrame::OnProjectOpenMenu
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnProjectSaveMenu (wxCommandEvent& WXUNUSED(event))
{
	if (Project==0) return;

	Project->SaveProject();
	this->LogTextCtrl->AppendText ("Project saved\n");
}  // CBeremizProjectManagerMainFrame::OnProjectSaveMenu
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnProjectCloseMenu (wxCommandEvent& WXUNUSED(event))
{
	int DialogResult;

	if (Project==0) return;   // No project loaded

	// If current project has not been saved, display a warning
	if (Project->HasChanged())
	{
		DialogResult = wxMessageBox ("Latest changes in current project have not been saved.\nDo you really want to close the current project?", "Unsaved changes", wxYES_NO+wxICON_WARNING);
		if (DialogResult == wxNO) return;
	}

	this->SetTitle ("Beremiz Project Manager");

	// Clean project tree
	ProjectTree->DeleteAllItems();
    rootItemId = ProjectTree->AddRoot(wxT("New PLC project"), PROJECT_TREE_ICON_PROJECT, PROJECT_TREE_ICON_PROJECT, 0);

	delete Project;
	Project = 0;

	//RemoteTargetMenu->Enable(false);
	this->LogTextCtrl->AppendText ("Project closed\n");
}  // CBeremizProjectManagerMainFrame::OnProjectCloseMenu
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnProjectExitMenu(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}  // CBeremizProjectManagerMainFrame::OnProjectExitMenu
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnConnectionReportMenu (wxCommandEvent& WXUNUSED(event))
{

}  // CBeremizProjectManagerMainFrame::OnConnectionReportMenu
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnGenerateFrameworkMenu (wxCommandEvent& WXUNUSED(event))
{
	int GenerateResult;

	// Check first that a project has been loaded
	if (Project==0)
	{
		wxMessageBox ("A project must be created or loaded before PLC framework can be generated", "Can not generate PLC framework", wxOK+wxICON_INFORMATION);
		return;
	}

	GenerateResult = Project->GenerateTargetFramework ();
	if (GenerateResult!=0)
	{
		wxMessageBox ("Error during framework generation", "Generate PLC framework", wxOK+wxICON_ERROR);
		return;
	}

	this->LogTextCtrl->AppendText ("PLC framework generated successfully.\n");
}  // CBeremizProjectManagerMainFrame::OnGenerateFrameworkMenu
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnOpenBeremizEditor (wxCommandEvent& WXUNUSED(event))
{
#ifdef __TARGET_WIN__
	long m_pidLast;
#endif
	wxString Cmd;

	// TODO : check if Editor is not yet launched

	// Check first that a project has been loaded
	if (Project==0)
	{
		wxMessageBox ("A project must be created or loaded before Beremiz Editor can be launched", "Can not launch Beremiz Editor", wxOK+wxICON_INFORMATION);
		return;
	}

	//this->SaveProject();

#ifdef __TARGET_WIN__
	Cmd="..\\python\\pythonw.exe ..\\beremiz\\Beremiz.py \""+Project->GetProjectPath()+"\"";		// Load project directly in Beremiz
	//Cmd="..\\python\\pythonw.exe ..\\beremiz\\Beremiz.py";

	// TODO : using a non-NULL callback below allows to know when Beremiz closes
	m_pidLast = wxExecute(Cmd, wxEXEC_ASYNC, 0, 0);

	if (m_pidLast==0)
	{
		wxMessageBox ("Can not start Beremiz Editor", "Error", wxOK+wxICON_ERROR);
		return;
	}
#endif // __TARGET_WIN__
#ifdef __TARGET_LINUX__
	// TODO : add an option for Linux target to give the python name (python27, etc...) as new machines will have python3 called using this command line
	Cmd="python2 \"../Beremiz/Beremiz.py\" \""+Project->GetProjectPath()+"\"";
	wxShell (Cmd);
#endif
}  // CBeremizProjectManagerMainFrame::OnOpenBeremizEditor
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnBuildCleanupMenu (wxCommandEvent& WXUNUSED(event))
{
	int DialogResult;

	// Check first that a project has been loaded
	if (Project==0)
	{
		wxMessageBox ("A project must be created or loaded before Build commands can be executed", "Cleanup project binaries", wxOK+wxICON_INFORMATION);
		return;
	}

	// Warn user about is going to happen
	DialogResult = wxMessageBox ("This will erase all generated target files.\nYou will need to generate again all files before project can be compiled.\n\nDo you confirm you want to clean the target files?", "Clean target files", wxYES_NO+wxICON_INFORMATION);
	if (DialogResult == wxNO) return;

	if (Project->TargetPluginLoaded)
	{
		// TODO : display error from return code
		Project->TargetPlugin->CleanForBuild();
	}
}  // CBeremizProjectManagerMainFrame::OnBuildCleanupMenu
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnBuildMenu (wxCommandEvent& WXUNUSED(event))
{
	int EditPOUSResult;
	int CopyFileResult;
	int GenerateIOFilesResult;
	wxString ErrorMsg;
	int CompileResult;
	int OptionSupported;

	if (Project==0)
	{
		wxMessageBox ("A project must be created or loaded before Build commands can be executed", "Build project binaries", wxOK+wxICON_INFORMATION);
		return;
	}

	if (ChkClearBeforeBuild->GetValue())
	{
		this->LogTextCtrl->Clear();
	}
	// TODO : check that Beremiz has generated target source code

	if (Project->HasChanged())
		Project->SaveProject();

	// Process the POUS.c from IEC2C quirkness...
	EditPOUSResult = Project->ProcessBeremizC_POU ();
	if (EditPOUSResult!=0)
	{
		switch (EditPOUSResult)
		{
			case -32768 : ErrorMsg = "Resource1.c file is missing.\nPlease check that C source files have been generated from Beremiz"; break;
			case -1 : ErrorMsg = "Can not open Resource1_Temp.c"; break;
			case -2 : ErrorMsg = "Can not create Resource1.c"; break;
			default : ErrorMsg = "An error occured during edition of resource file.\nMake sure that your resource is called Resource1";
		}
		wxMessageBox (ErrorMsg, "Error during POUs C processing", wxOK+wxICON_ERROR);
		return;
	}

	GenerateIOFilesResult = Project->GenerateIOConfigurationFiles ();
	if (GenerateIOFilesResult != 0)
	{
		wxMessageBox ("An error occured during generation of I/O configuration files", "Build project", wxOK+wxICON_ERROR);
		return;
	}

	// We now have to put all generated files in the compilation directory
	CopyFileResult = Project->CopyPLCFilesForCompilation();
	if (CopyFileResult!=0)
	{
		switch (CopyFileResult)
		{
			case ERR_TARGET_PLUGIN_FILE_ERROR : ErrorMsg = "An error occured while copying PLC source files to target"; break;
			case ERR_TARGET_PLUGIN_NON_SUPPORTED_FEATURE : ErrorMsg = "Operation/option is not supported"; break;
			default : ErrorMsg = "An unknown error occured while copying PLC source files to target";
		}
		wxMessageBox (ErrorMsg, "Error during PLC source files transfer", wxOK+wxICON_ERROR);
		return;
	}

	this->LogTextCtrl->AppendText ("Starting Build...\n");

	if (Project->TargetPluginLoaded==0)
	{
		this->LogTextCtrl->AppendText ("No target plugin loaded : ending Build...\n");
		return;
	}

	// Check first if compilation can be launched from project manager
	OptionSupported = Project->TargetPlugin->IsOptionSupported (TP_OPTION_PLUGIN_COMPILER);
	if (OptionSupported==1)
	{
		CompileResult = Project->StartCompilation ();
		if (CompileResult<0)
		{
			switch (CompileResult)
			{
				case ERR_TARGET_PLUGIN_NON_SUPPORTED_FEATURE : ErrorMsg = "Compiler for this target can not be launched from Beremiz Project Manager"; break;
				case ERR_TARGET_NO_COMMUNICATION : ErrorMsg = "Communication with target is not established"; break;
				case ERR_TARGET_COMMUNICATION_ERROR : ErrorMsg = "Communication error with target"; break;
				case ERR_TARGET_COMMUNICATION_TIMEDOUT : ErrorMsg = "No reply from target"; break;
				case ERR_TARGET_COMPILER_FAULT : ErrorMsg = "Compiler encountered an error"; break;
				default : ErrorMsg = "Unknown error";
			}
			wxMessageBox (ErrorMsg, "Can not start PLC compilation process", wxOK+wxICON_ERROR);
			return;
		}

		// We need now to receive stream of compiler messages until plugin reports end of compilation
		// so we don't stay in this method. Reception from Supervisor will now be made by window timer
		CompilationInProgress = true;
		this->MainTimer.Start(1);		// Run timer as fast as possible to get messages from the supervisor

		return;
	}

	// If target reports it can't be compiled from the plugin, we assume we have external compilation only
	wxMessageBox ("Compiler for this target is not controlled from Project Manager.\nPlease refer to user's manual for instructions using the external compiler", "Start PLC compilation", wxOK+wxICON_INFORMATION);
	this->LogTextCtrl->AppendText ("External compilation process : stopping here.\n");
}  // CBeremizProjectManagerMainFrame::OnBuildMenu
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnRebuildMenu (wxCommandEvent& WXUNUSED(event))
{
	if (ChkClearBeforeBuild->GetValue())
	{
		this->LogTextCtrl->Clear();
	}

	if (Project==0)
	{
		wxMessageBox ("A project must be created or loaded before Build commands can be executed", "Rebuild project binaries", wxOK+wxICON_INFORMATION);
		return;
	}

	// TODO : make this as a call to Cleanup then Build
}  // CBeremizProjectManagerMainFrame::OnRebuildMenu
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnBuildStopMenu (wxCommandEvent& WXUNUSED(event))
{
}  // CBeremizProjectManagerMainFrame::OnBuildStopMenu
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnHelpAboutMenu (wxCommandEvent& WXUNUSED(event))
{
	AboutDialog* Dialog;

	Dialog = new AboutDialog (this);
	if (Dialog)
	{
		Dialog->VersionStr->SetLabel ("Version 0.3.0");
		Dialog->ShowModal();
		delete Dialog;
	}

	/*
	Old code based on standard About box from wxWidgets
	wxAboutDialogInfo info;
	info.SetName ("Beremiz Project Manager");
	info.SetVersion ("0.1");
	info.SetDescription ("Beremiz Project Manager uses wxWidgets 3.1 framework");
	info.SetCopyright ("(c) Benoit BOUCHEZ (BEB) 2021/2022");
	wxAboutBox (info);
	*/
}  // CBeremizProjectManagerMainFrame::OnHelpAboutMenu
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnMainTimer (wxTimerEvent& WXUNUSED(event))
{
	char LogBuffer[1500];
	int CompilerMsgResult;
	wxSize CurrentSize;

	UpdateEditorSize();

	if (CompilationInProgress)
	{// Get next message from supervisor
		CompilerMsgResult=Project->GetCompilerMessages(&LogBuffer[0]);
		if (CompilerMsgResult==-1)
		{
			this->LogTextCtrl->AppendText ("Build finished\n");
			CompilationInProgress=false;
			this->MainTimer.Start (100);   // Return to default timing
		}
		else if (CompilerMsgResult>0)
		{
			this->LogTextCtrl->AppendText (LogBuffer);
		}
	}
}  // CBeremizProjectManagerMainFrame::OnMainTimer
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::BuildTreeFromProject (void)
{
	int NumEditors;
	int NewEntry;
	char TreeLabel[TARGET_PLUGIN_STRING_SIZE];
	int32_t IconIndex;

	ProjectTree->DeleteAllItems();
	rootItemId = 0;
	CPUItemId = 0;

	if (Project==0) return;

	rootItemId = ProjectTree->AddRoot(Project->GetProjectName(), PROJECT_TREE_ICON_PROJECT, PROJECT_TREE_ICON_PROJECT);
	// Create CPU node
	CPUItemId = ProjectTree->AppendItem(rootItemId, Project->GetCPUDisplayName(), PROJECT_TREE_ICON_CPU, PROJECT_TREE_ICON_CPU);

	if (Project->TargetPluginLoaded)
	{
		NumEditors = Project->TargetPlugin->GetNumberOfEditors();

		if (NumEditors>1)		// Editor 1 = main editor, >1 sub editors
		{
			for (NewEntry=1; NewEntry<NumEditors; NewEntry++)  // We have to offset by 1 as Editor 0 is the CPU in the plugin
			{
				Project->TargetPlugin->GetEditorLabel (NewEntry, &TreeLabel[0], &IconIndex);
				// TODO : make a table with created tree ID
				ProjectTree->AppendItem (CPUItemId, TreeLabel, IconIndex);
			}
		}
	}

    ProjectTree->ExpandAll ();
}  // CBeremizProjectManagerMainFrame::BuildTreeFromProject
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnTreeDoubleClick (wxTreeEvent& event)
{
	wxTreeItemId ItemId = event.GetItem();

	if (Project==0) return;

	// TODO : use the target plugin to define if there is a dedicated window or embedded window

	// Display edition box depending on CPU type and what is selected in the tree
	if (ItemId == CPUItemId)
	{
		if (Project!=0)
			Project->OpenEditor (this, 0);		// TODO : set editor index depending on the icon clicked
		EmptyPanel->EditableLabel->SetLabel("Element is edited using external editor");
	}
	else
	{
		EmptyPanel->EditableLabel->SetLabel ("No editable parameter for this element");
	}
}  // CBeremizProjectManagerMainFrame::OnTreeDoubleClick
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnTreeSelChanged (wxTreeEvent& event)
{
	wxTreeItemId ItemId = event.GetItem();

	// TODO : if there is a internal editor, display it when item is selected

	if (ItemId == CPUItemId)
	{
		EmptyPanel->EditableLabel->SetLabel("Element is edited using external editor");
	}
	else
	{
		EmptyPanel->EditableLabel->SetLabel ("No editable parameter for this element");
	}
}  // CBeremizProjectManagerMainFrame::OnTreeSelChanged
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnOptionsGeneralMenu (wxCommandEvent& WXUNUSED(event))
{
	OptionsDialog* Dialog;

	Dialog=new OptionsDialog (this);

	if (Dialog)
	{
		Dialog->EditBaseFilesLocation->SetValue (this->TargetsDirectory);
		if (Dialog->ShowModal() == wxID_OK)
		{
			TargetsDirectory = Dialog->EditBaseFilesLocation->GetValue();
			this->SaveManagerConfiguration();
		}

		delete Dialog;
	}
}  // CBeremizProjectManagerMainFrame::OnOptionsGeneralMenu
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnShowPluginVersionMenu (wxCommandEvent& WXUNUSED(event))
{
	uint32_t Major;
	uint32_t Minor;
	uint32_t Build;
	uint32_t Revision;
	bool NoVersionAvailable = false;

	// Check if we have something to be displayed
	if (Project==0) NoVersionAvailable = true;
	else
	{
		if (Project->TargetPluginLoaded==false) NoVersionAvailable = true;
	}

	if (NoVersionAvailable)
	{
		wxMessageBox ("No project loaded or no CPU defined.\nCan not display any plugin version.", "Show plugin version", wxOK+wxICON_INFORMATION);
		return;
	}

	// Dump information in the console for now (TODO : make a dedicated dialog or we can use the panel)
	Project->TargetPlugin->GetPluginVersion (&Major, &Minor, &Build, &Revision);
	this->LogTextCtrl->AppendText ("Plugin version : "+wxString::Format("%d",Major)+"."+wxString::Format("%d",Minor)+"."+wxString::Format("%d",Build)+"."+wxString::Format("%d",Revision)+"\n");
}  // CBeremizProjectManagerMainFrame::OnShowPluginVersionMenu
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::OnOptionsCloseEditors (wxCommandEvent& WXUNUSED(event))
{
	if (Project==0) return;

	Project->CloseEditor(-1);
}  // CBeremizProjectManagerMainFrame::OnOptionsCloseEditors
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::SaveManagerConfiguration (void)
{
	wxString FilePath;
    FILE* ConfigFile;
    wxString Path2Tools;
    //char Path2Tools[512];

	FilePath="config.xml";
	ConfigFile=fopen (FilePath, "wt");
	if (ConfigFile==0)
	{
		wxMessageBox("Can not save Beremiz Project Manager configuration", "Configuration file error", wxOK+wxICON_ERROR);
		return;
	}

	fprintf (ConfigFile, "<?xml version='1.0' encoding='utf-8'?>\n");
	fprintf (ConfigFile, "<beremiz_project_manager_config>\n");

    Path2Tools = "  <basefiles path=\""+TargetsDirectory+"\"/>\n";
    fprintf (ConfigFile, Path2Tools);

	if (CleanWithFramework) fprintf (ConfigFile, "  <build_options clean_framework=\"1\" />\n");
	else fprintf (ConfigFile, "  <build_options clean_framework=\"0\" />\n");

	fprintf (ConfigFile, "</beremiz_project_manager_config>\n");

	fclose (ConfigFile);
}  // CBeremizProjectManagerMainFrame::SaveManagerConfiguration
// -----------------------------------------------------

void CBeremizProjectManagerMainFrame::LoadManagerConfiguration (void)
{
	wxString ConfigPath;
    wxXmlDocument doc;
	wxXmlNode* RootNode;
    wxXmlNode* TopNode;
	wxString ValueStr;

	// Set default values
	CleanWithFramework = false;
	TargetsDirectory = "";

	ConfigPath="config.xml";

	// We have to check first if config file exists, otherwise doc.Load triggers an exception
	// and displays a warning the first time the application is launched
	if (!wxFileExists(ConfigPath)) return;

	if (doc.Load(ConfigPath))
	{
        RootNode=doc.GetRoot();
        if (RootNode->GetName() == "beremiz_project_manager_config")
        {
            TopNode=RootNode->GetChildren();
			do
			{
				if (TopNode->GetName() == "basefiles")
				{
					TargetsDirectory = TopNode->GetAttribute("path", "");
				}
				else if (TopNode->GetName() == "build_options")
				{
					TopNode->GetAttribute ("clean_framework", &ValueStr);
					if (ValueStr == "1") CleanWithFramework = true;
				}

				TopNode = TopNode->GetNext();
			} while (TopNode!=0);
        }
	}
}  // CBeremizProjectManagerMainFrame::LoadManagerConfiguration
// -----------------------------------------------------
