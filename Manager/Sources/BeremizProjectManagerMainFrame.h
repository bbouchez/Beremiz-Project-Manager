/////////////////////////////////////////////////////////////////////////////
// Name:        BeremizProjectManagerMainFrame.h
// Purpose:     Beremiz Project Manager main frame
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

#ifndef __BEREMIZPROJECTMANAGERMAINFRAME_H__
#define __BEREMIZPROJECTMANAGERMAINFRAME_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/process.h>
#include <wx/dirdlg.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/file.h>
#include <wx/grid.h>
#include <wx/filefn.h>
#ifdef __TARGET_WIN__
#include <wx/msw/registry.h>
#endif
#include <wx/treectrl.h>
#include <wx/splitter.h>
#include <wx/richtext/richtextctrl.h>

#include "BPMForms.h"
#include "ProjectControl.h"

class CBeremizProjectManagerMainFrame : public CBaseFrame
{
public:
    CBeremizProjectManagerMainFrame(wxFrame* ParentFrame);
	~CBeremizProjectManagerMainFrame();

    // Event handlers
    void OnClose(wxCloseEvent& event);
	//void OnFrameResize (wxSizeEvent& event);			// DO NOT USE THIS METHOD : it avoid the splitter to work properly
	void UpdateEditorSize (void);

	// Project menu
	void OnProjectNewMenu (wxCommandEvent& event);
	void OnProjectOpenMenu (wxCommandEvent& event);
	void OnProjectSaveMenu (wxCommandEvent& event);
	void OnProjectCloseMenu (wxCommandEvent& event);
    void OnProjectExitMenu(wxCommandEvent& event);

	void OnConnectionReportMenu (wxCommandEvent& event);

	void OnGenerateFrameworkMenu (wxCommandEvent& event);

	void OnOpenBeremizEditor (wxCommandEvent& event);

	void OnBuildCleanupMenu (wxCommandEvent& event);
	void OnBuildMenu (wxCommandEvent& event);
	void OnRebuildMenu (wxCommandEvent& event);
	void OnBuildStopMenu (wxCommandEvent& event);

	void OnMainTimer (wxTimerEvent& event);

	void OnTreeDoubleClick (wxTreeEvent& event);
	void OnTreeSelChanged (wxTreeEvent& event);

	void OnHelpAboutMenu (wxCommandEvent& event);

	void OnOptionsGeneralMenu (wxCommandEvent& event);
	void OnShowPluginVersionMenu (wxCommandEvent& event);
	void OnOptionsCloseEditors (wxCommandEvent& event);

private:
	bool CompilationInProgress;
	wxString TargetsDirectory;		// Path to directory containing targets definition
	bool CleanWithFramework;		// Clean command will also delete framework files (so GenerateFramework() call is needed before build)

	wxSize LastFrameSize, CurrentFrameSize;		// Detect when frame has changed to update editor size automatically

	wxTreeItemId rootItemId;        // First item in the tree (Project name)
	wxTreeItemId CPUItemId;

	CBeremizProject* Project;

	//! Refresh tree structure from project data
	void BuildTreeFromProject (void);

	//! Save PLC project
	void SaveProject ();

	//! Load Beremiz Project Manager options (like location of source files)
	void LoadManagerConfiguration (void);
	//! Save Beremiz Project Manager options
	void SaveManagerConfiguration (void);

	// *** Edition panels displayed on top right main frame
	NoParamPanel* EmptyPanel;				// Panel used by all targets when no parameter can be edited in the current tree selection
};

#endif
