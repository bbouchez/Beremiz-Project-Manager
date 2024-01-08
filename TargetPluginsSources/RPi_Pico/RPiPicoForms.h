///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/grid.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class CPicoIOEditorFrame
///////////////////////////////////////////////////////////////////////////////
class CPicoIOEditorFrame : public wxFrame
{
	private:

	protected:
		wxStaticBitmap* PicoBitmap;
		wxGrid* IOGrid;
		wxRadioBox* CompilerChoiceBox;
		wxTextCtrl* EditArduinoCLILocation;
		wxButton* BrowseCLILocationBtn;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnGridChange( wxGridEvent& event ) { event.Skip(); }
		virtual void OnGridSelected( wxGridEvent& event ) { event.Skip(); }
		virtual void OnCompilerSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnArduinoCLIEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBrowseCLI( wxCommandEvent& event ) { event.Skip(); }


	public:

		CPicoIOEditorFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Raspberry Pi Pico I/O Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 865,549 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_TOOL_WINDOW|wxTAB_TRAVERSAL );

		~CPicoIOEditorFrame();

};

