/////////////////////////////////////////////////////////////////////////////
// Name:        IONO_IOEdit.cpp
// Purpose:     I/O assignation frame for Beremiz IONO RP plugin
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

#include "IONO_IOEdit.h"
#include "IONO_RP_DLLMain.h"

extern unsigned int PinUsage[IONO_RP_IO_LINES];
extern int ProjectCompiler;
extern bool DataHasChanged;
extern wxString ArduinoCLILocation;

//! Strings for pin functions
wxString NotUsedStr = "Not used";
wxString DigitalInputStr = "Digital input";
wxString DigitalOutputStr = "Digital output";
wxString AnalogInputStr = "Analog input";
wxString AnalogOutputStr = "Analog output";
wxString ServoOutputStr = "Servo output";

IONORP_IOEditFrame::IONORP_IOEditFrame (wxWindow* Parent) : CIonoIOEditorFrame (Parent)
{
	IOGrid->HideRowLabels ();

	IOGrid->SetColSize (0, 100);
	IOGrid->SetColSize (1, 100);
	IOGrid->SetColSize (2, 80);

	IOGrid->SetCellValue (0, 0, "DI1 / AI1");
	IOGrid->SetCellValue (1, 0, "DI2 / AI2");
	IOGrid->SetCellValue (2, 0, "DI3 / AI3");
	IOGrid->SetCellValue (3, 0, "DI4 / AI4");
	IOGrid->SetCellValue (4, 0, "DI5");		// This should be also DIO, as it can be set as TTL I/O
	IOGrid->SetCellValue (5, 0, "DI6");		// Same as DI5
	IOGrid->SetCellValue (6, 0, "DO1");
	IOGrid->SetCellValue (7, 0, "DO2");
	IOGrid->SetCellValue (8, 0, "DO3");
	IOGrid->SetCellValue (9, 0, "DO4");
	IOGrid->SetCellValue (10, 0, "AO1");
	IOGrid->SetCellValue (11, 0, "LED PWM");

	PinoutBMP = new wxBitmap ("iono_rp_pinout", wxBITMAP_TYPE_BMP_RESOURCE);
	this->IonoBitmap->SetBitmap (*PinoutBMP);
}  // IONORP_IOEditFrame::IONORP_IOEditFrame
// -----------------------------------------------------

IONORP_IOEditFrame::~IONORP_IOEditFrame ()
{
	if (PinoutBMP)
		delete PinoutBMP;
}  // IONORP_IOEditFrame::~IONORP_IOEditFrame
// -----------------------------------------------------

void IONORP_IOEditFrame::OnClose (wxCloseEvent& WXUNUSED(event))
{
	this->Show(false);
}  // IONORP_IOEditFrame::OnClose
// -----------------------------------------------------

void IONORP_IOEditFrame::RefreshView (void)
{
	int Lines;
	char PLCNameStr[256];

	// Display selected compiler
	if (ProjectCompiler==ARDUINO_COMPILER) CompilerChoiceBox->SetSelection(0);
	else if (ProjectCompiler==PICO_SDK_COMPILER) CompilerChoiceBox->SetSelection(1);

	for (Lines=0; Lines<IONO_RP_IO_LINES; Lines++)
	{
		if (PinUsage[Lines] == IO_FUNC_NONE)
		{
			IOGrid->SetCellValue (Lines, 1, "Not used");
			IOGrid->SetCellValue (Lines, 2, "---");
		}
		else
		{
			if (Lines<=3)
			{
				switch (PinUsage[Lines])
				{
					case IO_FUNC_DIGITAL_INPUT :
						IOGrid->SetCellValue (Lines, 1, DigitalInputStr);
						sprintf (&PLCNameStr[0], "%%IX0.%d", Lines+1);
						IOGrid->SetCellValue (Lines, 2, PLCNameStr);
						break;
					case IO_FUNC_ANALOG_INPUT :
						IOGrid->SetCellValue (Lines, 1, AnalogInputStr);
						sprintf (&PLCNameStr[0], "%%IW0.%d", Lines+1);
						IOGrid->SetCellValue (Lines, 2, PLCNameStr);
						break;
					default :
						IOGrid->SetCellValue (Lines, 1, "????");
						IOGrid->SetCellValue (Lines, 2, "");
				}
			}
			else if (Lines <= 5)
			{
				switch (PinUsage[Lines])
				{
					case IO_FUNC_DIGITAL_INPUT :
						IOGrid->SetCellValue (Lines, 1, DigitalInputStr);
						sprintf (&PLCNameStr[0], "%%IX0.%d", Lines+1);
						IOGrid->SetCellValue (Lines, 2, PLCNameStr);
						break;
					default :
						IOGrid->SetCellValue (Lines, 1, "????");
						IOGrid->SetCellValue (Lines, 2, "");
				}
			}
			else if (Lines <= 9)
			{
				if (PinUsage[Lines] == IO_FUNC_DIGITAL_OUTPUT)
				{
					IOGrid->SetCellValue (Lines, 1, DigitalOutputStr);
					sprintf (&PLCNameStr[0], "%%QX0.%d", Lines-5);
					IOGrid->SetCellValue (Lines, 2, PLCNameStr);
				}
				else
				{
					IOGrid->SetCellValue (Lines, 1, "????");
					IOGrid->SetCellValue (Lines, 2, "");
				}
			}
			else if (Lines == 10)
			{
				if (PinUsage[Lines] == IO_FUNC_ANALOG_OUTPUT)
				{
					IOGrid->SetCellValue (Lines, 1, AnalogOutputStr);
					IOGrid->SetCellValue (Lines, 2, "%QB0.1");
				}
				else
				{
					IOGrid->SetCellValue (Lines, 1, "????");
					IOGrid->SetCellValue (Lines, 2, "");
				}
			}
			else if (Lines == 11)
			{
				if (PinUsage[Lines] == IO_FUNC_ANALOG_OUTPUT)
				{
					IOGrid->SetCellValue (Lines, 1, AnalogOutputStr);
					IOGrid->SetCellValue (Lines, 2, "%QB0.2");
				}
				else if (PinUsage[Lines] == IO_FUNC_DIGITAL_OUTPUT)
				{
					IOGrid->SetCellValue (Lines, 1, DigitalOutputStr);
					IOGrid->SetCellValue (Lines, 2, "%QX0.5");
				}
				else
				{
					IOGrid->SetCellValue (Lines, 1, "????");
					IOGrid->SetCellValue (Lines, 2, "");
				}
			}
		}
	}

	EditArduinoCLILocation->SetValue (ArduinoCLILocation);
}  // IONORP_IOEditFrame::RefreshView
// -----------------------------------------------------

void IONORP_IOEditFrame::OnGridSelected (wxGridEvent& event)
{
	int Col = event.GetCol();
	int Row = event.GetRow();
	wxString IOChoices[10];		// Maximum 10 functions per pin

	if (Col != 1) return;

	IOChoices[0] = NotUsedStr;		// Always valid

	// Choose list depending on CPU type and pin number
	// Four first lines are Digital Inputs or Analog Inputs
	if (Row <= 3)
	{
		IOChoices[1] = DigitalInputStr;
		IOChoices[2] = AnalogInputStr;
		IOGrid->SetCellEditor (Row, 1, new wxGridCellChoiceEditor(3, IOChoices, false));
	}
	else if (Row <= 5)  // DI5 / DI6
	{  // TODO : allow to set digital outputs (these lines can be set to direct TTL)
		IOChoices[1] = DigitalInputStr;
		IOGrid->SetCellEditor (Row, 1, new wxGridCellChoiceEditor(2, IOChoices, false));
	}
	else if (Row <= 9)	// DO1..DO4
	{
		IOChoices[1] = DigitalOutputStr;
		IOGrid->SetCellEditor (Row, 1, new wxGridCellChoiceEditor(2, IOChoices, false));
	}
	else if (Row == 10)		// AO1
	{
		IOChoices[1] = AnalogOutputStr;
		IOGrid->SetCellEditor (Row, 1, new wxGridCellChoiceEditor(2, IOChoices, false));
	}
	else  // LED PWM, but can be also set as a digital output
	{
		IOChoices[1] = AnalogOutputStr;
		IOChoices[2] = DigitalOutputStr;
		IOGrid->SetCellEditor (Row, 1, new wxGridCellChoiceEditor(3, IOChoices, false));
	}

	//IOConfigGrid->EnableCellEditControl(true);
	IOGrid->ShowCellEditControl();
}  // IONORP_IOEditFrame::OnGridSelected
// -----------------------------------------------------

void IONORP_IOEditFrame::OnGridChange (wxGridEvent& event)
{
	unsigned int Function=IO_FUNC_NONE;
	int Col = event.GetCol();
	int Row = event.GetRow();
	if (Col != 1) return;

	// Identify selected function
	if (IOGrid->GetCellValue(Row, 1)==NotUsedStr) Function=IO_FUNC_NONE;
	else if (IOGrid->GetCellValue(Row, 1)==DigitalInputStr) Function=IO_FUNC_DIGITAL_INPUT;
	else if (IOGrid->GetCellValue(Row, 1)==DigitalOutputStr) Function=IO_FUNC_DIGITAL_OUTPUT;
	else if (IOGrid->GetCellValue(Row, 1)==AnalogInputStr) Function=IO_FUNC_ANALOG_INPUT;
	else if (IOGrid->GetCellValue(Row, 1)==AnalogOutputStr) Function=IO_FUNC_ANALOG_OUTPUT;

	// TODO : check that function is valid for the pin (normally, the choices in list prevents this, but just to be sure...)
	PinUsage[Row]=Function;
	DataHasChanged = true;
	this->RefreshView();
}  // IONORP_IOEditFrame::OnGridChange
// -----------------------------------------------------

void IONORP_IOEditFrame::OnCompilerSelect (wxCommandEvent& WXUNUSED(event))
{
	if (CompilerChoiceBox->GetSelection()==0) ProjectCompiler=ARDUINO_COMPILER;
	else if (CompilerChoiceBox->GetSelection()==1) ProjectCompiler=PICO_SDK_COMPILER;
	DataHasChanged = true;
}  // IONORP_IOEditFrame::OnCompilerSelect
// -----------------------------------------------------

void IONORP_IOEditFrame::OnBrowseCLI (wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog dlg (this, wxT("Indicate location of arduino_cli.exe"), wxEmptyString, wxEmptyString, wxT("Executable file (*.exe)|*.exe"), wxFD_OPEN+wxFD_FILE_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)	return;

	EditArduinoCLILocation->SetValue (dlg.GetPath());
	ArduinoCLILocation = dlg.GetPath();
	DataHasChanged = true;
}  // IONORP_IOEditFrame::OnBrowseCLI
// -----------------------------------------------------

void IONORP_IOEditFrame::OnArduinoCLIEnter (wxCommandEvent& WXUNUSED(event))
{
	ArduinoCLILocation = EditArduinoCLILocation->GetValue();
	DataHasChanged = true;
}  // IONORP_IOEditFrame::OnArduinoCLIEnter
// -----------------------------------------------------
