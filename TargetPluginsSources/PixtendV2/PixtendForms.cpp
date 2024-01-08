///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "PixtendForms.h"

///////////////////////////////////////////////////////////////////////////

CPixtendV2IOEditorFrame::CPixtendV2IOEditorFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
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

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	PixtendBitmap = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	PixtendBitmap->SetMinSize( wxSize( 1024,600 ) );

	bSizer1->Add( PixtendBitmap, 0, wxALL, 5 );

	wxString PixtendTypeSelectorChoices[] = { wxT("PiXtend V2-L"), wxT("PiXtend V2-S") };
	int PixtendTypeSelectorNChoices = sizeof( PixtendTypeSelectorChoices ) / sizeof( wxString );
	PixtendTypeSelector = new wxRadioBox( this, wxID_ANY, wxT("PiXtend model"), wxDefaultPosition, wxDefaultSize, PixtendTypeSelectorNChoices, PixtendTypeSelectorChoices, 2, wxRA_SPECIFY_COLS );
	PixtendTypeSelector->SetSelection( 0 );
	PixtendTypeSelector->Enable( false );

	bSizer1->Add( PixtendTypeSelector, 0, wxALL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CPixtendV2IOEditorFrame::OnClose ) );
	MenuRemoteTarget->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CPixtendV2IOEditorFrame::OnTargetParametersMenu ), this, MenuRPiLogin->GetId());
	PLCControlMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CPixtendV2IOEditorFrame::OnPLCStartMenu ), this, PLCStartMenu->GetId());
	PLCControlMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CPixtendV2IOEditorFrame::OnPLCStopMenu ), this, PLCStopMenu->GetId());
	PLCControlMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CPixtendV2IOEditorFrame::OnEnableAutoStartMenu ), this, EnableAutoStartPLCMenu->GetId());
	PLCControlMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CPixtendV2IOEditorFrame::OnDisableAutoStartMenu ), this, DisablePLCAutoStartMenu->GetId());
	MenuOptions->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CPixtendV2IOEditorFrame::OnFileTransferOption ), this, FileTransferOptionMenu->GetId());
}

CPixtendV2IOEditorFrame::~CPixtendV2IOEditorFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CPixtendV2IOEditorFrame::OnClose ) );

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

CPixtendOptionsDialog::CPixtendOptionsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
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
	WinSCPBrowseBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPixtendOptionsDialog::OnBrowseButton ), NULL, this );
	m_sdbSizer1Cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPixtendOptionsDialog::OnCancelBtn ), NULL, this );
	m_sdbSizer1OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPixtendOptionsDialog::OnOKBtn ), NULL, this );
}

CPixtendOptionsDialog::~CPixtendOptionsDialog()
{
	// Disconnect Events
	WinSCPBrowseBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPixtendOptionsDialog::OnBrowseButton ), NULL, this );
	m_sdbSizer1Cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPixtendOptionsDialog::OnCancelBtn ), NULL, this );
	m_sdbSizer1OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPixtendOptionsDialog::OnOKBtn ), NULL, this );

}
