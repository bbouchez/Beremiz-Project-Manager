/////////////////////////////////////////////////////////////////////////////
// Name:        BeremizProjectManager_TargetsAPI.h
// Purpose:     Target Plugin SDK - Dynamic libray interface declaration
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

#ifndef __BPM_TARGETSAPI_H__
#define __BPM_TARGETSAPI_H__

#include <stdint.h>
#include "BeremizProjectManager_SDK_Defs.h"

#ifdef __TARGET_WIN__
#define EXPORT_DYNAMIC_LIB __declspec(dllexport) __cdecl
#define EXPORT_INTERFACE __cdecl
#endif  // __TARGET_WIN__
#ifdef __TARGET_LINUX__
#define EXPORT_DYNAMIC_LIB
#define EXPORT_INTERFACE
#endif  // __TARGET_LINUX__-

#ifdef __cplusplus
extern "C" {
#endif

// *** System initialization / release ***
//! Prepares underlying framework and resources. This function MUST be called by host before any other function of the DLL is called
void EXPORT_DYNAMIC_LIB TP_Initialize(void);
//! \brief Release all resources used by the plugin. This function is called by host just before it closes
void EXPORT_DYNAMIC_LIB TP_Terminate(void);

// *** Plugin identification ***
//! Fill Name buffer with a human readable name for the plugin (to be displayed typically in a list of available targets)
//! \param Name : pointer to a C string buffer. Minimum buffer size is expected to be at least TARGET_PLUGIN_STRING_SIZE
void EXPORT_DYNAMIC_LIB TP_GetPluginName (char* Name);

void EXPORT_DYNAMIC_LIB TP_GetPluginVersion (uint32_t* Major, uint32_t* Minor, uint32_t* Build, uint32_t* Revision);

//! Request plugin to indicate if an option is supported. An option can be modified dynamically depending on project, so it is recommended to check if an option is supported before it is used
//! \param Option option code to check if supported or not. See SDK TP_OPTION_xxxxx codes
//! \return 0 : option is not supported, 1 : option is supported, -1 : option or support is unknown
int32_t EXPORT_DYNAMIC_LIB TP_IsOptionSupported (uint32_t Option);

//! \brief Tells to plugin where PLC project is located
void EXPORT_DYNAMIC_LIB TP_SetProjectPath (char* Path, int32_t StrEncoding);
//! \brief Tells to plugin where target frameworks are stored
void EXPORT_DYNAMIC_LIB TP_SetTargetsPath (char* Path, int32_t StrEncoding);
//! \brief Configure remote target property (access to supervisor and compilation directory)
void EXPORT_DYNAMIC_LIB TP_SetRemoteTargetProperties (char* Login, char* Password, char* TargetAddress, char* CompilationPath, int32_t StrEncoding);

//! Load specific plugin configuration data (typically I/O configuration)
int32_t EXPORT_DYNAMIC_LIB TP_LoadTargetProjectData (void);
//! Save specific plugin configuration data (typicall I/O configuration)
int32_t EXPORT_DYNAMIC_LIB TP_SaveTargetProjectData (void);

//! Return 1 if plugin configuration data has changed, 0 in other case (used to warn user that project is not fully saved)
int32_t EXPORT_DYNAMIC_LIB TP_DataHasChanged (void);

// *** Editor windows ***
//! Reports number of editor frames for the plugin. Each editor will be represented as an entry in the tree, as a child of the CPU
// Value of 0 means no editor window is created even for the CPU.
uint32_t EXPORT_DYNAMIC_LIB TP_GetNumberOfEditors (void);

//! Returns the name of complementary editor to be displayed in the project tree
void EXPORT_DYNAMIC_LIB TP_GetEditorLabel (uint32_t EditorIndex, char* EditorName, int32_t* TreeIconIndex);

//! \param Parent pointer to a wxWindow
//! \param EditorIndex select the editor window to open in case there are multiple sub windows for edition (eg : main parameters, optional parameters). Index 0 is the CPU editor which should exist for all targets
int32_t EXPORT_DYNAMIC_LIB TP_OpenEditor(void* Parent, uint32_t EditorIndex);

//! Hide editor window
//! \param EditorIndex : in case the Target Plugin has mulitple editor windows, indicate the window to close. -1 tells the target plugin to close all opened editor windows
void EXPORT_DYNAMIC_LIB TP_CloseEditor (int32_t EditorIndex);

// *** Project files generation ***
//! Copy basic PLC project file into the project folder (base files for Beremiz)
int32_t EXPORT_DYNAMIC_LIB TP_CreateBeremizProjectFiles (void);

//! Copy framework source files (not user project) into compilation directory
int32_t EXPORT_DYNAMIC_LIB TP_GenerateTargetFramework (void);

//! Produce the I/O configuration file to be compiled for the target based on I/O declaration in the plugin
int32_t EXPORT_DYNAMIC_LIB TP_GenerateIOConfigurationFiles (void);

//! Copy user project source files (generated from Beremiz) into compilation directory
int32_t EXPORT_DYNAMIC_LIB TP_CopyPLCFilesForCompilation (void);

//! Performs a clean on the target (erases all PLC user source files)
int32_t EXPORT_DYNAMIC_LIB TP_CleanForBuild (void);

//! Starts compilation process driven by the plugin.
int32_t EXPORT_DYNAMIC_LIB TP_StartCompilation (void);

//! Returns message from compiler during compilation process
//! \return size of the message, 0 means no message available, -1 means compilation process has ended or a problem has been detected
int32_t EXPORT_DYNAMIC_LIB TP_GetCompilerMessages (uint8_t* Msg);

//! Fill the standard bus identification structure (allows the Manager to know what standard busses are supported by the plugin)
// TODO

#ifdef __cplusplus
}
#endif

#endif
