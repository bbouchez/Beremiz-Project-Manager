/////////////////////////////////////////////////////////////////////////////
// Name:        GraphicsUtils.cpp
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

#include "GraphicsUtils.h"

//! Bitmaps for the project tree
wxBitmap TreeIconProjectBitmap;
wxBitmap TreeIconCPUBitmap;
wxBitmap TreeIconBusBitmap;
wxBitmap TreeIconGear1Bitmap;
wxBitmap TreeIconGear2Bitmap;
wxBitmap TreeIconBlocksBitmap;
wxBitmap TreeIconCPOUBitmap;
wxBitmap TreeIconFBDPOUBitmap;

void InitProjectTreeIcons (wxTreeCtrl& ProjectTreeCtrl)
{
#ifdef __TARGET_WIN__
	TreeIconProjectBitmap.LoadFile (".\\images\\tree_project_icon.png", wxBITMAP_TYPE_PNG);
	TreeIconCPUBitmap.LoadFile (".\\images\\tree_cpu_icon.png", wxBITMAP_TYPE_PNG);
	TreeIconBusBitmap.LoadFile (".\\images\\tree_bus_icon.png", wxBITMAP_TYPE_PNG);
	TreeIconGear1Bitmap.LoadFile (".\\images\\tree_gear1_icon.png", wxBITMAP_TYPE_PNG);
	TreeIconGear2Bitmap.LoadFile (".\\images\\tree_gear2_icon.png", wxBITMAP_TYPE_PNG);
	TreeIconBlocksBitmap.LoadFile (".\\images\\tree_blocks_icon.png", wxBITMAP_TYPE_PNG);
	TreeIconCPOUBitmap.LoadFile (".\\images\\tree_c_pou_icon.png", wxBITMAP_TYPE_PNG);
	TreeIconFBDPOUBitmap.LoadFile (".\\images\\tree_fbd_pou_icon.png", wxBITMAP_TYPE_PNG);
#endif // __TARGET_WIN__
#ifdef __TARGET_LINUX__
	TreeIconProjectBitmap.LoadFile ("./images/tree_project_icon.png", wxBITMAP_TYPE_PNG);
	TreeIconCPUBitmap.LoadFile ("./images/tree_cpu_icon.png", wxBITMAP_TYPE_PNG);
	TreeIconBusBitmap.LoadFile ("./images/tree_bus_icon.png", wxBITMAP_TYPE_PNG);
	TreeIconGear1Bitmap.LoadFile ("./images/tree_gear1_icon.png", wxBITMAP_TYPE_PNG);
	TreeIconGear2Bitmap.LoadFile ("./images/tree_gear2_icon.png", wxBITMAP_TYPE_PNG);
	TreeIconBlocksBitmap.LoadFile ("./images/tree_blocks_icon.png", wxBITMAP_TYPE_PNG);
	TreeIconCPOUBitmap.LoadFile ("./images/tree_c_pou_icon.png", wxBITMAP_TYPE_PNG);
	TreeIconFBDPOUBitmap.LoadFile ("./images/tree_fbd_pou_icon.png", wxBITMAP_TYPE_PNG);
#endif // __TARGET_LINUX__

	// Create the icon list for the tree (will be retained automatically by the call to AssignImageList)
	// IMPORTANT : the icons must be added in the same order as the #defines for the icon index (see GraphicsUtils.h)
    wxImageList* TreeIconList = new wxImageList(16, 16);
	TreeIconList->Add (TreeIconProjectBitmap);
	TreeIconList->Add (TreeIconCPUBitmap);
	TreeIconList->Add (TreeIconBusBitmap);
	TreeIconList->Add (TreeIconGear1Bitmap);
	TreeIconList->Add (TreeIconGear2Bitmap);
	TreeIconList->Add (TreeIconBlocksBitmap);
	TreeIconList->Add (TreeIconCPOUBitmap);
	TreeIconList->Add (TreeIconFBDPOUBitmap);
	ProjectTreeCtrl.AssignImageList(TreeIconList);
}  // InitProjectTreeIcons
// -----------------------------------------------------
