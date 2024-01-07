///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/splitter.h>
#include <wx/checkbox.h>
#include <wx/timer.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/choice.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class CBaseFrame
///////////////////////////////////////////////////////////////////////////////
class CBaseFrame : public wxFrame
{
	private:

	protected:
		wxMenuBar* MainMenuBar;
		wxMenu* ProjectMenu;
		wxMenu* EditMenu;
		wxMenu* IEC61131Menu;
		wxMenu* BuildMenu;
		wxMenu* OptionsMenu;
		wxMenu* HelpMenu;
		wxSplitterWindow* MainVerticalSplitter;
		wxPanel* TreePanel;
		wxTreeCtrl* ProjectTree;
		wxPanel* RightMainPanel;
		wxSplitterWindow* MainHorizontalSplitter;
		wxPanel* TopRightPanel;
		wxPanel* BottomRightPanel;
		wxTextCtrl* LogTextCtrl;
		wxCheckBox* ChkClearBeforeBuild;
		wxTimer MainTimer;
		wxToolBar* MainToolbar;
		wxToolBarToolBase* ToolNew;
		wxToolBarToolBase* ToolOpen;
		wxToolBarToolBase* ToolSave;
		wxToolBarToolBase* ToolCut;
		wxToolBarToolBase* ToolCopy;
		wxToolBarToolBase* ToolPaste;
		wxToolBarToolBase* ToolClean;
		wxToolBarToolBase* ToolBuild;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnProjectNewMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProjectOpenMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProjectSaveMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProjectCloseMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProjectExitMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuEditCut( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuEditCopy( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditMenuPaste( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuEditDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditMenuRename( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGenerateFrameworkMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOpenBeremizEditor( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBuildCleanupMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBuildMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOptionsGeneralMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowPluginVersionMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOptionsCloseEditors( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHelpAboutMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTreeDoubleClick( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnTreeSelChanged( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnMainTimer( wxTimerEvent& event ) { event.Skip(); }
		virtual void OnMenuEditPaste( wxCommandEvent& event ) { event.Skip(); }


	public:

		CBaseFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Beremiz Project Manager"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 991,537 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~CBaseFrame();

		void MainVerticalSplitterOnIdle( wxIdleEvent& )
		{
			MainVerticalSplitter->SetSashPosition( 250 );
			MainVerticalSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( CBaseFrame::MainVerticalSplitterOnIdle ), NULL, this );
		}

		void MainHorizontalSplitterOnIdle( wxIdleEvent& )
		{
			MainHorizontalSplitter->SetSashPosition( -150 );
			MainHorizontalSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( CBaseFrame::MainHorizontalSplitterOnIdle ), NULL, this );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class CSelectionCPUDialog
///////////////////////////////////////////////////////////////////////////////
class CSelectionCPUDialog : public wxDialog
{
	private:

	protected:
		wxChoice* CPUModelChoice;
		wxTextCtrl* CPUInformation;
		wxButton* OKBtn;
		wxButton* CancelBtn;

		// Virtual event handlers, override them in your derived class
		virtual void OnCPUModelChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelButton( wxCommandEvent& event ) { event.Skip(); }


	public:

		CSelectionCPUDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Select CPU model"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 315,223 ), long style = wxCAPTION );

		~CSelectionCPUDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class CPluginInfoDialog
///////////////////////////////////////////////////////////////////////////////
class CPluginInfoDialog : public wxFrame
{
	private:

	protected:
		wxStaticText* m_staticText9;
		wxStaticText* LblPluginName;
		wxStaticText* m_staticText11;
		wxStaticText* LBLCPUName;
		wxStaticText* m_staticText13;
		wxStaticText* LblVersion;
		wxButton* m_button5;

	public:

		CPluginInfoDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Plugin information"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 370,167 ), long style = wxCAPTION|wxCLOSE_BOX|wxTAB_TRAVERSAL );

		~CPluginInfoDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class AboutDialog
///////////////////////////////////////////////////////////////////////////////
class AboutDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText11;
		wxStaticBitmap* ImageLogo;
		wxStaticText* m_staticText12;
		wxStaticText* name;
		wxStaticText* description;
		wxStaticText* wxcredit;
		wxStaticText* copyright;
		wxButton* BtnClose;

	public:
		wxStaticText* VersionStr;

		AboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("About Beremiz Project Manager"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 363,368 ), long style = wxDEFAULT_DIALOG_STYLE );

		~AboutDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class CProjectManagerOptionsDialog
///////////////////////////////////////////////////////////////////////////////
class CProjectManagerOptionsDialog : public wxDialog
{
	private:

	protected:
		wxButton* PLCBaseFilesBrowseBtn;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnBrowseButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelBtn( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKBtn( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxTextCtrl* EditBaseFilesLocation;

		CProjectManagerOptionsDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Beremiz Project Manager options"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 427,174 ), long style = wxDEFAULT_DIALOG_STYLE );

		~CProjectManagerOptionsDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class NoParamPanel
///////////////////////////////////////////////////////////////////////////////
class NoParamPanel : public wxPanel
{
	private:

	protected:
		wxStaticBoxSizer* ProjectEntitySizer;

	public:
		wxStaticText* EditableLabel;

		NoParamPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~NoParamPanel();

};

