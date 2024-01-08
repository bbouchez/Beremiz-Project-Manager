///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "RPiPicoForms.h"

///////////////////////////////////////////////////////////////////////////

CPicoIOEditorFrame::CPicoIOEditorFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	PicoBitmap = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	PicoBitmap->SetMinSize( wxSize( 512,512 ) );
	PicoBitmap->SetMaxSize( wxSize( 512,512 ) );

	bSizer1->Add( PicoBitmap, 0, wxALL, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	IOGrid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	IOGrid->CreateGrid( 30, 3 );
	IOGrid->EnableEditing( true );
	IOGrid->EnableGridLines( true );
	IOGrid->EnableDragGridSize( false );
	IOGrid->SetMargins( 0, 0 );

	// Columns
	IOGrid->EnableDragColMove( false );
	IOGrid->EnableDragColSize( true );
	IOGrid->SetColLabelValue( 0, wxT("Pin") );
	IOGrid->SetColLabelValue( 1, wxT("Function") );
	IOGrid->SetColLabelValue( 2, wxT("PLC Name") );
	IOGrid->SetColLabelValue( 3, wxEmptyString );
	IOGrid->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	IOGrid->EnableDragRowSize( false );
	IOGrid->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	IOGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	IOGrid->SetMinSize( wxSize( -1,300 ) );

	bSizer2->Add( IOGrid, 1, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND, 5 );

	wxString CompilerChoiceBoxChoices[] = { wxT("Arduino"), wxT("Pico SDK") };
	int CompilerChoiceBoxNChoices = sizeof( CompilerChoiceBoxChoices ) / sizeof( wxString );
	CompilerChoiceBox = new wxRadioBox( this, wxID_ANY, wxT("Compiler"), wxDefaultPosition, wxDefaultSize, CompilerChoiceBoxNChoices, CompilerChoiceBoxChoices, 2, wxRA_SPECIFY_COLS );
	CompilerChoiceBox->SetSelection( 1 );
	CompilerChoiceBox->Enable( false );

	bSizer2->Add( CompilerChoiceBox, 0, wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Arduino CLI location") ), wxVERTICAL );

	EditArduinoCLILocation = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	sbSizer1->Add( EditArduinoCLILocation, 0, wxALL|wxEXPAND, 5 );

	BrowseCLILocationBtn = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer1->Add( BrowseCLILocationBtn, 0, wxALL, 5 );


	bSizer2->Add( sbSizer1, 1, wxEXPAND|wxRIGHT, 5 );


	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CPicoIOEditorFrame::OnClose ) );
	IOGrid->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( CPicoIOEditorFrame::OnGridChange ), NULL, this );
	IOGrid->Connect( wxEVT_GRID_SELECT_CELL, wxGridEventHandler( CPicoIOEditorFrame::OnGridSelected ), NULL, this );
	CompilerChoiceBox->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( CPicoIOEditorFrame::OnCompilerSelect ), NULL, this );
	EditArduinoCLILocation->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( CPicoIOEditorFrame::OnArduinoCLIEnter ), NULL, this );
	BrowseCLILocationBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPicoIOEditorFrame::OnBrowseCLI ), NULL, this );
}

CPicoIOEditorFrame::~CPicoIOEditorFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CPicoIOEditorFrame::OnClose ) );
	IOGrid->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( CPicoIOEditorFrame::OnGridChange ), NULL, this );
	IOGrid->Disconnect( wxEVT_GRID_SELECT_CELL, wxGridEventHandler( CPicoIOEditorFrame::OnGridSelected ), NULL, this );
	CompilerChoiceBox->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( CPicoIOEditorFrame::OnCompilerSelect ), NULL, this );
	EditArduinoCLILocation->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( CPicoIOEditorFrame::OnArduinoCLIEnter ), NULL, this );
	BrowseCLILocationBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPicoIOEditorFrame::OnBrowseCLI ), NULL, this );

}
