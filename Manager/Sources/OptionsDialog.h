/////////////////////////////////////////////////////////////////////////////
// Name:        OptionsDialog.h
// Purpose:     Beremiz Project Manager options dialog
// Author:      Benoit BOUCHEZ
// Modified by:
// Created:     28/06/2022
// Copyright:   (c) Benoit BOUCHEZ
/////////////////////////////////////////////////////////////////////////////

#ifndef __OPTIONSDIALOG_H__
#define __OPTIONSDIALOG_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "BPMForms.h"

class OptionsDialog : public CProjectManagerOptionsDialog
{
public:
	OptionsDialog (wxFrame* ParentFrame);
	~OptionsDialog ();

	void FillFields (wxString BaseFilesDirectory);
	void OnBrowseButton (wxCommandEvent& event);
private:
};

#endif