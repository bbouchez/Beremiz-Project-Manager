/////////////////////////////////////////////////////////////////////////////
// Name:        RPiPico_Plugin.cpp
// Purpose:     Exposed DLL functions
// Author:      Benoit BOUCHEZ
// Created:     12/05/2022
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

#include "BeremizProjectManager_TargetsAPI.h"
#include "RPiPico_DLLMain.h"
#include "RPiPico_IOEdit.h"

#include <wx/xml/xml.h>
#include <wx/dir.h>

extern "C" int CMD_SHOW_WINDOW;
extern "C" int CMD_HIDE_WINDOW;
extern "C" int CMD_START_COMPILATION;

static wxString ProjectPath;			// Folder where project is stored on local machine
static wxString TargetsDirectory;		// Folder where target source files are stored
static wxString ProjectName;			// Extracted for project path

// Project configuration data
unsigned int PinUsage [RPI_PICO_IO_LINES];
int ProjectCompiler;				// 0 : Arduino, 1 : Raspberry Pico SDK
wxString ArduinoCLILocation;

bool DataHasChanged = false;

RPiPico_IOEditFrame* Editor=0;

static void CleanConfiguration (void)
{
	for (int Lines=0; Lines<RPI_PICO_IO_LINES; Lines++)
	{
		PinUsage[Lines] = IO_FUNC_NONE;
	}
	ProjectCompiler = ARDUINO_COMPILER;
	ArduinoCLILocation = wxEmptyString;
}  // CleanConfiguration
// -----------------------------------------------------

extern "C"
{

void EXPORT_INTERFACE TP_GetPluginName (char* Name)
{
	strcpy (Name, "Raspberry Pi Pico");
}  // TP_GetPluginName
// -----------------------------------------------------

void EXPORT_INTERFACE TP_GetPluginVersion (uint32_t* Major, uint32_t* Minor, uint32_t* Build, uint32_t* Revision)
{
	*Major = 0;
	*Minor = 4;
	*Build = 0;
	*Revision = 0;
}  // TP_GetPluginVersion
// -----------------------------------------------------

void EXPORT_INTERFACE TP_SetProjectPath (char* Path, int32_t StrEncoding)
{
	switch (StrEncoding)
	{
		case STRING_ENCODING_C : ProjectPath = Path; break;			// wxWidgets 3.x allows direct conversion from C to wxString
		case STRING_ENCODING_UTF8 : ProjectPath = wxString::FromUTF8 (Path); break;
	}

	ProjectName = ProjectPath.AfterLast(wxFILE_SEP_PATH);
}  // TP_SetProjectPath
// -----------------------------------------------------

void EXPORT_INTERFACE TP_SetTargetsPath (char* Path, int32_t StrEncoding)
{
	switch (StrEncoding)
	{
		case STRING_ENCODING_C : TargetsDirectory = Path; break;			// wxWidgets 3.x allows direct conversion from C to wxString
		case STRING_ENCODING_UTF8 : TargetsDirectory = wxString::FromUTF8 (Path); break;
	}
}  // TP_SetTargetsPath
// -----------------------------------------------------

int32_t EXPORT_INTERFACE TP_LoadTargetProjectData (void)
{
	wxXmlDocument doc;
	wxXmlNode* RootNode;
	wxString ProjectFilePath;
	wxString TestString;
	wxXmlNode* TopNode;
	wxXmlNode* IOConfigNode;
	int PortIndex;
	wxString IOPortStr;

	CleanConfiguration();

	ProjectFilePath=ProjectPath+"/rpi_pico_target.xml";

	if (!doc.Load(ProjectFilePath)) return ERR_TARGET_PLUGIN_FILE_ERROR;  // File does not exist or can not be loaded

	// Check that the XML file is a Beremiz project file
	RootNode=doc.GetRoot();
	if (RootNode->GetName() != "beremiz_project") return ERR_TARGET_PLUGIN_INVALID_FILE;  // Not a Beremiz project file ?
	RootNode->GetAttribute ("type", &TestString);
	if (TestString != "rpi_pico") return ERR_TARGET_PLUGIN_INVALID_FILE;
	// Check that Beremiz project file version is supported
	RootNode->GetAttribute ("version", &TestString);
	if (TestString != "1") return ERR_TARGET_PLUGIN_INVALID_FILE_VERSION;   // Project file version is not supported

	// Next level node can be "cpu" or "ioconfig"
	TopNode=RootNode->GetChildren();

	while (TopNode!=0)
	{
		if (TopNode->GetName()=="ioconfig")
		{
			IOConfigNode=TopNode->GetChildren();
			do
			{
				if (IOConfigNode->GetName()=="ioport")
				{
					IOConfigNode->GetAttribute ("index", &IOPortStr);
					PortIndex = wxAtoi (IOPortStr);
					if ((PortIndex>=0) && (PortIndex<=RPI_PICO_IO_LINES))
					{
						IOConfigNode->GetAttribute ("mode", &IOPortStr);
						if (IOPortStr=="di") PinUsage[PortIndex]=IO_FUNC_DIGITAL_INPUT;
						else if (IOPortStr=="do") PinUsage[PortIndex]=IO_FUNC_DIGITAL_OUTPUT;
						else if (IOPortStr=="ai") PinUsage[PortIndex]=IO_FUNC_ANALOG_INPUT;
						else if (IOPortStr == "ao") PinUsage[PortIndex]=IO_FUNC_ANALOG_OUTPUT;
						else if (IOPortStr == "so") PinUsage[PortIndex]=IO_FUNC_SERVO_OUTPUT;
						else PinUsage[PortIndex]=IO_FUNC_NONE;
					}
				}  // name = ioport

				IOConfigNode=IOConfigNode->GetNext();
			} while (IOConfigNode != 0);
		}  // ioconfig

		else if (TopNode->GetName() == "compiler")
		{
			TopNode->GetAttribute ("chain", &TestString);
			if (TestString == "pico_sdk") ProjectCompiler = PICO_SDK_COMPILER;
			else ProjectCompiler = ARDUINO_COMPILER;
		}

		else if (TopNode->GetName() == "arduinocli")
		{
			TopNode->GetAttribute ("location", &ArduinoCLILocation);
		}

		TopNode=TopNode->GetNext();
	};

	DataHasChanged = false;

	return TARGET_PLUGIN_NO_ERROR;
}  // TP_LoadTargetProjectData
// -----------------------------------------------------

int32_t EXPORT_INTERFACE TP_SaveTargetProjectData (void)
{
	FILE* ProjectFile;
	int IOPortIndex;
	char IOConfStr[256];

	ProjectFile=fopen (ProjectPath+"/rpi_pico_target.xml", "wt");
	if (ProjectFile==0) return ERR_TARGET_PLUGIN_FILE_ERROR;		// Can not create project file

	// Save XML header and create top level tag
	fprintf (ProjectFile, "<?xml version='1.0' encoding='utf-8'?>\n");
	fprintf (ProjectFile, "<beremiz_project type=\"rpi_pico\" version=\"1\">\n");

	// Save I/O configuration
	fprintf (ProjectFile, "  <ioconfig>\n");

	for (IOPortIndex=0; IOPortIndex<RPI_PICO_IO_LINES; IOPortIndex++)
	{
		sprintf (&IOConfStr[0], "    <ioport index=\"%d\" mode=\"", IOPortIndex);
		switch (PinUsage[IOPortIndex])
		{
			case IO_FUNC_NONE : strcat (&IOConfStr[0], "nc\"/>\n"); break;
			case IO_FUNC_DIGITAL_INPUT : strcat (&IOConfStr[0], "di\"/>\n"); break;
			case IO_FUNC_DIGITAL_OUTPUT : strcat (&IOConfStr[0], "do\"/>\n"); break;
			case IO_FUNC_ANALOG_INPUT : strcat (&IOConfStr[0], "ai\"/>\n"); break;
			case IO_FUNC_ANALOG_OUTPUT : strcat (&IOConfStr[0], "ao\"/>\n"); break;
			case IO_FUNC_SERVO_OUTPUT : strcat (&IOConfStr[0], "so\"/>\n"); break;
			default : strcat (&IOConfStr[0], "nc\"/>\n"); break;
		}
		fprintf (ProjectFile, "%s", IOConfStr);
	}

	fprintf (ProjectFile, "  </ioconfig>\n");

	// Save compiler type
	if (ProjectCompiler == ARDUINO_COMPILER)  fprintf (ProjectFile, "  <compiler chain=\"arduino\" />\n");
	if (ProjectCompiler == PICO_SDK_COMPILER)  fprintf (ProjectFile, "  <compiler chain=\"pico_sdk\" />\n");

	// Save Arduino CLI location
	fprintf (ProjectFile, "  <arduinocli location=\"");
	fprintf (ProjectFile, ArduinoCLILocation);
	fprintf (ProjectFile, "\" />\n");

	// Close project tag
	fprintf (ProjectFile, "</beremiz_project>\n");
	fclose (ProjectFile);

	DataHasChanged = false;

	return TARGET_PLUGIN_NO_ERROR;
}  // TP_SaveTargetProjectData
// -----------------------------------------------------

void OpenEditor (uint32_t EditorIndex)
{
	if (Editor==0)
		Editor = new RPiPico_IOEditFrame (NULL);

	if (Editor)
	{
		Editor->Show(true);
		Editor->RefreshView();
		Editor->SetFocus();  // Put on top
	}
}  // OpenEditor
// -----------------------------------------------------

void CloseEditor (int32_t EditorIndex)
{
#ifdef __TARGET_WIN__
	if (Editor)
		Editor->Show(false);
#endif  // __TARGET_WIN__
#ifdef __TARGET_LINUX__
	if (Editor)
	{
		delete Editor;
		Editor = 0;
	}
#endif  // __TARGET_LINUX__
}  // CloseEditor
// -----------------------------------------------------

int32_t EXPORT_INTERFACE TP_OpenEditor(void* WXUNUSED(Parent), uint32_t EditorIndex)
{
#ifdef __TARGET_WIN__
	// Send a message to wx thread to show a frame
    wxThreadEvent *event = new wxThreadEvent(wxEVT_THREAD, CMD_SHOW_WINDOW);
    event->SetInt(EditorIndex);
    wxQueueEvent(wxApp::GetInstance(), event);

	return TARGET_PLUGIN_NO_ERROR;
#endif // _TARGET_WIN__
	#ifdef __TARGET_LINUX__
	OpenEditor (EditorIndex);
	return TARGET_PLUGIN_NO_ERROR;
#endif  // __TARGET_LINUX__
}  // TP_OpenEditor
// -----------------------------------------------------

void EXPORT_INTERFACE TP_CloseEditor(int32_t EditorIndex)
{
#ifdef __TARGET_WIN__
    wxThreadEvent *event = new wxThreadEvent(wxEVT_THREAD, CMD_HIDE_WINDOW);
	event->SetInt(EditorIndex);
    wxQueueEvent(wxApp::GetInstance(), event);
#endif  // __TARGET_WIN__
#ifdef __TARGET_LINUX__
	CloseEditor (EditorIndex);
#endif  //__TARGET_LINUX__
}  // TP_CloseEditor
// -----------------------------------------------------

int32_t EXPORT_INTERFACE TP_CreateBeremizProjectFiles (void)
{
	bool FileOK;

	// Copy XML files from basic project into the new folder (use a basic project that can be compiled)
	FileOK = wxCopyFile (TargetsDirectory+"Targets\\RP2040\\RPI_PICO\\beremiz.xml", ProjectPath+"\\beremiz.xml");
	FileOK &= wxCopyFile (TargetsDirectory+"Targets\\RP2040\\RPI_PICO\\plc.xml", ProjectPath+"\\plc.xml");

	if (FileOK == false) return ERR_TARGET_PLUGIN_FILE_ERROR;

	return TARGET_PLUGIN_NO_ERROR;
}  // TP_CreateBeremizProjectFiles
// -----------------------------------------------------

int32_t EXPORT_INTERFACE TP_GenerateTargetFramework (void)
{
	wxString BaseFilesPath;
	wxString RuntimeDir;

	RuntimeDir = ProjectPath+"/"+ProjectName+"_arduino/";
	// Create directory for Arduino compilation
	wxMkDir (RuntimeDir, wxS_DIR_DEFAULT);

	// Copy generic runtime files
	// TODO : use return value from wxCopyFile to report error
	BaseFilesPath = TargetsDirectory+"Common\\";
	wxCopyFile (BaseFilesPath+"accessor.h", RuntimeDir+"accessor.h");
	wxCopyFile (BaseFilesPath+"beremiz.h", RuntimeDir+"beremiz.h");
	wxCopyFile (BaseFilesPath+"iec_std_FB.h", RuntimeDir+"iec_std_FB.h");
	wxCopyFile (BaseFilesPath+"iec_std_FB.c", RuntimeDir+"iec_std_FB.c");
	wxCopyFile (BaseFilesPath+"iec_std_lib.c", RuntimeDir+"iec_std_lib.c");
	wxCopyFile (BaseFilesPath+"iec_std_lib.h", RuntimeDir+"iec_std_lib.h");
	wxCopyFile (BaseFilesPath+"iec_types.h", RuntimeDir+"iec_types.h");
	wxCopyFile (BaseFilesPath+"iec_types_all.h", RuntimeDir+"iec_types_all.h");
	wxCopyFile (BaseFilesPath+"iec_std_functions.h", RuntimeDir+"iec_std_functions.h");

	// Copy target specific runtime files
	// TODO : use return value from wxCopyFile to report error
	if (ProjectCompiler==ARDUINO_COMPILER)
	{
		BaseFilesPath = TargetsDirectory+"Targets\\RP2040\\RPI_PICO\\";
		wxCopyFile (BaseFilesPath+"pico_runtime.ino", RuntimeDir+ProjectName+"_arduino.ino");
	}
	else
	{
		wxMessageBox ("Only Arduino compiler is supported for now", "Raspberry Pi Pico Generate Target Framework");
		return ERR_TARGET_PLUGIN_NON_SUPPORTED_FEATURE;
	}

	return TARGET_PLUGIN_NO_ERROR;
}  // TP_GenerateTargetFramework
// -----------------------------------------------------

int32_t EXPORT_INTERFACE TP_CopyPLCFilesForCompilation (void)
{
	wxString RuntimeDir;
	wxString BuildDir;
	wxDir Directory;
	bool FoundCFile;
	wxString CFilename;

	if (ProjectCompiler != ARDUINO_COMPILER)
		return ERR_TARGET_PLUGIN_NON_SUPPORTED_FEATURE;

	BuildDir = ProjectPath+"/build/";

	// TODO : report error if any file can not be copied

	// Processing for Arduino
	RuntimeDir = ProjectPath+"/"+ProjectName+"_arduino/";

	// Copy files generated by MatIEC
	// IMPORTANT : for now, we are limited to ONE resource and it must be called Resource1
	// TODO : it is better to copy all .h and .c files from generated files (this will include the C files too)
	wxCopyFile (BuildDir+"config.c", RuntimeDir+"config.c");
	wxCopyFile (BuildDir+"config.h", RuntimeDir+"config.h");
	wxCopyFile (BuildDir+"POUS.h", RuntimeDir+"POUS.h");
	wxCopyFile (BuildDir+"POUS.c", RuntimeDir+"POUS2.h");		// Rename file
	wxCopyFile (BuildDir+"Resource1.c", RuntimeDir+"Resource1.c");

	// copy c_ext source files (for the C extensions)
	// These files are named CFile_0.c, CFile_1.c, etc...
	// TODO : make a loop to find all CFile_*.c files and copy them
	// Note a bug in Beremiz : if the C extension number is changed, it keeps the old c_ext file in build directory
	// This can be solved be cleaning the build directory before generating C code (but this should be done in Beremiz not here)
	Directory.Open (BuildDir);
	FoundCFile = Directory.GetFirst (&CFilename, "CFile_*.c");
	while (FoundCFile)
	{
		wxCopyFile (BuildDir+CFilename, RuntimeDir+CFilename);
		FoundCFile = Directory.GetNext (&CFilename);
	}

	return TARGET_PLUGIN_NO_ERROR;
}  // TP_CopyPLCFilesForCompilation
// -----------------------------------------------------

//! returns true if at least one analog input is used on the project
bool CheckAnalogInputs (void)
{
	for (int AnalogPin=0; AnalogPin<RPI_PICO_IO_LINES; AnalogPin++)
	{
		if (PinUsage[AnalogPin]==IO_FUNC_ANALOG_INPUT) return true;
	}

	return false;
}  // CheckAnalogInputs
// -----------------------------------------------------------

//! Returns true if at least one analog output is used on the project
bool CheckAnalogOutputs (void)
{
	for (int Pin=0; Pin<RPI_PICO_IO_LINES; Pin++)
	{
		if (PinUsage[Pin] == IO_FUNC_ANALOG_OUTPUT) return true;
	}

	return false;
}  // CheckAnalogOutputs
// -----------------------------------------------------------

//! Returns true if at least one servo output is used in the project
bool CheckServoOutputs (void)
{
	for (int Pin=0; Pin<RPI_PICO_IO_LINES; Pin++)
	{
		if (PinUsage[Pin] == IO_FUNC_SERVO_OUTPUT) return true;
	}

	return false;
}  // CheckServoOutputs
// -----------------------------------------------------------

int32_t EXPORT_INTERFACE TP_GenerateIOConfigurationFiles (void)
{
	FILE* IOFile;
	wxString SourceLine;
	int Pin;
	bool AnalogInputsUsed;
	bool AnalogOutputsUsed;
	bool ServoOutputsUsed;
	wxString ConfigFileName;

	ConfigFileName = ProjectPath+"/"+ProjectPath.AfterLast(wxFILE_SEP_PATH)+"_arduino/plc_ioconfig.cpp";

	if (ProjectCompiler!=ARDUINO_COMPILER)
	{
		wxMessageBox ("I/O configuration file generation only supported for Arduino compiler", "Raspberry Pi Pico Generate I/O configuration files");
		return ERR_TARGET_PLUGIN_NON_SUPPORTED_FEATURE;
	}

	AnalogInputsUsed = CheckAnalogInputs();
	AnalogOutputsUsed = CheckAnalogOutputs();
	ServoOutputsUsed = CheckServoOutputs();

	// Try to create the file
	IOFile = fopen (ConfigFileName, "wt");
	if (IOFile==0)
	{
		return ERR_TARGET_PLUGIN_FILE_ERROR;		// Can not create the file
	}

	// Write the various constant parts in the file
	// TODO : move this part in a function
	fprintf (IOFile, "/**********************************************************************/\n");
	fprintf (IOFile, "/* This file has been generated automatically by RPi Pico plugin	    */\n");
	fprintf (IOFile, "/* for Beremiz Project Manager                                        */\n");
	fprintf (IOFile, "/* WARNING : DO NOT EDIT MANUALLY THIS FILE                           */\n");
	fprintf (IOFile, "/**********************************************************************/\n");
	fprintf (IOFile, "\n");
	fprintf (IOFile, "#include \"iec_types.h\"\n");
	fprintf (IOFile, "#include <Arduino.h>\n");
	fprintf (IOFile, "#include <Servo.h>\n");
	fprintf (IOFile, "\n");

	fprintf (IOFile, "uint8_t DigitalInput[30];\n");
	fprintf (IOFile, "uint8_t DigitalOutput[30];\n");
	if (AnalogInputsUsed)
	{
		fprintf (IOFile, "uint16_t AnalogInput[4];\n");
	}
	if (AnalogOutputsUsed)
	{  // TODO : we can optimize this by counting the real number of analog outputs
		// However, this will make difficult to optimize connections between variables and physical outputs
		// For now, we simply create the 16 PWM outputs available on Pico (PWM channels)
		fprintf (IOFile, "uint8_t AnalogOutput[16];\n");
	}
	if (ServoOutputsUsed)
	{  // TODO : we can optimize this by counting the real number of servo outputs
		// However, this will make difficult to optimize connections between variables and physical outputs
		// For now, we simply create the 16 PWM outputs available on Pico (PWM channels)
		fprintf (IOFile, "uint8_t ServoOutput[16];\n");
	}

	fprintf (IOFile, "\n");

	// Generate variable declaration depending on declared I/O pins
	for (Pin=0; Pin<RPI_PICO_IO_LINES; Pin++)
	{
		if (PinUsage[Pin]==IO_FUNC_DIGITAL_INPUT)
		{
			SourceLine="IEC_BOOL* __IX0_"+wxString::Format(wxT("%d"), Pin)+"=&DigitalInput["+wxString::Format(wxT("%d"), Pin)+"];\n";
			fprintf (IOFile, SourceLine);
		}
		else if (PinUsage[Pin]==IO_FUNC_DIGITAL_OUTPUT)
		{
			SourceLine="IEC_BOOL* __QX0_"+wxString::Format(wxT("%d"), Pin)+"=&DigitalOutput["+wxString::Format(wxT("%d"), Pin)+"];\n";
			fprintf (IOFile, SourceLine);
		}
		else if (PinUsage[Pin]==IO_FUNC_ANALOG_OUTPUT)
		{
			SourceLine="IEC_USINT* __QB0_"+wxString::Format(wxT("%d"), Pin)+"=&AnalogOutput["+wxString::Format(wxT("%d"), Pin)+"];\n";
			fprintf (IOFile, SourceLine);
		}
		else if (PinUsage[Pin]==IO_FUNC_ANALOG_INPUT)
		{
			SourceLine="IEC_UINT* __IW0_"+wxString::Format(wxT("%d"), Pin)+"=&AnalogInput["+wxString::Format(wxT("%d"), Pin-26)+"];\n";   // Pins 26 to 29 are analog inputs 0 to 3
			fprintf (IOFile, SourceLine);
		}
		else if (PinUsage[Pin]==IO_FUNC_SERVO_OUTPUT)
		{
			SourceLine="IEC_BYTE* __QB0_"+wxString::Format(wxT("%d"), Pin)+"=&ServoOutput["+wxString::Format(wxT("%d"), Pin)+"];\n";
			fprintf (IOFile, SourceLine);
		}
	}
	fprintf (IOFile, "\n");

	// Create as many servo objects as declared servo outputs
	if (ServoOutputsUsed)
	{
		for (Pin=0; Pin<RPI_PICO_IO_LINES; Pin++)
		{
			if (PinUsage[Pin]==IO_FUNC_SERVO_OUTPUT)
			{
				SourceLine = "Servo __ServoOut"+wxString::Format(wxT("%d"), Pin)+";\n";
				fprintf (IOFile, SourceLine);
			}
		}
		fprintf (IOFile, "\n");
	}

	// *** Generate ConfigurePLCIO() function ***
	fprintf (IOFile, "void ConfigurePLCIO (void)\n{\n");
	for (Pin=0; Pin<RPI_PICO_IO_LINES; Pin++)
	{
		if (PinUsage[Pin]==IO_FUNC_DIGITAL_INPUT)
		{
			SourceLine = "  pinMode ("+wxString::Format(wxT("%d"), Pin)+", INPUT);\n";
			fprintf (IOFile, SourceLine);
		}
		else if (PinUsage[Pin]==IO_FUNC_DIGITAL_OUTPUT)
		{
			SourceLine = "  pinMode ("+wxString::Format(wxT("%d"), Pin)+", OUTPUT);\n";
			fprintf (IOFile, SourceLine);
		}
		// Analog outputs do not need to be configured here (they are set automatically by the analogWrite function)
		// Analog inputs are automatically created when AnalogRead function is called
		else if (PinUsage[Pin]==IO_FUNC_SERVO_OUTPUT)
		{
			SourceLine = "  __ServoOut"+wxString::Format(wxT("%d"), Pin)+".attach ("+wxString::Format(wxT("%d"), Pin)+");\n";
			fprintf (IOFile, SourceLine);
		}
	}
	fprintf (IOFile, "}\n");

	// *** Generate AcquirePLCInputs() function ***
	fprintf (IOFile, "\nvoid AcquirePLCInputs (void)\n{\n");

	for (Pin=0; Pin<RPI_PICO_IO_LINES; Pin++)
	{
		if (PinUsage[Pin]==IO_FUNC_DIGITAL_INPUT)
		{
			SourceLine = "  DigitalInput["+wxString::Format(wxT("%d"), Pin)+"]=digitalRead("+wxString::Format(wxT("%d"), Pin)+");\n";
			fprintf (IOFile, SourceLine);
		}
		else if (PinUsage[Pin]==IO_FUNC_ANALOG_INPUT)
		{  // TODO : check if we read pin number (26 to 29) with analogRead or analog input index
			SourceLine = "  AnalogInput["+wxString::Format(wxT("%d"), Pin-26)+"]=analogRead("+wxString::Format(wxT("%d"), Pin)+");\n";		// Pins 26 to 29 are analog inputs 0 to 3
			fprintf (IOFile, SourceLine);
		}
	}

	fprintf (IOFile, "}\n");

	// *** Generate UpdatePLCOutputs() function ***
	fprintf (IOFile, "\nvoid UpdatePLCOutputs (void)\n{\n");

	for (Pin=0; Pin<RPI_PICO_IO_LINES; Pin++)
	{
		if (PinUsage[Pin]==IO_FUNC_DIGITAL_OUTPUT)
		{
			SourceLine = "  digitalWrite ("+wxString::Format(wxT("%d"), Pin)+", DigitalOutput["+wxString::Format(wxT("%d"), Pin)+"]);\n";
			fprintf (IOFile, SourceLine);
		}
		else if (PinUsage[Pin]==IO_FUNC_ANALOG_OUTPUT)
		{
			SourceLine = "  analogWrite ("+wxString::Format(wxT("%d"), Pin)+", AnalogOutput["+wxString::Format(wxT("%d"), Pin)+"]);\n";
			fprintf (IOFile, SourceLine);
		}
		else if (PinUsage[Pin]==IO_FUNC_SERVO_OUTPUT)
		{
			SourceLine = "  __ServoOut"+wxString::Format(wxT("%d"), Pin)+".write (ServoOutput["+wxString::Format(wxT("%d"), Pin)+"]);\n";
			fprintf (IOFile, SourceLine);
		}
	}

	fprintf (IOFile, "}\n");

	fclose (IOFile);

	return TARGET_PLUGIN_NO_ERROR;
}  // TP_GenerateIOConfigurationFiles
// -----------------------------------------------------

int32_t EXPORT_INTERFACE TP_CleanForBuild (void)
{
	wxString BuildDir;
	wxString RuntimeDir;
	wxDir Directory;
	bool FoundFile;
	wxString Filename;

	// Remove all files in build directory
	BuildDir = ProjectPath+"/build/";
	Directory.Open (BuildDir);
	FoundFile = Directory.GetFirst (&Filename, "*.*");

	while (FoundFile)
	{
		wxRemoveFile (BuildDir + Filename);
		FoundFile = Directory.GetNext (&Filename);
	}

	Directory.Close ();

	if (ProjectCompiler == ARDUINO_COMPILER)
	{
		// Remove all files in runtime directory
		RuntimeDir = ProjectPath+"/"+ProjectName+"_arduino/";
		Directory.Open (RuntimeDir);
		FoundFile = Directory.GetFirst (&Filename, "*.*");

		while (FoundFile)
		{
			wxRemoveFile (RuntimeDir + Filename);
			FoundFile = Directory.GetNext (&Filename);
		}

		Directory.Close ();
	}
	else
	{
		wxMessageBox ("Clean only supported for Arduino compiler", "Raspberry Pi Pico Clean for build");
		return ERR_TARGET_PLUGIN_NON_SUPPORTED_FEATURE;
	}

	return TARGET_PLUGIN_NO_ERROR;
}  // TP_CleanForBuild
// -----------------------------------------------------

uint32_t EXPORT_INTERFACE TP_GetNumberOfEditors (void)
{
	// Only basic editor for now
	// TODO : we can add a Modbus entry later to use the serial port
	return 1;
}  // TP_GetNumberOfEditors
// -----------------------------------------------------

void EXPORT_INTERFACE TP_GetEditorLabel (uint32_t EditorIndex, char* EditorName, int32_t* TreeIconIndex)
{
	switch (EditorIndex)
	{
		case 0 :
			strcpy (EditorName, "Raspberry Pi Pico");
			*TreeIconIndex = TP_TREE_ICON_CPU;
			break;
		default :
			strcpy (EditorName, "");
			*TreeIconIndex = TP_TREE_ICON_NONE;
	}
}  // TP_GetEditorLabel
// -----------------------------------------------------

int32_t EXPORT_INTERFACE TP_DataHasChanged (void)
{
	if (DataHasChanged) return 1;
	return 0;
}  // TP_DataHasChanged
// -----------------------------------------------------

int32_t EXPORT_INTERFACE TP_IsOptionSupported (uint32_t Option)
{
	switch (Option)
	{
		case TP_OPTION_TARGET_START : return 0;
		case TP_OPTION_TARGET_STOP : return 0;
		case TP_OPTION_TARGET_AUTO_START : return 0;

		case TP_OPTION_COMPILATION_EXTERNAL : return 1;		// Project can always be compiled externally by Pico SDK or Arduino if needed
		case TP_OPTION_PLUGIN_COMPILER : return 1;			// TODO : check if using Pico SDK would return 0
		default : return -1;		// Option is not known, assume it is not supported
	}
}  // TP_IsOptionSupported
// -----------------------------------------------------

int32_t EXPORT_INTERFACE TP_StartCompilation (void)
{
	FILE* BatFile;

	if (ArduinoCLILocation==wxEmptyString) return -1;		// Path to compiler not defined, can not start compilation

	// Create a batch file to launch compiler as we want the shell window to remain opened to see compilation results
	// Batch will be launched from DLL main thread to respect wxExecute restrictions. File is created here so we can report creation problems if needed
	BatFile = fopen (ProjectPath+"\\launch_cli.bat", "wt");
	if (BatFile == 0) return ERR_TARGET_PLUGIN_FILE_ERROR;

	fprintf (BatFile, "echo off\n");
	fprintf (BatFile, "\""+ArduinoCLILocation + "\" compile -v -b arduino:mbed_rp2040:pico \""+ProjectPath+"/"+ProjectName+"_arduino\" --build-path \""+ProjectPath+"/plc_binary\" \n");
	fprintf (BatFile, "echo End of compilation. Press a key to close this window.\n");
	fprintf (BatFile, "pause\n");

	fclose (BatFile);

	// wxExecute can not be launched directly by a call to TP_StartCompilation as it requires to be launched from the DLL thread, not the GUI one
	// So we send a command to DLL main thread
    wxThreadEvent *event = new wxThreadEvent(wxEVT_THREAD, CMD_START_COMPILATION);
	event->SetInt(0);
    wxQueueEvent(wxApp::GetInstance(), event);

	return 0;
}  // TP_StartCompilation
// -----------------------------------------------------

void StartCompilation (void)
{
	long m_pid;
	wxString Cmd;
	//wxArrayString output;
	//wxArrayString error;

	// To use Arduino CLI compiler, send following command to shell "arduino-cli compile -v -b arduino:mbed_rp2040:pico D:\BeremizPLC\BeremizProjectManager\TestProjects\TestIONO\TestIONO_arduino"
	//Cmd = ArduinoCLILocation + " compile -v -b arduino:mbed_rp2040:pico "+ProjectPath+"/"+ProjectName+"_arduino/";
	Cmd = "C:\\Windows\\system32\\cmd.exe /c \""+ProjectPath+"\\launch_cli.bat\"";

	m_pid = wxExecute(Cmd, wxEXEC_ASYNC | wxEXEC_SHOW_CONSOLE, 0, 0);
	if (m_pid==-1)
	{
		wxMessageBox ("An error occured while trying to start the compiler\nCan not compile application", "RPiPico.dll", wxOK+wxICON_ERROR);
	}

	// TODO : replace this will a call to a .BAT file, so shell window remains open and we can see final result
	//m_pid = wxExecute(Cmd, wxEXEC_ASYNC, 0, 0);
	//m_pid = wxExecute (Cmd, output, error, wxEXEC_ASYNC, 0);
}  // StartCompilation
// -----------------------------------------------------

int32_t EXPORT_INTERFACE TP_GetCompilerMessages (uint8_t* Msg)
{
	return 0;		// No messages retrieved from compiler window for now to be displayed in the manager
}  // TP_GetCompilerMessages
// -----------------------------------------------------

} // extern "C"
