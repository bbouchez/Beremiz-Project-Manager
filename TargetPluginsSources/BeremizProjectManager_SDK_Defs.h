/////////////////////////////////////////////////////////////////////////////
// Name:        BeremizProjectManager_SDK_Defs.h
// Purpose:     Target Plugin SDK - Generic definitions
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

#ifndef __BPM_SDK_DEFS_H__
#define __BPM_SDK_DEFS_H__

//! Maximum length of plugin name
#define TARGET_PLUGIN_STRING_SIZE		256

//! String encoding modes
#define STRING_ENCODING_C		0
#define STRING_ENCODING_UTF8	1

//! Standard icons index (for the project tree)
#define TP_TREE_ICON_NONE		-1
#define TP_TREE_ICON_ROOT		0
#define TP_TREE_ICON_CPU		1
#define TP_TREE_ICON_BUS		2

//! Error codes
#define TARGET_PLUGIN_NO_ERROR				0
//! Function not found in target plugin (or plugin not loaded properly)
#define ERR_TARGET_PLUGIN_MISSING_FUNCTION	-1
//! File not found or file can not be created
#define ERR_TARGET_PLUGIN_FILE_ERROR		-2
//! File type does not match expected one
#define ERR_TARGET_PLUGIN_INVALID_FILE		-3
//! File version is not supported
#define ERR_TARGET_PLUGIN_INVALID_FILE_VERSION	-4
//! Option is not supported
#define ERR_TARGET_PLUGIN_NON_SUPPORTED_FEATURE	-5
//! Communication with target is not possible (like supervisor not existing or not instanciated)
#define ERR_TARGET_NO_COMMUNICATION			-6
//! Communication with target is possible but errors are encountered
#define ERR_TARGET_COMMUNICATION_ERROR		-7
//! No answer received from target after timeout
#define ERR_TARGET_COMMUNICATION_TIMEDOUT	-8
//! Compiler can't be started
#define ERR_TARGET_COMPILER_FAULT			-9
//! Fallback error case
#define ERR_TARGET_GENERIC_ERROR			-100

//! Plugin options codes (for TP_IsOptionSupported)
#define TP_OPTION_TARGET_START				1		// Target PLC can be started from Project Manager using supervisor
#define TP_OPTION_TARGET_STOP				2		// Target PLC can be stopped from Project Manager using supervisor
#define TP_OPTION_TARGET_AUTO_START			3		// Target PLC allows control of automatic startup when powered
#define TP_OPTION_COMPILATION_EXTERNAL		100		// Compilation is completely external (not be launched from Project Manager)
#define TP_OPTION_PLUGIN_COMPILER			101		// Compilation is initiated by the plugin itself

#endif