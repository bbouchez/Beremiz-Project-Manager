/////////////////////////////////////////////////////////////////////////////
// Name:        FileTransferOptionsDialog.cpp
// Purpose:     File transfer options dialog for CBUS PLC target plugin
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

#include "FileTransferOptionsDialog.h"

FileTransferOptionsDialog::FileTransferOptionsDialog (wxFrame* ParentFrame) : CCBUSPLCOptionsDialog (ParentFrame)
{
}  // FileTransferOptionsDialog::FileTransferOptionsDialog
// -----------------------------------------------------

FileTransferOptionsDialog::~FileTransferOptionsDialog ()
{
}  // FileTransferOptionsDialog::~FileTransferOptionsDialog
// -----------------------------------------------------

void FileTransferOptionsDialog::OnBrowseButton (wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog dlg (this, wxT("Choose location of winscp.com"), wxEmptyString, wxEmptyString, wxT("WinSCP.com file (*.com)|*.com"), wxFD_OPEN+wxFD_FILE_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)	return;

	EditWinSCPLocation->SetValue (dlg.GetPath());
}  // OptionsDialog::OnBrowseButton
// -----------------------------------------------------
