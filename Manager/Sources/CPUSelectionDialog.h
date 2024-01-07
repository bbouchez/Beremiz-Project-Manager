/////////////////////////////////////////////////////////////////////////////
// Name:        CPUSelectionDialog.h
// Purpose:     Beremiz Project Manager CPU selection dialog
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

#ifndef __CPUSELECTIONDIALOG_H__
#define __CPUSELECTIONDIALOG_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "BPMForms.h"

typedef struct {
	wxString TargetName;
	wxString CPUType;
	wxString LibraryName;
	wxString Information;
	void* NextTargetData;		// Pointer to next TARGET_DATA member in the pointer chain
} TARGET_DATA;

class CPUSelectionDialog : public CSelectionCPUDialog
{
public:
	CPUSelectionDialog (wxFrame* ParentFrame);
	~CPUSelectionDialog ();

	void OnCPUModelChoice (wxCommandEvent& event);	
	void OnOKButton (wxCommandEvent& event);
	void OnCancelButton (wxCommandEvent& event);

	bool OKClicked;
	wxString TargetPluginName;
private:
	TARGET_DATA* FirstTargetData;
};

#endif