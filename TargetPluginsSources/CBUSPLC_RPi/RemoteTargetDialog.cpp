/////////////////////////////////////////////////////////////////////////////
// Name:        RemoteTargetDialog.h
// Purpose:     Beremiz Project Manager CPU remote target configuration dialog
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

#include "RemoteTargetDialog.h"
#include "SupervisorComm.h"
#ifdef __TARGET_LINUX__
#include <arpa/inet.h>
#endif

extern CSupervisorCommunicator* Supervisor;

RemoteTargetDialog::RemoteTargetDialog (wxFrame* ParentFrame) : CTargetConfigDialog (ParentFrame)
{
	this->OKClicked = false;
}  // RemoteTargetDialog::RemoteTargetDialog
// -----------------------------------------------------

RemoteTargetDialog::~RemoteTargetDialog ()
{
}  // RemoteTargetDialog::~RemoteTargetDialog
// -----------------------------------------------------

void RemoteTargetDialog::SetFields (void)
{
	this->EditIPAddress->SetValue(RemoteTarget);
	this->EditLogin->SetValue(RemoteLogin);
	this->EditPassword->SetValue(RemotePassword);
	this->EditBeremizPLCDirectory->SetValue (RemotePath);
}  // RemoteTargetDialog::SetFields
// -----------------------------------------------------

void RemoteTargetDialog::OnOKButton (wxCommandEvent& WXUNUSED(event))
{
	// TODO : check IP address validity

	// Copy entered strings into project
	RemoteTarget = this->EditIPAddress->GetValue();
	RemoteLogin = this->EditLogin->GetValue();
	RemotePassword = this->EditPassword->GetValue();
	RemotePath = this->EditBeremizPLCDirectory->GetValue();
	DataHasChanged = true;

	this->OKClicked = true;
	this->Close();
}  // RemoteTargetDialog::OnOKButton
// -----------------------------------------------------

void RemoteTargetDialog::OnCancelButton (wxCommandEvent& WXUNUSED(event))
{
	this->OKClicked = false;
	this->Close();
}  // RemoteTargetDialog::OnCancelButton
// -----------------------------------------------------

bool RemoteTargetDialog::IsOKClicked (void)
{
	return OKClicked;
}  // RemoteTargetDialog::IsOKClicked
// -----------------------------------------------------

void RemoteTargetDialog::OnTestConnectionBtn (wxCommandEvent& WXUNUSED(event))
{
	bool ConnectionOK;
	//bool FileTransferOK=false;
	wxString StatusStr;
	unsigned int IPTest;
	wxString IPAddress;

	if (Supervisor == 0)
	{
		wxMessageBox ("Internal error : supervisor module has not been created.\nPlease report error to developer.", "Test supervisor connection", wxOK+wxICON_STOP);
		return;
	}

	// Convert temporary address from edition box rather than address stored in project (may be different)
	// DON'T FORGET TO CLICK ON OK TO SAVE IT IF IT HAS CHANGED
	IPTest=inet_addr(EditIPAddress->GetValue().mb_str());
    if (IPTest==INADDR_NONE)
	{
		wxMessageBox ("Target IP address is invalid.\nCan not test communication with PLC supervisor", "Error", wxOK+wxICON_ERROR);
		return;
	}

	IPAddress = EditIPAddress->GetValue();
	ConnectionOK=(Supervisor->TestSupervisorConnection(IPAddress)==0);

	// TODO : Check that SCP file transfers works

	// Display test result
	StatusStr = "Connection to PiXtend V2 PLC supervisor : ";
	if (ConnectionOK) StatusStr=StatusStr+"OK";
	else StatusStr=StatusStr+"Not working";
	//StatusStr = StatusStr + "\nFile transfer : ";
	//if (FileTransferOK) StatusStr = StatusStr + "OK";
	//else StatusStr = StatusStr + "Not working";

	wxMessageBox (StatusStr, "Connection test results", wxOK);
}  // RemoteTargetDialog::OnTestConnectionBtn
// -----------------------------------------------------
