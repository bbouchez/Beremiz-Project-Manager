/////////////////////////////////////////////////////////////////////////////
// Name:        CBUSPLC_IOEdit.cpp
// Purpose:     I/O assignation frame for Beremiz CBUS PLC
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

#include "CBUSPLC_IOEdit.h"
#include "RemoteTargetDialog.h"
#include "FileTransferOptionsDialog.h"
#include "RPi_CBUS_PLC_DLLMain.h"

extern TCBUS_EVENT_IO CBUSEventInput[NUM_CBUS_EVENT_INPUTS];
extern TCBUS_EVENT_IO CBUSEventOutput[NUM_CBUS_EVENT_OUTPUTS];
extern wxString WinSCPLocation;
extern bool HoldSCPTransfer;
extern bool DataHasChanged;

extern CSupervisorCommunicator* Supervisor;

CBUSPLC_IOEditFrame::CBUSPLC_IOEditFrame (wxWindow* Parent) : CCBUSIOEditFrame (Parent)
{
	int Lines;
	int BitCounter;
	int ByteCounter;
	char IOName[256];

	IOGrid->HideRowLabels ();

	// Fill cells with PLC I/O addresses
	BitCounter = 0;
	ByteCounter= 1;		// First byte of I/O is reserved for CANPiCAP local I/O
	for (Lines=0; Lines<128; Lines++)
	{
		// Protect cells with I/O names
		IOGrid->SetReadOnly (Lines, 0, true);
		IOGrid->SetReadOnly (Lines, 4, true);

		sprintf (IOName, "%%IX%d.%d", ByteCounter, BitCounter);
		IOGrid->SetCellValue (Lines, 0, IOName);
		sprintf (IOName, "%%QX%d.%d", ByteCounter, BitCounter);
		IOGrid->SetCellValue (Lines, 4, IOName);

		BitCounter++;
		if (BitCounter==8)
		{
			BitCounter = 0;
			ByteCounter++;
		}
	}
}  // CBUSPLC_IOEditFrame::CBUSPLC_IOEditFrame
// -----------------------------------------------------

CBUSPLC_IOEditFrame::~CBUSPLC_IOEditFrame ()
{
}  // CBUSPLC_IOEditFrame::~CBUSPLC_IOEditFrame
// -----------------------------------------------------

void CBUSPLC_IOEditFrame::RefreshView (void)
{
	int Line;

	for (Line=0; Line<NUM_CBUS_EVENT_INPUTS; Line++)
	{
		if (CBUSEventInput[Line].DeviceNumber != 0)
		{
			IOGrid->SetCellValue (Line, 1, wxString::Format("%d", CBUSEventInput[Line].DeviceNumber));
			IOGrid->SetCellValue (Line, 2, wxString::Format("%d", CBUSEventInput[Line].EventNumber));
			IOGrid->SetCellValue (Line, 3, CBUSEventInput[Line].IOLabel);
		}
		else
		{
			IOGrid->SetCellValue (Line, 1, "");
			IOGrid->SetCellValue (Line, 2, "");
			IOGrid->SetCellValue (Line, 3, "");
		}
	}

	for (Line=0; Line<NUM_CBUS_EVENT_OUTPUTS; Line++)
	{
		if (CBUSEventOutput[Line].DeviceNumber != 0)
		{
			IOGrid->SetCellValue (Line, 5, wxString::Format("%d", CBUSEventOutput[Line].DeviceNumber));
			IOGrid->SetCellValue (Line, 6, wxString::Format("%d", CBUSEventOutput[Line].EventNumber));
			IOGrid->SetCellValue (Line, 7, CBUSEventOutput[Line].IOLabel);
		}
		else
		{
			IOGrid->SetCellValue (Line, 5, "");
			IOGrid->SetCellValue (Line, 6, "");
			IOGrid->SetCellValue (Line, 7, "");
		}
	}
}  // CBUSPLC_IOEditFrame::RefreshView
// -----------------------------------------------------

void CBUSPLC_IOEditFrame::OnCellDataChange (wxGridEvent& event)
{
	int CellData;
	int Row, Col;
	wxString TestValStr;

	// Check if value entered in the cell is valid
	Row = event.GetRow();
	Col = event.GetCol();
	TestValStr = IOGrid->GetCellValue (Row, Col);

	// If this is a label cell, do not test the value range, just copy the string into project
	if (Col == 3)  // Input label
	{
		CBUSEventInput[Row].IOLabel=TestValStr;
	}
	else if (Col == 7)  // Output label
	{
		CBUSEventOutput[Row].IOLabel=TestValStr;
	}

	// For other columns, we have to check that entered value is in valid range
	else
	{
		CellData = wxAtoi (TestValStr);
		// If value is out of range, simply ignore it
		// TODO : we should reload the value from configuration data, to erase what has been entered
		if ((CellData<0)||(CellData>65535))
		{
			wxMessageBox ("Invalid value entered", "Invalid node or event number", wxOK+wxICON_EXCLAMATION);
			return;
		}

		// If we enter a null value for Device Number, the entry is deactivated
		// Erase event number to show event is deactivated
		switch (Col)
		{
			case 1 : // Input device number
				CBUSEventInput[Row].DeviceNumber = CellData;
				this->RefreshView();		// This will hide the deactivated input event number
				break;
			case 2 : // Input event number
				CBUSEventInput[Row].EventNumber = CellData;
				break;
			case 4 : // Output device number
				CBUSEventOutput[Row].DeviceNumber = CellData;
				this->RefreshView();		// This will hide the deactivated output event number
				break;
			case 5 :  // Output event number
				CBUSEventOutput[Row].EventNumber = CellData;
				break;
		}
	}
	DataHasChanged = true;
}  // CBUSPLC_IOEditFrame::OnCellDataChange
// -----------------------------------------------------

void CBUSPLC_IOEditFrame::OnTargetParametersMenu (wxCommandEvent& WXUNUSED(event))
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
}  // CBUSPLC_IOEditFrame::OnTargetParametersMenu
// -----------------------------------------------------

void CBUSPLC_IOEditFrame::OnFileTransferOption (wxCommandEvent& WXUNUSED(event))
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

void CBUSPLC_IOEditFrame::OnPLCStartMenu (wxCommandEvent& WXUNUSED(event))
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
}  // CBUSPLC_IOEditFrame::OnPLCStartMenu
// -----------------------------------------------------

void CBUSPLC_IOEditFrame::OnPLCStopMenu (wxCommandEvent& WXUNUSED(event))
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
}  // CBUSPLC_IOEditFrame::OnPLCStopMenu
// -----------------------------------------------------

void CBUSPLC_IOEditFrame::OnEnableAutoStartMenu (wxCommandEvent& WXUNUSED(event))
{
	int Result;

	if (Supervisor==0) return;

	Result = Supervisor->SetAutomaticPLCStart(RemoteTarget, true);
	if (Result!=0)
		wxMessageBox ("An error occured while executing the command", "Enable automatic PLC start", wxOK+wxICON_ERROR);
}  // CBUSPLC_IOEditFrame::OnEnableAutoStartMenu
// -----------------------------------------------------

void CBUSPLC_IOEditFrame::OnDisableAutoStartMenu (wxCommandEvent& WXUNUSED(event))
{
	int Result;

	if (Supervisor==0) return;

	Result = Supervisor->SetAutomaticPLCStart(RemoteTarget, false);
	if (Result!=0)
		wxMessageBox ("An error occured while executing the command", "Disable automatic PLC start", wxOK+wxICON_ERROR);
}  // CBUSPLC_IOEditFrame::OnDisableAutoStartMenu
// -----------------------------------------------------

