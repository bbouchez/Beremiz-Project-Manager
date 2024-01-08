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
#include <wx/statbmp.h>
#include <wx/radiobox.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class CPixtendV2IOEditorFrame
///////////////////////////////////////////////////////////////////////////////
class CPixtendV2IOEditorFrame : public wxFrame
{
	private:

	protected:
		wxMenuBar* m_menubar1;
		wxMenu* MenuRemoteTarget;
		wxMenu* PLCControlMenu;
		wxMenu* MenuOptions;
		wxStaticBitmap* PixtendBitmap;
		wxRadioBox* PixtendTypeSelector;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnTargetParametersMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPLCStartMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPLCStopMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEnableAutoStartMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDisableAutoStartMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileTransferOption( wxCommandEvent& event ) { event.Skip(); }


	public:

		CPixtendV2IOEditorFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("PiXtend V2-L / PiXtend V2-S I/O Configurator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1045,731 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_TOOL_WINDOW|wxTAB_TRAVERSAL );

		~CPixtendV2IOEditorFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class CTargetConfigDialog
///////////////////////////////////////////////////////////////////////////////
class CTargetConfigDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* EditIPAddress;
		wxStaticText* m_staticText2;
		wxTextCtrl* EditLogin;
		wxStaticText* m_staticText3;
		wxTextCtrl* EditPassword;
		wxStaticText* m_staticText4;
		wxTextCtrl* EditBeremizPLCDirectory;
		wxButton* OKBtn;
		wxButton* TestConnectionBtn;
		wxButton* CancelBtn;

		// Virtual event handlers, override them in your derived class
		virtual void OnOKButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTestConnectionBtn( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelButton( wxCommandEvent& event ) { event.Skip(); }


	public:

		CTargetConfigDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Target connection parameters"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 579,289 ), long style = wxCAPTION );

		~CTargetConfigDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class CPixtendOptionsDialog
///////////////////////////////////////////////////////////////////////////////
class CPixtendOptionsDialog : public wxDialog
{
	private:

	protected:
		wxButton* WinSCPBrowseBtn;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnBrowseButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelBtn( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKBtn( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxTextCtrl* EditWinSCPLocation;
		wxCheckBox* ChkHoldWinSCPTransfer;

		CPixtendOptionsDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("PiXtend V2 Options"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 427,239 ), long style = wxDEFAULT_DIALOG_STYLE );

		~CPixtendOptionsDialog();

};

