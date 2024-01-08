/////////////////////////////////////////////////////////////////////////////
// Name:        Pixtend_IOEdit.h
// Purpose:     I/O configuration frame for Beremiz Project Manager Pixtend V2 plugin
// Author:      Benoit BOUCHEZ
// Created:     28/06/2022
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

#ifndef __PIXTEND_IOEDIT_H__
#define __PIXTEND_IOEDIT_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "PixtendForms.h"

class PixtendV2_IOEditFrame : public CPixtendV2IOEditorFrame
{
public:
	PixtendV2_IOEditFrame (wxWindow* Parent);
    ~PixtendV2_IOEditFrame ();

	void OnClose (wxCloseEvent& event);

	void RefreshView (void);

	//! Menus
	void OnTargetParametersMenu (wxCommandEvent& event);
	void OnFileTransferOption (wxCommandEvent& event);
	void OnPLCStartMenu (wxCommandEvent& event);
	void OnPLCStopMenu (wxCommandEvent& event);
	void OnEnableAutoStartMenu (wxCommandEvent& event);
	void OnDisableAutoStartMenu (wxCommandEvent& event);

private:
	wxBitmap* PinoutBMP;
};

#endif
