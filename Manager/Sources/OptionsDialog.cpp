/////////////////////////////////////////////////////////////////////////////
// Name:        OptionsDialog.h
// Purpose:     Beremiz Project Manager options dialog
// Author:      Benoit BOUCHEZ
// Modified by:
// Created:     28/06/2022
// Copyright:   (c) Benoit BOUCHEZ
/////////////////////////////////////////////////////////////////////////////

#include "OptionsDialog.h"

OptionsDialog::OptionsDialog (wxFrame* ParentFrame) : CProjectManagerOptionsDialog (ParentFrame)
{
}  // OptionsDialog::OptionsDialog
// -----------------------------------------------------

OptionsDialog::~OptionsDialog ()
{
}  // OptionsDialog::~OptionsDialog
// -----------------------------------------------------

void OptionsDialog::FillFields (wxString BaseFilesDirectory)
{
	EditBaseFilesLocation->SetValue (BaseFilesDirectory);
}  // OptionsDialog::FillFields
// -----------------------------------------------------
	
void OptionsDialog::OnBrowseButton (wxCommandEvent& WXUNUSED(event))
{
	wxDirDialog dlg(NULL, "Select PLC base files directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)	return;

	EditBaseFilesLocation->SetValue (dlg.GetPath()+"\\");
}  // OptionsDialog::OnBrowseButton
// -----------------------------------------------------
