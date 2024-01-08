/////////////////////////////////////////////////////////////////////////////
// Name:        RemoteTargetDialog.h
// Purpose:     CBUS PLC Remote Target configuration dialog
// Author:      Benoit BOUCHEZ
// Created:     12/08/2020
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

#ifndef __REMOTETARGETDIALOG_H__
#define __REMOTETARGETDIALOG_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "CBUSPLCForms.h"

extern wxString RemoteTarget;
extern wxString RemoteLogin;
extern wxString RemotePassword;
extern wxString RemotePath;
extern bool DataHasChanged;

class RemoteTargetDialog : public CTargetConfigDialog
{
public:
	RemoteTargetDialog (wxFrame* ParentFrame);
	~RemoteTargetDialog ();

	void SetFields (void);

	bool IsOKClicked (void);

private:
	bool OKClicked;

	void OnOKButton (wxCommandEvent& event);
	void OnCancelButton (wxCommandEvent& event);
	void OnTestConnectionBtn (wxCommandEvent& event);
};


#endif
