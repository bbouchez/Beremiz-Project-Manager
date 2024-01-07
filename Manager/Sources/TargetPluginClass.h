/////////////////////////////////////////////////////////////////////////////
// Name:        TargetPluginClass.h
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

#ifndef __TARGETPLUGINCLASS_H__
#define __TARGETPLUGINCLASS_H__

#include "wx/wxprec.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <stdint.h>
#include "BeremizProjectManager_SDK_Defs.h"

// DLL imported functions prototypes
#ifdef __TARGET_WIN__
typedef void (__cdecl *TP_GetPluginNameFunc)(char* Name);
typedef void (__cdecl *TP_GetPluginVersionFunc)(uint32_t* Major, uint32_t* Minor, uint32_t* Build, uint32_t* Revision);

typedef void (__cdecl *TP_InitializeFunc)(void);
typedef void (__cdecl *TP_TerminateFunc)(void);

typedef void (__cdecl *TP_SetProjectPathFunc)(char* Path, int32_t StrEncoding);
typedef void (__cdecl *TP_SetTargetsPathFunc)(char* Path, int32_t StrEncoding);

typedef int32_t (__cdecl *TP_LoadTargetProjectDataFunc)(void);
typedef int32_t (__cdecl *TP_SaveTargetProjectDataFunc)(void);
typedef int32_t (__cdecl *TP_DataHasChangedFunc)(void);

typedef int32_t (__cdecl *TP_CreateBeremizProjectFilesFunc)(void);
typedef int32_t (__cdecl *TP_GenerateTargetFrameworkFunc)(void);
typedef int32_t (__cdecl *TP_CopyPLCFilesForCompilationFunc)(void);
typedef int32_t (__cdecl *TP_GenerateIOConfigurationFilesFunc)(void);
typedef int32_t (__cdecl *TP_CleanForBuildFunc)(void);
typedef int32_t (__cdecl *TP_StartCompilationFunc)(void);
typedef int32_t (__cdecl *TP_GetCompilerMessagesFunc)(char* Msg);

typedef int32_t (__cdecl *TP_OpenEditorFunc)(void* Parent, uint32_t EditorIndex);
typedef int32_t (__cdecl *TP_CloseEditorFunc)(int32_t EditorIndex);

typedef uint32_t (__cdecl *TP_GetNumberOfEditorsFunc)(void);
typedef void (__cdecl *TP_GetEditorLabelFunc)(uint32_t EditorIndex, char* EditorName, int32_t* TreeIconIndex);

typedef int32_t (__cdecl *TP_IsOptionSupportedFunc)(uint32_t Option);
#endif // __TARGET_WIN__

class TargetPluginClass
{
public:
	TargetPluginClass ();
	~TargetPluginClass ();

	//! Load the target plugin and instanciates all functions from the dynamic library
	//! \return >0 if dynamic library can not be loaded (system error code), -1 if some functions can not be instanciated, 0 if target plugin has been loaded correctly
	int LoadPlugin (wxString PluginPath);

	void GetPluginName (char* Name);
	void GetPluginVersion (uint32_t* Major, uint32_t* Minor, uint32_t* Build, uint32_t* Revision);

	void Initialize (void);
	void Terminate (void);

	void SetProjectPath (wxString Path, int32_t StrEncoding);
	void SetTargetsPath (wxString Path, int32_t StrEncoding);

	int CreateBeremizProjectFiles (void);
	int GenerateTargetFramework (void);
	int CopyPLCFilesForCompilation (void);
	int GenerateIOConfigurationFiles (void);
	int CleanForBuild (void);
	int StartCompilation (void);

	int LoadTargetProjectData (void);
	int SaveTargetProjectData (void);
	bool DataHasChanged (void);

	int OpenEditor (wxWindow* Parent, uint32_t EditorIndex);
	void CloseEditor (int32_t EditorIndex);

	int GetNumberOfEditors (void);
	void GetEditorLabel (int EditorIndex, char* EditorName, int32_t* TreeIconIndex);

	int IsOptionSupported (unsigned int Option);
	int GetCompilerMessages (char* Msg);
private:
#ifdef __TARGET_WIN__
	HINSTANCE hGetProcIDDLL;

	TP_GetPluginNameFunc TP_GetPluginName;
	TP_GetPluginVersionFunc TP_GetPluginVersion;

	TP_InitializeFunc TP_Initialize;
	TP_TerminateFunc TP_Terminate;

	TP_SetProjectPathFunc TP_SetProjectPath;
	TP_SetTargetsPathFunc TP_SetTargetsPath;

	TP_LoadTargetProjectDataFunc TP_LoadTargetProjectData;
	TP_SaveTargetProjectDataFunc TP_SaveTargetProjectData;
	TP_DataHasChangedFunc TP_DataHasChanged;

	TP_OpenEditorFunc TP_OpenEditor;
	TP_CloseEditorFunc TP_CloseEditor;

	TP_CreateBeremizProjectFilesFunc TP_CreateBeremizProjectFiles;
	TP_GenerateTargetFrameworkFunc TP_GenerateTargetFramework;
	TP_CopyPLCFilesForCompilationFunc TP_CopyPLCFilesForCompilation;
	TP_GenerateIOConfigurationFilesFunc TP_GenerateIOConfigurationFiles;
	TP_CleanForBuildFunc TP_CleanForBuild;
	TP_StartCompilationFunc TP_StartCompilation;
	TP_GetCompilerMessagesFunc TP_GetCompilerMessages;

	TP_GetNumberOfEditorsFunc TP_GetNumberOfEditors;
	TP_GetEditorLabelFunc TP_GetEditorLabel;

	TP_IsOptionSupportedFunc TP_IsOptionSupported;
#endif
#ifdef __TARGET_LINUX__
    void *dlibHandle;
#endif

	//! Set all function pointers to NULL to block call if function can not be instanciated
	void CleanFunctionEntries (void);
};

#endif

