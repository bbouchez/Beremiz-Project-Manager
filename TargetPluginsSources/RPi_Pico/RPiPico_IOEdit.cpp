/////////////////////////////////////////////////////////////////////////////
// Name:        RPiPico_IOEdit.cpp
// Purpose:     I/O assignation frame for Beremiz Raspberry Pi Pico plugin
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

#include "RPiPico_IOEdit.h"
#include "RPiPico_DLLMain.h"

extern unsigned int PinUsage[RPI_PICO_IO_LINES];
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

RPiPico_IOEditFrame::RPiPico_IOEditFrame (wxWindow* Parent) : CPicoIOEditorFrame (Parent)
{
	int Pin;
	wxString PinLabel;

	IOGrid->HideRowLabels ();

	IOGrid->SetColSize (0, 100);
	IOGrid->SetColSize (1, 100);
	IOGrid->SetColSize (2, 80);

	for (Pin=0; Pin<RPI_PICO_IO_LINES; Pin++)
	{
		PinLabel="GP"+wxString::Format(wxT("%d"), Pin);
		// Special pins on Pico
		if (Pin == 23) PinLabel = PinLabel + " (PS Mode)";
		else if (Pin == 24) PinLabel = PinLabel + " (VBUS)";
		else if (Pin == 25) PinLabel = PinLabel + " (LED)";
		else if (Pin == 29) PinLabel = PinLabel + " (VSYS)";
		IOGrid->SetCellValue (Pin, 0, PinLabel);
	}

	for (int i=0; i<RPI_PICO_IO_LINES; i++)
	{
		IOGrid->SetReadOnly (i, 0, true);
		IOGrid->SetReadOnly (i, 2, true);
	}

#ifdef __TARGET_WIN__
	PinoutBMP = new wxBitmap ("rpi_pico_pinout", wxBITMAP_TYPE_BMP_RESOURCE);
#endif  // __TARGET_WIN__
#ifdef __TARGET_LINUX__
	PinoutBMP = new wxBitmap ("./RPiPico_Images/pico.bmp", wxBITMAP_TYPE_BMP);
#endif  // TARGET_LINUX__
	this->PicoBitmap->SetBitmap (*PinoutBMP);
}  // RPiPico_IOEditFrame::IONORP_IOEditFrame
// -----------------------------------------------------

RPiPico_IOEditFrame::~RPiPico_IOEditFrame ()
{
	if (PinoutBMP)
		delete PinoutBMP;
}  // RPiPico_IOEditFrame::~RPiPico_IOEditFrame
// -----------------------------------------------------

void RPiPico_IOEditFrame::OnClose (wxCloseEvent& WXUNUSED(event))
{
	this->Show(false);
}  // RPiPico_IOEditFrame::OnClose
// -----------------------------------------------------

void RPiPico_IOEditFrame::RefreshView (void)
{
	int Lines;
	char PLCNameStr[256];

	// Display selected compiler
	if (ProjectCompiler==ARDUINO_COMPILER) CompilerChoiceBox->SetSelection(0);
	else if (ProjectCompiler==PICO_SDK_COMPILER) CompilerChoiceBox->SetSelection(1);

	for (Lines=0; Lines<RPI_PICO_IO_LINES; Lines++)
	{
		switch (PinUsage[Lines])
		{
			case IO_FUNC_NONE :
				IOGrid->SetCellValue (Lines, 1, NotUsedStr);
				IOGrid->SetCellValue (Lines, 2, "---");
				break;
			case IO_FUNC_DIGITAL_INPUT :
				IOGrid->SetCellValue (Lines, 1, DigitalInputStr);
				sprintf (&PLCNameStr[0], "%%IX0.%d", Lines);
				IOGrid->SetCellValue (Lines, 2, PLCNameStr);
				break;
			case IO_FUNC_DIGITAL_OUTPUT :
				IOGrid->SetCellValue (Lines, 1, DigitalOutputStr);
				sprintf (&PLCNameStr[0], "%%QX0.%d", Lines);
				IOGrid->SetCellValue (Lines, 2, PLCNameStr);
				break;
			case IO_FUNC_ANALOG_INPUT :
				IOGrid->SetCellValue (Lines, 1, AnalogInputStr);
				sprintf (&PLCNameStr[0], "%%IW0.%d", Lines);
				IOGrid->SetCellValue (Lines, 2, PLCNameStr);
				break;
			case IO_FUNC_ANALOG_OUTPUT :
				IOGrid->SetCellValue (Lines, 1, AnalogOutputStr);
				sprintf (&PLCNameStr[0], "%%QB0.%d", Lines);
				IOGrid->SetCellValue (Lines, 2, PLCNameStr);
				break;
			case IO_FUNC_SERVO_OUTPUT :
				IOGrid->SetCellValue (Lines, 1, ServoOutputStr);
				sprintf (&PLCNameStr[0], "%%QB0.%d", Lines);
				IOGrid->SetCellValue (Lines, 2, PLCNameStr);
				break;
			default :
				IOGrid->SetCellValue (Lines, 1, "????");
				IOGrid->SetCellValue (Lines, 2, "");
		}
	}

	EditArduinoCLILocation->SetValue (ArduinoCLILocation);
}  // RPiPico_IOEditFrame::RefreshView
// -----------------------------------------------------

void RPiPico_IOEditFrame::OnGridSelected (wxGridEvent& event)
{
	int Col = event.GetCol();
	int Row = event.GetRow();
	wxString IOChoices[10];		// Maximum 10 functions per pin

	if (Col != 1) return;

	IOChoices[0] = NotUsedStr;		// Always valid

	// Choose list depending on CPU pin number
	// All pins have "Not used" capability at least
	IOChoices[0] = NotUsedStr;

	// Pins 0 to 15 can be analog outputs, remaining pins are copies of channels 0 to 15
	// We reserve the same pins for servo outputs, this should cover most application to have 16 pins shared between analog outputs and servo outputs

	if ((Row <= 15))
	{  // First 16 GPIO have analog output and servo capabilities (other pins are copies)
		IOChoices[1] = DigitalInputStr;
		IOChoices[2] = DigitalOutputStr;
		IOChoices[3] = AnalogOutputStr;
		IOChoices[4] = ServoOutputStr;
		IOGrid->SetCellEditor(Row, 1, new wxGridCellChoiceEditor(5, IOChoices, false));
	}
	else if ((Row >= 26) && (Row <=28))
	{  // Analog inputs can also be used as digital inputs and digital outputs
		IOChoices[1] = DigitalInputStr;
		IOChoices[2] = DigitalOutputStr;
		IOChoices[3] = AnalogInputStr;
		IOGrid->SetCellEditor(Row, 1, new wxGridCellChoiceEditor(4, IOChoices, false));
	}
	else if (Row == 23)
	{  // Reserved pin to control SMPS save mode : Can only be a digital output
		IOChoices[1] = DigitalOutputStr;
		IOGrid->SetCellEditor(Row, 1, new wxGridCellChoiceEditor(2, IOChoices, false));
	}
	else if (Row == 24)
	{  // Reserved pin for CBUS sense : can only be a digital input
		IOChoices[1] = DigitalInputStr;
		IOGrid->SetCellEditor(Row, 1, new wxGridCellChoiceEditor(2, IOChoices, false));
	}
	else if (Row == 25)
	{  // Reserved pin for LED control : can be digital output or analog output
		IOChoices[1] = DigitalOutputStr;
		IOChoices[2] = AnalogOutputStr;
		IOGrid->SetCellEditor(Row, 1, new wxGridCellChoiceEditor(3, IOChoices, false));
	}
	else if (Row == 29)
	{  // Reserved pin for VSYS/3 sense : can only be a analog input
		IOChoices[1] = AnalogInputStr;
		IOGrid->SetCellEditor(Row, 1, new wxGridCellChoiceEditor(2, IOChoices, false));
	}
	else
	{   // All other pins are digital I/Os only
		IOChoices[1] = DigitalInputStr;
		IOChoices[2] = DigitalOutputStr;
		IOGrid->SetCellEditor(Row, 1, new wxGridCellChoiceEditor(3, IOChoices, false));		// Stop list at "Digital output"
	}

	//IOConfigGrid->EnableCellEditControl(true);
	IOGrid->ShowCellEditControl();
}  // RPiPico_IOEditFrame::OnGridSelected
// -----------------------------------------------------

void RPiPico_IOEditFrame::OnGridChange (wxGridEvent& event)
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
	else if (IOGrid->GetCellValue(Row, 1)==ServoOutputStr) Function=IO_FUNC_SERVO_OUTPUT;

	// TODO : check that function is valid for the pin (normally, the choices in list prevents this, but just to be sure...)
	PinUsage[Row]=Function;
	DataHasChanged = true;
	this->RefreshView();
}  // RPiPico_IOEditFrame::OnGridChange
// -----------------------------------------------------

void RPiPico_IOEditFrame::OnCompilerSelect (wxCommandEvent& WXUNUSED(event))
{
	if (CompilerChoiceBox->GetSelection()==0) ProjectCompiler=ARDUINO_COMPILER;
	else if (CompilerChoiceBox->GetSelection()==1) ProjectCompiler=PICO_SDK_COMPILER;
	DataHasChanged = true;
}  // RPiPico_IOEditFrame::OnCompilerSelect
// -----------------------------------------------------

void RPiPico_IOEditFrame::OnBrowseCLI (wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog dlg (this, wxT("Indicate location of arduino_cli.exe"), wxEmptyString, wxEmptyString, wxT("Executable file (*.exe)|*.exe"), wxFD_OPEN+wxFD_FILE_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)	return;

	EditArduinoCLILocation->SetValue (dlg.GetPath());
	ArduinoCLILocation = dlg.GetPath();
	DataHasChanged = true;
}  // RPiPico_IOEditFrame::OnBrowseCLI
// -----------------------------------------------------

void RPiPico_IOEditFrame::OnArduinoCLIEnter (wxCommandEvent& WXUNUSED(event))
{
	ArduinoCLILocation = EditArduinoCLILocation->GetValue();
	DataHasChanged = true;
}  // RPiPico_IOEditFrame::OnArduinoCLIEnter
// -----------------------------------------------------
