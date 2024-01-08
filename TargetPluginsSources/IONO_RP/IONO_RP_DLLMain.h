/////////////////////////////////////////////////////////////////////////////
// Name:        IONO_RP_DLLMain.h
// Purpose:     Plugin for Beremiz Project Manager for IONO RP target
// Author:      Benoit BOUCHEZ
// Created:     12/08/2020
// Copyright:   (c) Benoit BOUCHEZ
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

#ifndef __IONO_RP_DLLMAIN_H__
#define __IONO_RP_DLLMAIN_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include ".\..\BeremizProjectManager_TargetsAPI.h"

// Possible functions for I/O pins
#define IO_FUNC_NONE			0
#define IO_FUNC_DIGITAL_INPUT	1
#define IO_FUNC_DIGITAL_OUTPUT	2
#define IO_FUNC_ANALOG_INPUT	3
#define IO_FUNC_ANALOG_OUTPUT	4

#define IONO_RP_IO_LINES		12

#define ARDUINO_COMPILER		0
#define PICO_SDK_COMPILER		1

#endif // __IONO_RP_DLLMAIN_H__
