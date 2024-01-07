/////////////////////////////////////////////////////////////////////////////
// Name:        ProjectControl.cpp
// Purpose:     Beremiz Project Manager project management functions
// Author:      Benoit BOUCHEZ
// Created:     12/05/2022
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

#include "ProjectControl.h"
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/file.h>
#include <wx/xml/xml.h>

CBeremizProject::CBeremizProject()
{
	TargetPlugin = 0;		// Must be done BEFORE call to CleanProject() as it will check this pointer
	this->CleanProject();
	ProjectPath="";
	ProjectName="";
	TargetsPath = "";

	// TODO : this has to be enhanced : LoadProject will delete the target plugin
	// We should instantiate the plugin only when we need it, not when the project is instanciated
	TargetPlugin = new TargetPluginClass ();
	if (TargetPlugin == 0)
		wxMessageBox ("Target plugin instanciation failed", "CBeremizProject instanciation failure", wxOK+wxICON_ERROR);
}  // CBeremizProject::CBeremizProject
// -----------------------------------------------------

CBeremizProject::~CBeremizProject()
{
	this->CleanProject();
}  // CBeremizProject::~CBeremizProject
// -----------------------------------------------------

void CBeremizProject::CleanProject (void)
{
	TargetLibraryName = "";
	DataHasChanged=false;

	if (TargetPlugin)
	{
		TargetPlugin->Terminate();
		delete TargetPlugin;
		TargetPlugin = 0;
	}
	TargetPluginLoaded = false;
}  // CBeremizProject::CleanProject
// -----------------------------------------------------

void CBeremizProject::SetPathAndName (wxString ProjectFolder)
{
	this->ProjectPath = ProjectFolder;
	this->ProjectName = this->ProjectPath.AfterLast(wxFILE_SEP_PATH);
}  // CBeremizProject::SetPathAndName
// -----------------------------------------------------

void CBeremizProject::SetTargetsPath (wxString Path)
{
	this->TargetsPath = Path;
}  // CBeremizProject::SetTargetsPath
// -----------------------------------------------------

int CBeremizProject::LoadProject (void)
{
	wxXmlDocument doc;
	wxXmlNode* RootNode;
	wxString TestString;
	wxXmlNode* TopNode;
	wxXmlNode* CPUChildNode;
	wxString TargetLibrary;
	wxString ProjectFilePath;
	int TargetProjectLoadRes;

	this->CleanProject();		// This will remove any previously created target plugin

	TargetPlugin = new TargetPluginClass ();
	if (TargetPlugin == 0)
		wxMessageBox ("Target plugin instanciation failed", "CBeremizProject instanciation failure", wxOK+wxICON_ERROR);

	ProjectFilePath=this->ProjectPath+"/project.xml";

	if (!doc.Load(ProjectFilePath)) return ERR_TARGET_PLUGIN_FILE_ERROR;  // File does not exist or can not be loaded

	// Check that the XML file is a Beremiz project file
	RootNode=doc.GetRoot();
	if (RootNode->GetName() != "project") return ERR_TARGET_PLUGIN_INVALID_FILE;  // Not a Beremiz project file ?
	RootNode->GetAttribute ("type", &TestString);
	if (TestString != "beremiz") return ERR_TARGET_PLUGIN_INVALID_FILE;
	// Check that Beremiz project file version is supported
	RootNode->GetAttribute ("version", &TestString);
	if (TestString != "1") return ERR_TARGET_PLUGIN_INVALID_FILE_VERSION;   // Project file version is not supported

	// Let's iterate now over all entries...
	TopNode = RootNode->GetChildren();
	do
	{
		if (TopNode->GetName()=="cpu")
		{
			TopNode->GetAttribute ("type", &TargetLibrary);

			CPUChildNode = TopNode->GetChildren();
			do 
			{
				CPUChildNode=CPUChildNode->GetNext();
			} while (CPUChildNode != 0);
		}
		else if (TopNode->GetName()=="bus")
		{
		}
		else if (TopNode->GetName()=="iomodules")
		{
		}

		TopNode=TopNode->GetNext();
	} while (TopNode!=0);

	SetTargetPlugin (TargetLibrary);		// If this fails, TargetPluginLoaded will stay false
	if (TargetPluginLoaded)
	{
		TargetPlugin->SetProjectPath (this->ProjectPath, 0);
		
		TargetProjectLoadRes = TargetPlugin->LoadTargetProjectData();
		if (TargetProjectLoadRes!=0)
			return TargetProjectLoadRes;		// Error while loading target specific
	}
	
	return TARGET_PLUGIN_NO_ERROR;
}  // CBeremizProject::LoadProject
// -----------------------------------------------------
	
int CBeremizProject::SaveProject (void)
{
	FILE* ProjectFile;
	int TargetProjectSaveRes;

	ProjectFile=fopen (this->ProjectPath+"/project.xml", "wt");
	if (ProjectFile==0) return ERR_TARGET_PLUGIN_FILE_ERROR;		// Can not create project file

	// Save XML header and create top level tag
	fprintf (ProjectFile, "<?xml version='1.0' encoding='utf-8'?>\n");
	fprintf (ProjectFile, "<project type=\"beremiz\" version=\"1\">\n");

	// CPU type
	fprintf (ProjectFile, "  <cpu type=\""+this->TargetLibraryName+"\">\n");

	fprintf (ProjectFile, "    <ioconfig>\n");
	fprintf (ProjectFile, "    </ioconfig>\n");

	fprintf (ProjectFile, "  </cpu>\n");

	// Commmunication bus
	fprintf (ProjectFile, "  <bus>\n");
	fprintf (ProjectFile, "  </bus>\n");

	// Remote I/O modules
	fprintf (ProjectFile, "  <iomodules>\n");
	fprintf (ProjectFile, "  </iomodules>\n");

	// Close project tag
	fprintf (ProjectFile, "</project>\n");

	fclose (ProjectFile);

	this->DataHasChanged = false;

	if (TargetPluginLoaded)
	{
		TargetProjectSaveRes = TargetPlugin->SaveTargetProjectData();
		if (TargetProjectSaveRes!=0)
			return TargetProjectSaveRes;		// Error while saving target specific data
	}

	return TARGET_PLUGIN_NO_ERROR;
}  // CBeremizProject::SaveProject
// -----------------------------------------------------

void CBeremizProject::SetTargetPlugin (wxString PluginName)
{
	int ResPlugin;

	if (this->TargetPluginLoaded) return;		// Can not change the target if already selected
	
	this->TargetLibraryName = PluginName;
	ResPlugin = TargetPlugin->LoadPlugin (PluginName);
	if (ResPlugin!=0)
	{
		wxMessageBox ("An error occured while loading target plugin", "Load target plugin", wxOK+wxICON_WARNING);
	}
	else TargetPluginLoaded = true;

	// This call is mandatory to initialize the framework used in the plugin
	if (TargetPluginLoaded)
	{
		TargetPlugin->Initialize();
		TargetPlugin->SetProjectPath (this->ProjectPath, 0);		// TODO : set encoding (just C for now)
		TargetPlugin->SetTargetsPath (this->TargetsPath, 0);		// TODO : set encoding (just C for now)
	}
}  // CBeremizProject::SetTargetPlugin
// -----------------------------------------------------

wxString CBeremizProject::GetCPUDisplayName (void)
{
	char CPUName[TARGET_PLUGIN_STRING_SIZE];
	wxString ReturnString;

	if ((TargetPluginLoaded==false)||(TargetPlugin==0)) return ("Unknown CPU name");
	TargetPlugin->GetPluginName (&CPUName[0]);
	ReturnString = CPUName;
	return ReturnString;
}  // CBeremizProject::GetCPUDisplayName
// -----------------------------------------------------

wxString CBeremizProject::GetProjectPath (void)
{
	return this->ProjectPath;
}  // CBeremizProject::GetProjectPath
// -----------------------------------------------------

wxString CBeremizProject::GetProjectName (void)
{
	return this->ProjectName;
}  // CBeremizProject::GetProjectName
// -----------------------------------------------------

int CBeremizProject::ProcessBeremizC_POU (void)
{
	wxString BuildDir;
	int EditPOUSResult;

	BuildDir = ProjectPath+"/build/";

	// Check first that Resource1.c exists (must have been generated first from Beremiz)
	if (wxFileExists (BuildDir+"Resource1.c")==false) return -32768;

	// For now, we restrict the user to have only one resource and it must be called Resource1 in Beremiz
	wxCopyFile (BuildDir+"Resource1.c", BuildDir+"Resource1_Temp.c");			// Rename file

	// Edit the .c file containing #include "pous.c"
	// Resource1_Temp.c is edited and renamed into Resource1.c
	EditPOUSResult = POU_Includer (BuildDir+"Resource1_Temp.c", BuildDir+"Resource1.c");
	if (EditPOUSResult!=0) return EditPOUSResult;

	// Delete Resource1_Temp.c
	wxRemoveFile (BuildDir+"Resource1_Temp.c");

	// Rename POUS.c into POUS2.h
	wxCopyFile (BuildDir+"POUS.c", BuildDir+"POUS2.h");

	return 0;
}  // ProcessBeremizC_POU
// -----------------------------------------------------

int CBeremizProject::POU_Includer (wxString InFileName, wxString OutFileName)
{
	FILE* InFile;
	FILE* OutFile;
	char line[1024];

	InFile = fopen (InFileName, "rt");
	if (InFile == 0) return -1;

	OutFile = fopen (OutFileName, "wt");
	if (OutFile == 0) 
	{
		fclose (InFile);
		return -2;
	}

	// Processing loop
	while (fgets(line, sizeof(line), InFile))
	{
		// Check if we find the #include "pous.c"
		if (strcmp (line, "#include \"POUS.c\"\n")==0)
		{
			// If line is found, replace it
			strcpy (line, "#include \"POUS2.h\"\n");
		}
		
		fprintf (OutFile, "%s", line);
	}

	fclose (InFile);
	fclose (OutFile);

	return 0;
}  // CBeremizProject::POU_Includer
// -----------------------------------------------------------

int CBeremizProject::CreateBeremizProjectFiles (void)
{
	if (!TargetPluginLoaded) return ERR_TARGET_PLUGIN_MISSING_FUNCTION;

	return TargetPlugin->CreateBeremizProjectFiles ();
}  // CBeremizProject::CreateBeremizProjectFiles
// -----------------------------------------------------------

int CBeremizProject::GenerateTargetFramework (void)
{
	if (!TargetPluginLoaded) return ERR_TARGET_PLUGIN_MISSING_FUNCTION;

	return TargetPlugin->GenerateTargetFramework ();
}  // CBeremizProject::GenerateTargetFramework
// -----------------------------------------------------------

int CBeremizProject::CopyPLCFilesForCompilation (void)
{
	if (!TargetPluginLoaded) return ERR_TARGET_PLUGIN_MISSING_FUNCTION;

	return TargetPlugin->CopyPLCFilesForCompilation ();
}  // CBeremizProject::CopyPLCFilesForCompilation
// -----------------------------------------------------------

int CBeremizProject::GenerateIOConfigurationFiles (void)
{
	if (!TargetPluginLoaded) return ERR_TARGET_PLUGIN_MISSING_FUNCTION;

	return TargetPlugin->GenerateIOConfigurationFiles ();
}  // CBeremizProject::GenerateIOConfigurationFiles
// -----------------------------------------------------------

int CBeremizProject::OpenEditor (wxWindow* Parent, unsigned int EditorIndex)
{
	if (!TargetPluginLoaded) return ERR_TARGET_PLUGIN_MISSING_FUNCTION;

	return TargetPlugin->OpenEditor (Parent, EditorIndex);
}  // CBeremizProject::OpenEditor
// -----------------------------------------------------------

void CBeremizProject::CloseEditor (int EditorIndex)
{
	if (TargetPluginLoaded)
	{
		TargetPlugin->CloseEditor (EditorIndex);
	}
}  // CBeremizProject::OpenEditor
// -----------------------------------------------------------

int CBeremizProject::StartPLC (void)
{
	if (TargetPluginLoaded==false)
		return ERR_TARGET_PLUGIN_MISSING_FUNCTION;

	if (TargetPlugin->IsOptionSupported(TP_OPTION_TARGET_START) == 1)
	{
		// TODO : this must be executed by the plugin or RemoteTarget shall be provided by the plugin
		/*
		if (Supervisor)
			return Supervisor->StartPLC (this->RemoteTarget);
		*/
	}

	return ERR_TARGET_PLUGIN_NON_SUPPORTED_FEATURE;
}  // CBeremizProject::StartPLC
// -----------------------------------------------------------

int CBeremizProject::StopPLC (void)
{
	if (TargetPluginLoaded==false)
		return ERR_TARGET_PLUGIN_MISSING_FUNCTION;

	if (TargetPlugin->IsOptionSupported(TP_OPTION_TARGET_STOP) == 1)
	{
		// TODO : this must be executed by the plugin or RemoteTarget shall be provided by the plugin
		/*
		if (Supervisor)
			return Supervisor->StopPLC(this->RemoteTarget);
		*/
	}

	return ERR_TARGET_PLUGIN_NON_SUPPORTED_FEATURE;
}  // CBeremizProject::StopPLC
// -----------------------------------------------------------

int CBeremizProject::StartCompilation (void)
{
	if (TargetPluginLoaded==false)
		return ERR_TARGET_PLUGIN_MISSING_FUNCTION;

	if (TargetPlugin->IsOptionSupported (TP_OPTION_PLUGIN_COMPILER)==1)
	{  // Compilation by plugin is supported
		return (TargetPlugin->StartCompilation());
	}
	
	return ERR_TARGET_PLUGIN_NON_SUPPORTED_FEATURE;			// Error : compilation can not be started
}  // CBeremizProject::StartCompilation
// -----------------------------------------------------------

int CBeremizProject::SetAutomaticPLCStart (bool ShallStart)
{
	int Supported;

	if (TargetPluginLoaded==false)
		return ERR_TARGET_PLUGIN_MISSING_FUNCTION;

	Supported = TargetPlugin->IsOptionSupported (TP_OPTION_TARGET_AUTO_START);

	if (Supported==1)
	{  // Plugin confirms that this target supports the function
		// TODO : this must be executed by the plugin or RemoteTarget shall be provided by the plugin
		/*
  		if (Supervisor)
			return Supervisor->SetAutomaticPLCStart (this->RemoteTarget, ShallStart);
		*/
	}

	return ERR_TARGET_PLUGIN_NON_SUPPORTED_FEATURE;
}  // CBeremizProject::SetAutomaticPLCStart
// -----------------------------------------------------------

int CBeremizProject::GetCompilerMessages (char* LogBuffer)
{
	if (TargetPluginLoaded==false)
		return ERR_TARGET_PLUGIN_MISSING_FUNCTION;

	return TargetPlugin->GetCompilerMessages (LogBuffer);
}  // CBeremizProject::GetCompilerMessages
// -----------------------------------------------------------

bool CBeremizProject::HasChanged (void)
{
	if (this->DataHasChanged) return true;
	if (TargetPluginLoaded)
	{
		if (TargetPlugin->DataHasChanged()) return true;
	}

	return false;
}  // CBeremizProject::HasChanged
// -----------------------------------------------------------
