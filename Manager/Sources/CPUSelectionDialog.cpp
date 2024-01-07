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

#include "CPUSelectionDialog.h"
#include <wx/xml/xml.h>

CPUSelectionDialog::CPUSelectionDialog (wxFrame* ParentFrame) : CSelectionCPUDialog (ParentFrame)
{
	wxXmlDocument doc;
	wxXmlNode* RootNode;
	wxXmlNode* TopNode;
	wxString TargetName;
	wxString PluginName;
	wxString InfoString;
	wxString CPUType;
	TARGET_DATA* NewTargetData;
	TARGET_DATA* LastTargetData=0;

	OKClicked = false;
	FirstTargetData = 0;
	TargetPluginName = wxEmptyString;

	// Load targets.xml file and generate target structure chain
	if (!doc.Load("targets.xml"))
	{
		wxMessageBox ("Error : can not read list of targets from targets.xml", "CPU Selection dialog", wxOK+wxICON_ERROR);
		return;
	}

	RootNode=doc.GetRoot();
	if (RootNode->GetName() != "beremiz_project_manager_targets")
	{
		wxMessageBox ("Error : corrupted targets.xml file", "CPU Selection dialog", wxOK+wxICON_ERROR);
		return;
	}

	TopNode=RootNode->GetChildren();
	while (TopNode!=0)
	{
		if (TopNode->GetName()=="target")
		{
			TopNode->GetAttribute ("name", &TargetName);
			TopNode->GetAttribute ("plugin", &PluginName);
			TopNode->GetAttribute ("cputype", &CPUType);
			TopNode->GetAttribute ("info", &InfoString);

			// Create first node in the chain
			if (FirstTargetData == 0)
			{
				FirstTargetData = new TARGET_DATA;
				FirstTargetData->TargetName = TargetName;
				FirstTargetData->LibraryName = PluginName;
				FirstTargetData->CPUType = CPUType;
				FirstTargetData->Information = InfoString;
				FirstTargetData->NextTargetData = 0;
				LastTargetData = FirstTargetData;
			}
			else
			{  // Create next node in the chain
				NewTargetData = new TARGET_DATA;
				NewTargetData->TargetName = TargetName;
				NewTargetData->LibraryName = PluginName;
				NewTargetData->CPUType = CPUType;
				NewTargetData->Information = InfoString;
				NewTargetData->NextTargetData = 0;
				LastTargetData->NextTargetData = NewTargetData;
				LastTargetData = NewTargetData;
			}
		}

		// Fill CPU list with target name
		CPUModelChoice->Append (TargetName);
			
		TopNode=TopNode->GetNext();
	}
}  // CPUSelectionDialog::CPUSelectionDialog
// -----------------------------------------------------

CPUSelectionDialog::~CPUSelectionDialog ()
{
	TARGET_DATA* NextTarget;
	TARGET_DATA* CurrentTarget;

	// Delete the target data chain if it has been created
	if (FirstTargetData != 0)
	{
		CurrentTarget = FirstTargetData;
		do
		{
			NextTarget = (TARGET_DATA*)CurrentTarget->NextTargetData;
			delete CurrentTarget;
			CurrentTarget = NextTarget;
		} while (NextTarget!=0);
	}
}  // CPUSelectionDialog::~CPUSelectionDialog
// -----------------------------------------------------

void CPUSelectionDialog::OnCPUModelChoice (wxCommandEvent& WXUNUSED(event))
{
	int SelectionIndex;
	TARGET_DATA* Target;
	int TargetCounter;

	// Get selection index and parse the chain until we reach the same count to locate entry in the chain
	SelectionIndex = CPUModelChoice->GetSelection();
	if (SelectionIndex==-1) return;		// Nothing selected

	if (SelectionIndex == 0)
		Target = FirstTargetData;
	else
	{
		// Parse the chain
		Target = (TARGET_DATA*)FirstTargetData->NextTargetData;
		TargetCounter = 1;
		while (TargetCounter!=SelectionIndex)
		{
			Target = (TARGET_DATA*)Target->NextTargetData;
			TargetCounter++;
		}
	}

	CPUInformation->SetLabel (Target->Information);
	TargetPluginName = Target->LibraryName;
}  // CPUSelectionDialog::OnCPUModelChoice
// -----------------------------------------------------

void CPUSelectionDialog::OnOKButton (wxCommandEvent& WXUNUSED(event))
{
	if (CPUModelChoice->GetCurrentSelection()==-1)
	{
		wxMessageBox ("Please select a CPU type for the project", "CPU Type not selected", wxOK+wxICON_WARNING);
		return;
	}

	OKClicked = true;
	this->Close();
}  // CPUSelectionDialog::OnOKButton
// -----------------------------------------------------

void CPUSelectionDialog::OnCancelButton (wxCommandEvent& WXUNUSED(event))
{
	OKClicked = false;
	this->Close();
}  // CPUSelectionDialog::OnCancelButton
// -----------------------------------------------------
