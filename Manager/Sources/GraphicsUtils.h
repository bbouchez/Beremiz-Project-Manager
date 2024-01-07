/////////////////////////////////////////////////////////////////////////////
// Name:        GraphicsUtils.h
// Purpose:     Beremiz Project Manager various tools for graphics
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

#ifndef __GRAPHICSUTILS_H__
#define __GRAPHICSUTILS_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/imaglist.h>
#include <wx/treectrl.h>

//! Icon index for the project tree
#define PROJECT_TREE_ICON_PROJECT		0
#define PROJECT_TREE_ICON_CPU			1
#define PROJECT_TREE_ICON_BUS			2
#define PROJECT_TREE_ICON_GEAR1			3
#define PROJECT_TREE_ICON_GEAR2			4
#define PROJECT_TREE_ICON_BLOCKS		5
#define PROJECT_TREE_ICON_C_POU			6
#define PROJECT_TREE_ICON_FBD_POU		7

//! Initializes icons for the project tree
void InitProjectTreeIcons (wxTreeCtrl& ProjectTreeCtrl);

#endif
