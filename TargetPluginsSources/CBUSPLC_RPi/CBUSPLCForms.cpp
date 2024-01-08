///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "CBUSPLCForms.h"

///////////////////////////////////////////////////////////////////////////

CCBUSIOEditFrame::CCBUSIOEditFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_menubar1 = new wxMenuBar( 0 );
	MenuRemoteTarget = new wxMenu();
	wxMenuItem* MenuRPiLogin;
	MenuRPiLogin = new wxMenuItem( MenuRemoteTarget, wxID_ANY, wxString( wxT("Connection properties") ) , wxEmptyString, wxITEM_NORMAL );
	MenuRemoteTarget->Append( MenuRPiLogin );

	m_menubar1->Append( MenuRemoteTarget, wxT("Target") );

	PLCControlMenu = new wxMenu();
	wxMenuItem* PLCStartMenu;
	PLCStartMenu = new wxMenuItem( PLCControlMenu, wxID_ANY, wxString( wxT("Start PLC") ) , wxEmptyString, wxITEM_NORMAL );
	PLCControlMenu->Append( PLCStartMenu );

	wxMenuItem* PLCStopMenu;
	PLCStopMenu = new wxMenuItem( PLCControlMenu, wxID_ANY, wxString( wxT("Stop PLC") ) , wxEmptyString, wxITEM_NORMAL );
	PLCControlMenu->Append( PLCStopMenu );

	wxMenuItem* EnableAutoStartPLCMenu;
	EnableAutoStartPLCMenu = new wxMenuItem( PLCControlMenu, wxID_ANY, wxString( wxT("Enable PLC automatic start") ) , wxEmptyString, wxITEM_NORMAL );
	PLCControlMenu->Append( EnableAutoStartPLCMenu );

	wxMenuItem* DisablePLCAutoStartMenu;
	DisablePLCAutoStartMenu = new wxMenuItem( PLCControlMenu, wxID_ANY, wxString( wxT("Disable PLC automatic start") ) , wxEmptyString, wxITEM_NORMAL );
	PLCControlMenu->Append( DisablePLCAutoStartMenu );

	m_menubar1->Append( PLCControlMenu, wxT("PLC Control") );

	MenuOptions = new wxMenu();
	wxMenuItem* FileTransferOptionMenu;
	FileTransferOptionMenu = new wxMenuItem( MenuOptions, wxID_ANY, wxString( wxT("File transfer") ) , wxEmptyString, wxITEM_NORMAL );
	MenuOptions->Append( FileTransferOptionMenu );

	m_menubar1->Append( MenuOptions, wxT("Options") );

	this->SetMenuBar( m_menubar1 );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("System inputs") ), wxVERTICAL );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 2, 4, 0, 0 );

	m_staticText2 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("%IX0.0 : CANPiCAP S1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer2->Add( m_staticText2, 0, wxALL, 5 );

	m_staticText3 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("%IX0.1 : CAN Socket Ready"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gSizer2->Add( m_staticText3, 0, wxALL, 5 );

	m_staticText4 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("%IX0.2 : CBUS Available"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer2->Add( m_staticText4, 0, wxALL, 5 );

	m_staticText5 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("%IX0.3 : DCC Track powered"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	gSizer2->Add( m_staticText5, 0, wxALL, 5 );

	m_staticText6 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("%IX0.4 : Emergency stop state"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	gSizer2->Add( m_staticText6, 0, wxALL, 5 );


	sbSizer1->Add( gSizer2, 1, wxEXPAND, 5 );


	bSizer16->Add( sbSizer1, 1, wxEXPAND|wxRIGHT|wxLEFT, 5 );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("System outputs") ), wxVERTICAL );

	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 2, 4, 0, 0 );

	m_staticText7 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("%QX0.0 : Yellow LED"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	gSizer3->Add( m_staticText7, 0, wxALL, 5 );

	m_staticText8 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("%QX0.1 : Green LED"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	gSizer3->Add( m_staticText8, 0, wxALL, 5 );

	m_staticText9 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("%QX0.2 : Red LED"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	gSizer3->Add( m_staticText9, 0, wxALL, 5 );

	m_staticText10 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("%QX0.3 : Track power control"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	gSizer3->Add( m_staticText10, 0, wxALL, 5 );

	m_staticText11 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("%QX0.4 : Emergency stop"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	gSizer3->Add( m_staticText11, 0, wxALL, 5 );


	sbSizer2->Add( gSizer3, 1, wxEXPAND, 5 );


	bSizer16->Add( sbSizer2, 1, wxEXPAND|wxRIGHT|wxLEFT, 5 );

	IOGrid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	IOGrid->CreateGrid( 128, 8 );
	IOGrid->EnableEditing( true );
	IOGrid->EnableGridLines( true );
	IOGrid->EnableDragGridSize( false );
	IOGrid->SetMargins( 0, 0 );

	// Columns
	IOGrid->EnableDragColMove( false );
	IOGrid->EnableDragColSize( false );
	IOGrid->SetColLabelValue( 0, wxT("PLC Input") );
	IOGrid->SetColLabelValue( 1, wxT("Device #") );
	IOGrid->SetColLabelValue( 2, wxT("Event #") );
	IOGrid->SetColLabelValue( 3, wxT("Comment") );
	IOGrid->SetColLabelValue( 4, wxT("PLC Output") );
	IOGrid->SetColLabelValue( 5, wxT("Device #") );
	IOGrid->SetColLabelValue( 6, wxT("Event #") );
	IOGrid->SetColLabelValue( 7, wxT("Comment") );
	IOGrid->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	IOGrid->EnableDragRowSize( false );
	IOGrid->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	IOGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer16->Add( IOGrid, 1, wxEXPAND|wxALL, 5 );


	this->SetSizer( bSizer16 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CCBUSIOEditFrame::OnClose ) );
	MenuRemoteTarget->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CCBUSIOEditFrame::OnTargetParametersMenu ), this, MenuRPiLogin->GetId());
	PLCControlMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CCBUSIOEditFrame::OnPLCStartMenu ), this, PLCStartMenu->GetId());
	PLCControlMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CCBUSIOEditFrame::OnPLCStopMenu ), this, PLCStopMenu->GetId());
	PLCControlMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CCBUSIOEditFrame::OnEnableAutoStartMenu ), this, EnableAutoStartPLCMenu->GetId());
	PLCControlMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CCBUSIOEditFrame::OnDisableAutoStartMenu ), this, DisablePLCAutoStartMenu->GetId());
	MenuOptions->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CCBUSIOEditFrame::OnFileTransferOption ), this, FileTransferOptionMenu->GetId());
	IOGrid->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( CCBUSIOEditFrame::OnCellDataChange ), NULL, this );
}

CCBUSIOEditFrame::~CCBUSIOEditFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CCBUSIOEditFrame::OnClose ) );
	IOGrid->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( CCBUSIOEditFrame::OnCellDataChange ), NULL, this );

}

CTargetConfigDialog::CTargetConfigDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );

	sbSizer10->SetMinSize( wxSize( -1,200 ) );
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 4, 2, 0, 0 );

	m_staticText1 = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("IP address"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	gSizer1->Add( m_staticText1, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );

	EditIPAddress = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !EditIPAddress->HasFlag( wxTE_MULTILINE ) )
	{
	EditIPAddress->SetMaxLength( 16 );
	}
	#else
	EditIPAddress->SetMaxLength( 16 );
	#endif
	gSizer1->Add( EditIPAddress, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText2 = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Login"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer1->Add( m_staticText2, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );

	EditLogin = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( EditLogin, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText3 = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Password"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gSizer1->Add( m_staticText3, 0, wxALIGN_RIGHT|wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );

	EditPassword = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	gSizer1->Add( EditPassword, 0, wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText4 = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Beremiz PLC directory"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer1->Add( m_staticText4, 0, wxALIGN_RIGHT|wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );

	EditBeremizPLCDirectory = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	EditBeremizPLCDirectory->SetMinSize( wxSize( 250,-1 ) );

	gSizer1->Add( EditBeremizPLCDirectory, 0, wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );


	sbSizer10->Add( gSizer1, 1, wxEXPAND, 5 );


	bSizer12->Add( sbSizer10, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );

	OKBtn = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( OKBtn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );

	TestConnectionBtn = new wxButton( this, wxID_ANY, wxT("Test supervisor connection"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( TestConnectionBtn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );

	CancelBtn = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( CancelBtn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer12->Add( bSizer13, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer12 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	OKBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CTargetConfigDialog::OnOKButton ), NULL, this );
	TestConnectionBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CTargetConfigDialog::OnTestConnectionBtn ), NULL, this );
	CancelBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CTargetConfigDialog::OnCancelButton ), NULL, this );
}

CTargetConfigDialog::~CTargetConfigDialog()
{
	// Disconnect Events
	OKBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CTargetConfigDialog::OnOKButton ), NULL, this );
	TestConnectionBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CTargetConfigDialog::OnTestConnectionBtn ), NULL, this );
	CancelBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CTargetConfigDialog::OnCancelButton ), NULL, this );

}

CCBUSPLCOptionsDialog::CCBUSPLCOptionsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Winscp.com location") ), wxVERTICAL );

	EditWinSCPLocation = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( EditWinSCPLocation, 0, wxALL|wxEXPAND, 5 );

	WinSCPBrowseBtn = new wxButton( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( WinSCPBrowseBtn, 0, wxALL, 5 );


	bSizer14->Add( sbSizer5, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Debug / Trace") ), wxVERTICAL );

	ChkHoldWinSCPTransfer = new wxCheckBox( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Hold WinSCP file transfer before closing connection"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer6->Add( ChkHoldWinSCPTransfer, 0, wxALL, 5 );


	bSizer14->Add( sbSizer6, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();

	bSizer14->Add( m_sdbSizer1, 1, wxEXPAND|wxRIGHT, 5 );


	this->SetSizer( bSizer14 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	WinSCPBrowseBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CCBUSPLCOptionsDialog::OnBrowseButton ), NULL, this );
	m_sdbSizer1Cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CCBUSPLCOptionsDialog::OnCancelBtn ), NULL, this );
	m_sdbSizer1OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CCBUSPLCOptionsDialog::OnOKBtn ), NULL, this );
}

CCBUSPLCOptionsDialog::~CCBUSPLCOptionsDialog()
{
	// Disconnect Events
	WinSCPBrowseBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CCBUSPLCOptionsDialog::OnBrowseButton ), NULL, this );
	m_sdbSizer1Cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CCBUSPLCOptionsDialog::OnCancelBtn ), NULL, this );
	m_sdbSizer1OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CCBUSPLCOptionsDialog::OnOKBtn ), NULL, this );

}
