/////////////////////////////////////////////////////////////////////////////
// Name:        TargetPluginClass.cpp
// Purpose:     Class to import target plugin DLL for Beremiz Project Manager
// Author:      Benoit BOUCHEZ
// Created:     05/07/2022
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

#include "TargetPluginClass.h"
#ifdef __TARGET_LINUX__
#include <dlfcn.h>
#endif

#ifdef __TARGET_LINUX__
void (*TP_GetPluginName)(char* Name);
void (*TP_GetPluginVersion)(uint32_t* Major, uint32_t* Minor, uint32_t* Build, uint32_t* Revision);

void (*TP_Initialize)(void);
void (*TP_Terminate)(void);

void (*TP_SetProjectPath)(char* Path, int32_t StrEncoding);
void (*TP_SetTargetsPath)(char* Path, int32_t StrEncoding));

int32_t (*TP_LoadTargetProjectData)(void);
int32_t (*TP_SaveTargetProjectData)(void);
int32_t (*TP_DataHasChanged)(void);

int32_t (*TP_CreateBeremizProjectFiles)(void);
int32_t (*TP_GenerateTargetFramework)(void);
int32_t (*TP_CopyPLCFilesForCompilation)(void);
int32_t (*TP_GenerateIOConfigurationFiles)(void);
int32_t (*TP_CleanForBuild)(void);
int32_t (*TP_StartCompilation)(void);
int32_t (*TP_GetCompilerMessages)(char* Msg);

int32_t (*TP_OpenEditor)(void* Parent, uint32_t EditorIndex);
int32_t (*TP_CloseEditor)(int32_t EditorIndex);

uint32_t (*TP_GetNumberOfEditors)(void);
void (*TP_GetEditorLabel)(uint32_t EditorIndex, char* EditorName, int32_t* TreeIconIndex);

int32_t (*TP_IsOptionSupported)(uint32_t Option);
#endif

TargetPluginClass::TargetPluginClass ()
{
#ifdef __TARGET_WIN__
	hGetProcIDDLL = 0;
#endif
#ifdef __TARGET_LINUX__
    dlibHandle = 0;
#endif
	this->CleanFunctionEntries();
}  // TargetPluginClass::TargetPluginClass
// -----------------------------------------------------

TargetPluginClass::~TargetPluginClass ()
{
#ifdef __TARGET_WIN__
	if (hGetProcIDDLL!=0)
	{
		FreeLibrary (hGetProcIDDLL);
		hGetProcIDDLL = 0;
	}
#endif // __TARGET_WIN__
#ifdef __TARGET_LINUX__
    if (dlibHandle)
    {
        dlclose (dlibHandle);
        dlibHandle = 0;
    }
#endif
}  // TargetPluginClass::~TargetPluginClass
// -----------------------------------------------------

void TargetPluginClass::CleanFunctionEntries (void)
{
	TP_GetPluginName=0;
	TP_GetPluginVersion=0;

	TP_Initialize=0;
	TP_Terminate=0;

	TP_SetProjectPath=0;
	TP_SetTargetsPath=0;

	TP_LoadTargetProjectData=0;
	TP_SaveTargetProjectData=0;
	TP_DataHasChanged=0;

	TP_OpenEditor=0;
	TP_CloseEditor=0;

	TP_CreateBeremizProjectFiles=0;
	TP_GenerateTargetFramework=0;
	TP_CopyPLCFilesForCompilation=0;
	TP_GenerateIOConfigurationFiles=0;
	TP_CleanForBuild=0;
	TP_StartCompilation=0;
	TP_GetCompilerMessages=0;

	TP_GetNumberOfEditors=0;
	TP_GetEditorLabel=0;

	TP_IsOptionSupported=0;
}  // TargetPluginClass::CleanFunctionEntries
// -----------------------------------------------------

int TargetPluginClass::LoadPlugin (wxString PluginPath)
{
	bool AllFunctionsLoaded = true;
	wxString ErrorTitle;

#ifdef __TARGET_WIN__
	// if there is already a plugin associated to the class, free it
	if (hGetProcIDDLL!=0)
	{
		FreeLibrary (hGetProcIDDLL);
		hGetProcIDDLL = 0;
		this->CleanFunctionEntries();
	}

	// Try to load the DLL into the system
	hGetProcIDDLL = LoadLibraryA(PluginPath+".dll");
	if (hGetProcIDDLL == 0) return GetLastError();

	// Instanciate all functions from the plugin
	TP_GetPluginName = (TP_GetPluginNameFunc)GetProcAddress(hGetProcIDDLL, "TP_GetPluginName");
	TP_GetPluginVersion = (TP_GetPluginVersionFunc)GetProcAddress(hGetProcIDDLL, "TP_GetPluginVersion");

	TP_Initialize = (TP_InitializeFunc)GetProcAddress(hGetProcIDDLL, "TP_Initialize");
	TP_Terminate = (TP_TerminateFunc)GetProcAddress(hGetProcIDDLL, "TP_Terminate");

	TP_SetProjectPath = (TP_SetProjectPathFunc)GetProcAddress(hGetProcIDDLL, "TP_SetProjectPath");
	TP_SetTargetsPath = (TP_SetTargetsPathFunc)GetProcAddress(hGetProcIDDLL, "TP_SetTargetsPath");

	TP_LoadTargetProjectData = (TP_LoadTargetProjectDataFunc)GetProcAddress(hGetProcIDDLL, "TP_LoadTargetProjectData");
	TP_SaveTargetProjectData = (TP_SaveTargetProjectDataFunc)GetProcAddress(hGetProcIDDLL, "TP_SaveTargetProjectData");
	TP_DataHasChanged = (TP_DataHasChangedFunc)GetProcAddress(hGetProcIDDLL, "TP_DataHasChanged");

	TP_OpenEditor = (TP_OpenEditorFunc)GetProcAddress(hGetProcIDDLL, "TP_OpenEditor");
	TP_CloseEditor = (TP_CloseEditorFunc)GetProcAddress(hGetProcIDDLL, "TP_CloseEditor");

	TP_GenerateTargetFramework = (TP_GenerateTargetFrameworkFunc)GetProcAddress(hGetProcIDDLL, "TP_GenerateTargetFramework");
	TP_CopyPLCFilesForCompilation = (TP_CopyPLCFilesForCompilationFunc)GetProcAddress(hGetProcIDDLL, "TP_CopyPLCFilesForCompilation");
	TP_CreateBeremizProjectFiles = (TP_CreateBeremizProjectFilesFunc)GetProcAddress(hGetProcIDDLL, "TP_CreateBeremizProjectFiles");
	TP_GenerateIOConfigurationFiles = (TP_GenerateIOConfigurationFilesFunc)GetProcAddress(hGetProcIDDLL, "TP_GenerateIOConfigurationFiles");
	TP_CleanForBuild = (TP_CleanForBuildFunc)GetProcAddress(hGetProcIDDLL, "TP_CleanForBuild");
	TP_StartCompilation = (TP_StartCompilationFunc)GetProcAddress(hGetProcIDDLL, "TP_StartCompilation");
	TP_GetCompilerMessages = (TP_GetCompilerMessagesFunc)GetProcAddress (hGetProcIDDLL, "TP_GetCompilerMessages");

	TP_GetNumberOfEditors = (TP_GetNumberOfEditorsFunc)GetProcAddress(hGetProcIDDLL, "TP_GetNumberOfEditors");
	TP_GetEditorLabel = (TP_GetEditorLabelFunc)GetProcAddress(hGetProcIDDLL, "TP_GetEditorLabel");

	TP_IsOptionSupported = (TP_IsOptionSupportedFunc)GetProcAddress(hGetProcIDDLL, "TP_IsOptionSupported");
#endif

#ifdef __TARGET_LINUX__
	// if there is already a plugin associated to the class, free it
    if (dlibHandle)
    {
        dlclose (dlibHandle);
        dlibHandle = 0;
        this->CleanFunctionEntries();
    }

    dlibHandle = dlopen ("./"+PluginPath+".so", RTLD_NOW);
    if (dlibHandle == 0)
        return ERR_TARGET_PLUGIN_MISSING_FUNCTION;

	*(void**)(&TP_GetPluginName) = dlsym(dlibHandle, "TP_GetPluginName");
	*(void**)(&TP_GetPluginVersion) = dlsym(dlibHandle, "TP_GetPluginVersion");

	*(void**)(&TP_Initialize) = dlsym(dlibHandle, "TP_Initialize");
	*(void**)(&TP_Terminate) = dlsym(dlibHandle, "TP_Terminate");

    *(void**)(&TP_SetProjectPath) = dlsym(dlibHandle, "TP_SetProjectPath");
	*(void**)(&TP_SetTargetsPath) = dlsym(dlibHandle, "TP_SetTargetsPath");

	*(void**)(&TP_LoadTargetProjectData) = dlsym(dlibHandle, "TP_LoadTargetProjectData");
	*(void**)(&TP_SaveTargetProjectData) = dlsym(dlibHandle, "TP_SaveTargetProjectData");
	*(void**)(&TP_DataHasChanged) = dlsym(dlibHandle, "TP_DataHasChanged");

	*(void**)(&TP_OpenEditor) = dlsym(dlibHandle, "TP_OpenEditor");
	*(void**)(&TP_CloseEditor) = dlsym(dlibHandle, "TP_CloseEditor");

	*(void**)(&TP_GenerateTargetFramework) = dlsym(dlibHandle, "TP_GenerateTargetFramework");
	*(void**)(&TP_CopyPLCFilesForCompilation) = dlsym(dlibHandle, "TP_CopyPLCFilesForCompilation");
	*(void**)(&TP_CreateBeremizProjectFiles) = dlsym(dlibHandle, "TP_CreateBeremizProjectFiles");
	*(void**)(&TP_GenerateIOConfigurationFiles) = dlsym(dlibHandle, "TP_GenerateIOConfigurationFiles");
	*(void**)(&TP_CleanForBuild) = dlsym(dlibHandle, "TP_CleanForBuild");
	*(void**)(&TP_StartCompilation) = dlsym(dlibHandle, "TP_StartCompilation");
	*(void**)(&TP_GetCompilerMessages) = dlsym(dlibHandle, "TP_GetCompilerMessages");

	*(void**)(&TP_GetNumberOfEditors) = dlsym(dlibHandle, "TP_GetNumberOfEditors");
	*(void**)(&TP_GetEditorLabel) = dlsym(dlibHandle, "TP_GetEditorLabel");

	*(void**)(&TP_IsOptionSupported) = dlsym(dlibHandle, "TP_IsOptionSupported");
#endif

	ErrorTitle = "Target plugin loading failed";

	// Check that all functions have been retrieved properly
	if (TP_GetPluginName==0) 
	{
		wxMessageBox ("TP_GetPluginName function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_GetPluginVersion==0)
	{
		wxMessageBox ("TP_GetPluginVersion function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_Initialize==0)
	{
		wxMessageBox ("TP_Initialize function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_Terminate==0)
	{
		wxMessageBox ("TP_Terminate function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}
		
	if (TP_SetProjectPath==0)
	{
		wxMessageBox ("TP_SetProjectPath function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_SetTargetsPath==0)
	{
		wxMessageBox ("TP_SetTargetsPath function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_LoadTargetProjectData==0)
	{
		wxMessageBox ("TP_LoadTargetProjectData function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}


	if (TP_SaveTargetProjectData==0)
	{
		wxMessageBox ("TP_SaveTargetProjectData function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_DataHasChanged==0)
	{
		wxMessageBox ("TP_DataHasChanged function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_OpenEditor==0)
	{
		wxMessageBox ("TP_OpenEditor function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_CloseEditor==0)
	{
		wxMessageBox ("TP_CloseEditor function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_GenerateTargetFramework==0)
	{
		wxMessageBox ("TP_GenerateTargetFramework function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_CopyPLCFilesForCompilation==0)
	{
		wxMessageBox ("TP_CopyPLCFilesForCompilation function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_CreateBeremizProjectFiles==0)
	{
		wxMessageBox ("TP_CreateBeremizProjectFiles function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_GenerateIOConfigurationFiles==0)
	{
		wxMessageBox ("TP_GenerateIOConfigurationFiles function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_CleanForBuild==0)
	{
		wxMessageBox ("TP_CleanForBuild function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_StartCompilation==0)
	{
		wxMessageBox ("TP_StartCompilation function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_GetCompilerMessages==0)
	{
		wxMessageBox ("TP_GetCompilerMessages function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_GetNumberOfEditors==0)
	{
		wxMessageBox ("TP_GetNumberOfEditors function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_GetEditorLabel==0)
	{
		wxMessageBox ("TP_GetEditorLabel function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (TP_IsOptionSupported==0)
	{
		wxMessageBox ("TP_IsOptionSupported function not found in plugin", ErrorTitle, wxOK+wxICON_ERROR);
		AllFunctionsLoaded=false;
	}

	if (AllFunctionsLoaded==false) return ERR_TARGET_PLUGIN_MISSING_FUNCTION;

	return 0;
}  // TargetPluginClass::LoadPlugin
// -----------------------------------------------------

void TargetPluginClass::GetPluginName (char* Name)
{
	if (TP_GetPluginName)
		TP_GetPluginName (Name);
}  // TargetPluginClass::GetPluginName
// -----------------------------------------------------

void TargetPluginClass::GetPluginVersion (uint32_t* Major, uint32_t* Minor, uint32_t* Build, uint32_t* Revision)
{
	if (TP_GetPluginVersion)
		TP_GetPluginVersion (Major, Minor, Build, Revision);
}  // TargetPluginClass::GetPluginVersion
// -----------------------------------------------------

void TargetPluginClass::Initialize (void)
{
	if (TP_Initialize)
		TP_Initialize();
}  // TargetPluginClass::Close
// -----------------------------------------------------

void TargetPluginClass::Terminate (void)
{
	if (TP_Terminate)
		TP_Terminate();
}  // TargetPluginClass::Close
// -----------------------------------------------------

void TargetPluginClass::SetProjectPath (wxString Path, int32_t StrEncoding)
{
	char CPath[1024];

	if (TP_SetProjectPath)
	{
		strncpy (CPath, Path.mb_str(), sizeof(CPath));
		TP_SetProjectPath (CPath, StrEncoding);		// TODO : check if encoding is useful as we pass a C string...
	}
}  // TargetPluginClass::SetProjectPath
// -----------------------------------------------------

void TargetPluginClass::SetTargetsPath (wxString Path, int32_t StrEncoding)
{
	char CPath[1024];

	if (TP_SetTargetsPath)
	{
		strncpy (CPath, Path.mb_str(), sizeof(CPath));
		TP_SetTargetsPath (CPath, StrEncoding);		// TODO : check if encoding is useful as we pass a C string...
	}
}  // TargetPluginClass::SetProjectPath
// -----------------------------------------------------

/*
void TargetPluginClass::SetRemoteTargetProperties (wxString& Login, wxString& Password, wxString& TargetAddress, wxString& CompilationPath, int32_t StrEncoding)
{
	char CLogin[1024];
	char CPassword[1024];
	char CTarget[1024];
	char CPath[1024];

	if (TP_SetRemoteTargetProperties)
	{
		strncpy (CLogin, Login.mb_str(), sizeof(CLogin));
		strncpy (CPassword, Password.mb_str(), sizeof(CPassword));
		strncpy (CTarget, TargetAddress.mb_str(), sizeof(CTarget));
		strncpy (CPath, CompilationPath.mb_str(), sizeof(CPath));

		TP_SetRemoteTargetProperties (CLogin, CPassword, CTarget, CPath, StrEncoding);
	}
}  // TargetPluginClass::SetRemoteTargetProperties
// -----------------------------------------------------
*/

int TargetPluginClass::LoadTargetProjectData (void)
{
	if (TP_LoadTargetProjectData)
		return TP_LoadTargetProjectData ();

	return ERR_TARGET_PLUGIN_MISSING_FUNCTION;
}  // TargetPluginClass::LoadProjectSpecificData
// -----------------------------------------------------

int TargetPluginClass::SaveTargetProjectData (void)
{
	if (TP_SaveTargetProjectData)
		return TP_SaveTargetProjectData();

	return ERR_TARGET_PLUGIN_MISSING_FUNCTION;
}  // TargetPluginClass::SaveTargetProjectData
// -----------------------------------------------------

int TargetPluginClass::OpenEditor (wxWindow* Parent, uint32_t EditorIndex)
{
	if (TP_OpenEditor)
		return TP_OpenEditor (Parent, EditorIndex);

	return ERR_TARGET_PLUGIN_MISSING_FUNCTION;
}  // TargetPluginClass::OpenEditor
// -----------------------------------------------------

void TargetPluginClass::CloseEditor (int32_t EditorIndex)
{
	if (TP_CloseEditor)
		TP_CloseEditor (EditorIndex);
}  // TargetPluginClass::CloseEditor
// -----------------------------------------------------

int TargetPluginClass::CreateBeremizProjectFiles (void)
{
	if (TP_CreateBeremizProjectFiles)
		return TP_CreateBeremizProjectFiles();

	return ERR_TARGET_PLUGIN_MISSING_FUNCTION;
}  // TargetPluginClass::CreateBeremizProjectFiles
// -----------------------------------------------------

int TargetPluginClass::GenerateTargetFramework (void)
{
	if (TP_GenerateTargetFramework)
	{
		return TP_GenerateTargetFramework();
	}

	return ERR_TARGET_PLUGIN_MISSING_FUNCTION;
}  // TargetPluginClass::GenerateTargetFramework
// -----------------------------------------------------

int TargetPluginClass::CopyPLCFilesForCompilation (void)
{
	if (TP_CopyPLCFilesForCompilation)
	{
		return TP_CopyPLCFilesForCompilation();
	}

	return ERR_TARGET_PLUGIN_MISSING_FUNCTION;
}  // TargetPluginClass::CopyPLCFilesForCompilation
// -----------------------------------------------------

int TargetPluginClass::GenerateIOConfigurationFiles (void)
{
	if (TP_GenerateIOConfigurationFiles)
		return TP_GenerateIOConfigurationFiles ();

	return ERR_TARGET_PLUGIN_MISSING_FUNCTION;
}  // // TargetPluginClass::GenerateIOConfigurationFiles
// -----------------------------------------------------

int TargetPluginClass::CleanForBuild (void)
{
	if (TP_CleanForBuild)
		return (TP_CleanForBuild());

	return ERR_TARGET_PLUGIN_MISSING_FUNCTION;
}  // TargetPluginClass::CleanForBuild
// -----------------------------------------------------

int TargetPluginClass::StartCompilation (void)
{
	if (TP_StartCompilation)
		return (TP_StartCompilation());

	return ERR_TARGET_PLUGIN_MISSING_FUNCTION;
}  // TargetPluginClass::StartCompilation
// -----------------------------------------------------

int TargetPluginClass::GetNumberOfEditors (void)
{
	if (TP_GetNumberOfEditors)
		return TP_GetNumberOfEditors();

	return ERR_TARGET_PLUGIN_MISSING_FUNCTION;
}  // TargetPluginClass::GetNumberOfEditors
// -----------------------------------------------------

void TargetPluginClass::GetEditorLabel (int EditorIndex, char* EditorName, int32_t* TreeIconIndex)
{
	if (TP_GetEditorLabel)
		TP_GetEditorLabel (EditorIndex, EditorName, TreeIconIndex);
}  // TargetPluginClass::GetEditorLabel
// -----------------------------------------------------

bool TargetPluginClass::DataHasChanged (void)
{
	if (TP_DataHasChanged)
	{
		if (TP_DataHasChanged()) return true;
		else return false;
	}

	return false;
}  // TargetPluginClass::DataHasChanged
// -----------------------------------------------------

int TargetPluginClass::IsOptionSupported (unsigned int Option)
{
	if (TP_IsOptionSupported)
	{
		return TP_IsOptionSupported (Option);
	}

	return -1;		// Act as if plugin says option is unknown
}  // TargetPluginClass::IsOptionSupported
// -----------------------------------------------------

int TargetPluginClass::GetCompilerMessages (char* Msg)
{
	if (TP_GetCompilerMessages)
	{
		return TP_GetCompilerMessages (Msg);
	}
	
	return ERR_TARGET_PLUGIN_MISSING_FUNCTION;
}  // TargetPluginClass::TP_GetCompilerMessages
// -----------------------------------------------------
