/////////////////////////////////////////////////////////////////////////////
// Name:        Pixtend_IOEdit.cpp
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

#include "Pixtend_IOEdit.h"
#include "PixtendV2_DLLMain.h"
#include "SupervisorComm.h"
#include "FileTransferOptionsDialog.h"
#include "RemoteTargetDialog.h"

extern bool DataHasChanged;
extern wxString RemoteTarget;
extern wxString WinSCPLocation;
extern bool HoldSCPTransfer;

extern CSupervisorCommunicator* Supervisor;

PixtendV2_IOEditFrame::PixtendV2_IOEditFrame (wxWindow* Parent) : CPixtendV2IOEditorFrame (Parent)
{
#ifdef __TARGET_WIN__
	PinoutBMP = new wxBitmap ("pixtendv2l_pinout", wxBITMAP_TYPE_BMP_RESOURCE);
#endif  // __TARGET_WIN__
#ifdef __TARGET_LINUX__
	PinoutBMP = new wxBitmap ("./PixtendV2_Images/pixtendV2-L.bmp", wxBITMAP_TYPE_BMP);
#endif  // TARGET_LINUX__
	this->PixtendBitmap->SetBitmap (*PinoutBMP);
}  // RPiPico_IOEditFrame::IONORP_IOEditFrame
// -----------------------------------------------------

PixtendV2_IOEditFrame::~PixtendV2_IOEditFrame ()
{
	if (PinoutBMP)
		delete PinoutBMP;
}  // PixtendV2_IOEditFrame::~PixtendV2_IOEditFrame
// -----------------------------------------------------

void PixtendV2_IOEditFrame::OnClose (wxCloseEvent& WXUNUSED(event))
{
	this->Show(false);
}  // PixtendV2_IOEditFrame::OnClose
// -----------------------------------------------------

void PixtendV2_IOEditFrame::RefreshView (void)
{
	// TODO : choose bitmap depending on platform
}  // PixtendV2_IOEditFrame::RefreshView
// -----------------------------------------------------

void PixtendV2_IOEditFrame::OnTargetParametersMenu (wxCommandEvent& WXUNUSED(event))
{
	RemoteTargetDialog* Dialog;

	Dialog = new RemoteTargetDialog (this);
	if (Dialog)
	{
		Dialog->SetFields();
		if (Dialog->ShowModal() == wxID_OK)
			DataHasChanged = true;

		delete Dialog;
	}
}  // PixtendV2_IOEditFrame::OnTargetParametersMenu
// -----------------------------------------------------

void PixtendV2_IOEditFrame::OnFileTransferOption (wxCommandEvent& WXUNUSED(event))
{
	FileTransferOptionsDialog* Dialog;

	Dialog=new FileTransferOptionsDialog (this);

	if (Dialog)
	{
		Dialog->EditWinSCPLocation->SetValue (WinSCPLocation);
		Dialog->ChkHoldWinSCPTransfer->SetValue (HoldSCPTransfer);
		if (Dialog->ShowModal() == wxID_OK)
		{
			WinSCPLocation = Dialog->EditWinSCPLocation->GetValue();
			HoldSCPTransfer = Dialog->ChkHoldWinSCPTransfer->GetValue();

			DataHasChanged = true;
		}

		delete Dialog;
	}
}  // CBUSPLC_IOEditFrame::OnFileTransferOption
// -----------------------------------------------------

void PixtendV2_IOEditFrame::OnPLCStartMenu (wxCommandEvent& WXUNUSED(event))
{
	int StartResult;
	wxString ErrMsg;

	if (Supervisor==0) return;

	StartResult = Supervisor->StartPLC(RemoteTarget);
	if (StartResult!=0)
	{
		switch (StartResult)
		{
			case 1 : ErrMsg = "Error when sending Start PLC command to Supervisor"; break;
			case 2 : ErrMsg = "PLC or Supervisor is not responding"; break;
			case 3 : ErrMsg = "PLC is already running"; break;
			case 4 : ErrMsg = "Supervisor can not start PLC"; break;
			default : ErrMsg = "Undefined error while starting PLC";
		}
		wxMessageBox (ErrMsg, "Start PLC error", wxOK+wxICON_ERROR);
	}
	else wxMessageBox ("PLC runtime started successfully", "Start PLC runtime", wxOK+wxICON_INFORMATION);
}  // PixtendV2_IOEditFrame::OnPLCStartMenu
// -----------------------------------------------------

void PixtendV2_IOEditFrame::OnPLCStopMenu (wxCommandEvent& WXUNUSED(event))
{
	int StopResult;
	wxString ErrMsg;

	if (Supervisor==0) return;

	StopResult = Supervisor->StopPLC(RemoteTarget);
	if (StopResult!=0)
	{
		switch (StopResult)
		{
			case 1 : ErrMsg = "Error when sending Stop PLC command to Supervisor"; break;
			case 2 : ErrMsg = "PLC or Supervisor is not responding"; break;
			case 3 : ErrMsg = "PLC is not running"; break;
			default : ErrMsg = "Undefined error while stopping PLC";
		}
		wxMessageBox (ErrMsg, "Stop PLC error", wxOK+wxICON_ERROR);
	}
	else wxMessageBox ("PLC runtime is stopped", "Stop PLC runtime", wxOK+wxICON_INFORMATION);
}  // PixtendV2_IOEditFrame::OnPLCStopMenu
// -----------------------------------------------------

void PixtendV2_IOEditFrame::OnEnableAutoStartMenu (wxCommandEvent& WXUNUSED(event))
{
	int Result;

	if (Supervisor==0) return;

	Result = Supervisor->SetAutomaticPLCStart(RemoteTarget, true);
	if (Result!=0)
		wxMessageBox ("An error occured while executing the command", "Enable automatic PLC start", wxOK+wxICON_ERROR);
}  // PixtendV2_IOEditFrame::OnEnableAutoStartMenu
// -----------------------------------------------------

void PixtendV2_IOEditFrame::OnDisableAutoStartMenu (wxCommandEvent& WXUNUSED(event))
{
	int Result;

	if (Supervisor==0) return;

	Result = Supervisor->SetAutomaticPLCStart(RemoteTarget, false);
	if (Result!=0)
		wxMessageBox ("An error occured while executing the command", "Disable automatic PLC start", wxOK+wxICON_ERROR);
}  // PixtendV2_IOEditFrame::OnDisableAutoStartMenu
// -----------------------------------------------------


