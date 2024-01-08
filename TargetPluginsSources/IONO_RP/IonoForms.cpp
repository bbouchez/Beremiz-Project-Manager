///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "IonoForms.h"

///////////////////////////////////////////////////////////////////////////

CIonoIOEditorFrame::CIonoIOEditorFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	IonoBitmap = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	IonoBitmap->SetMinSize( wxSize( 512,512 ) );
	IonoBitmap->SetMaxSize( wxSize( 512,512 ) );

	bSizer1->Add( IonoBitmap, 0, wxALL, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	IOGrid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	IOGrid->CreateGrid( 12, 3 );
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

	bSizer2->Add( IOGrid, 1, wxTOP|wxBOTTOM|wxRIGHT, 5 );

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

	m_button1 = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer1->Add( m_button1, 0, wxALL, 5 );


	bSizer2->Add( sbSizer1, 1, wxEXPAND|wxRIGHT, 5 );


	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CIonoIOEditorFrame::OnClose ) );
	IOGrid->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( CIonoIOEditorFrame::OnGridChange ), NULL, this );
	IOGrid->Connect( wxEVT_GRID_SELECT_CELL, wxGridEventHandler( CIonoIOEditorFrame::OnGridSelected ), NULL, this );
	CompilerChoiceBox->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( CIonoIOEditorFrame::OnCompilerSelect ), NULL, this );
	EditArduinoCLILocation->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( CIonoIOEditorFrame::OnArduinoCLIEnter ), NULL, this );
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CIonoIOEditorFrame::OnBrowseCLI ), NULL, this );
}

CIonoIOEditorFrame::~CIonoIOEditorFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CIonoIOEditorFrame::OnClose ) );
	IOGrid->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( CIonoIOEditorFrame::OnGridChange ), NULL, this );
	IOGrid->Disconnect( wxEVT_GRID_SELECT_CELL, wxGridEventHandler( CIonoIOEditorFrame::OnGridSelected ), NULL, this );
	CompilerChoiceBox->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( CIonoIOEditorFrame::OnCompilerSelect ), NULL, this );
	EditArduinoCLILocation->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( CIonoIOEditorFrame::OnArduinoCLIEnter ), NULL, this );
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CIonoIOEditorFrame::OnBrowseCLI ), NULL, this );

}
