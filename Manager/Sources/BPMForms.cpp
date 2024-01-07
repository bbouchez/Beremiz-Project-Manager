///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "BPMForms.h"

///////////////////////////////////////////////////////////////////////////

CBaseFrame::CBaseFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	MainMenuBar = new wxMenuBar( 0 );
	ProjectMenu = new wxMenu();
	wxMenuItem* ProjectNewMenu;
	ProjectNewMenu = new wxMenuItem( ProjectMenu, wxID_ANY, wxString( wxT("New") ) + wxT('\t') + wxT("Ctrl+N"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	ProjectNewMenu->SetBitmaps( wxBitmap( wxT("images/new.png"), wxBITMAP_TYPE_ANY ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	ProjectNewMenu->SetBitmap( wxBitmap( wxT("images/new.png"), wxBITMAP_TYPE_ANY ) );
	#endif
	ProjectMenu->Append( ProjectNewMenu );

	wxMenuItem* ProjectOpenMenu;
	ProjectOpenMenu = new wxMenuItem( ProjectMenu, wxID_ANY, wxString( wxT("Open") ) + wxT('\t') + wxT("Ctrl+O"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	ProjectOpenMenu->SetBitmaps( wxBitmap( wxT("images/open.png"), wxBITMAP_TYPE_ANY ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	ProjectOpenMenu->SetBitmap( wxBitmap( wxT("images/open.png"), wxBITMAP_TYPE_ANY ) );
	#endif
	ProjectMenu->Append( ProjectOpenMenu );

	ProjectMenu->AppendSeparator();

	wxMenuItem* ProjectSaveMenu;
	ProjectSaveMenu = new wxMenuItem( ProjectMenu, wxID_ANY, wxString( wxT("Save") ) + wxT('\t') + wxT("Ctrl+S"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	ProjectSaveMenu->SetBitmaps( wxBitmap( wxT("images/save.png"), wxBITMAP_TYPE_ANY ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	ProjectSaveMenu->SetBitmap( wxBitmap( wxT("images/save.png"), wxBITMAP_TYPE_ANY ) );
	#endif
	ProjectMenu->Append( ProjectSaveMenu );

	wxMenuItem* ProjectCloseMenu;
	ProjectCloseMenu = new wxMenuItem( ProjectMenu, wxID_ANY, wxString( wxT("Close") ) + wxT('\t') + wxT("Ctrl+F4"), wxEmptyString, wxITEM_NORMAL );
	ProjectMenu->Append( ProjectCloseMenu );

	ProjectMenu->AppendSeparator();

	wxMenuItem* ProjectExitMenu;
	ProjectExitMenu = new wxMenuItem( ProjectMenu, wxID_ANY, wxString( wxT("Exit") ) + wxT('\t') + wxT("Alt+F4"), wxEmptyString, wxITEM_NORMAL );
	ProjectMenu->Append( ProjectExitMenu );

	MainMenuBar->Append( ProjectMenu, wxT("Project") );

	EditMenu = new wxMenu();
	wxMenuItem* EditMenuCut;
	EditMenuCut = new wxMenuItem( EditMenu, wxID_ANY, wxString( wxT("Cut") ) + wxT('\t') + wxT("Ctrl+X"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	EditMenuCut->SetBitmaps( wxBitmap( wxT("images/cut.png"), wxBITMAP_TYPE_ANY ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	EditMenuCut->SetBitmap( wxBitmap( wxT("images/cut.png"), wxBITMAP_TYPE_ANY ) );
	#endif
	EditMenu->Append( EditMenuCut );

	wxMenuItem* EditMenuCopy;
	EditMenuCopy = new wxMenuItem( EditMenu, wxID_ANY, wxString( wxT("Copy") ) + wxT('\t') + wxT("Ctrl+C"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	EditMenuCopy->SetBitmaps( wxBitmap( wxT("images/copy.png"), wxBITMAP_TYPE_ANY ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	EditMenuCopy->SetBitmap( wxBitmap( wxT("images/copy.png"), wxBITMAP_TYPE_ANY ) );
	#endif
	EditMenu->Append( EditMenuCopy );

	wxMenuItem* EditMenuPaste;
	EditMenuPaste = new wxMenuItem( EditMenu, wxID_ANY, wxString( wxT("Paste") ) + wxT('\t') + wxT("Ctrl+V"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	EditMenuPaste->SetBitmaps( wxBitmap( wxT("images/paste.png"), wxBITMAP_TYPE_ANY ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	EditMenuPaste->SetBitmap( wxBitmap( wxT("images/paste.png"), wxBITMAP_TYPE_ANY ) );
	#endif
	EditMenu->Append( EditMenuPaste );

	wxMenuItem* EditMenuDelete;
	EditMenuDelete = new wxMenuItem( EditMenu, wxID_ANY, wxString( wxT("Delete") ) + wxT('\t') + wxT("Del"), wxEmptyString, wxITEM_NORMAL );
	EditMenu->Append( EditMenuDelete );

	EditMenu->AppendSeparator();

	wxMenuItem* EditMenuRename;
	EditMenuRename = new wxMenuItem( EditMenu, wxID_ANY, wxString( wxT("Rename") ) , wxEmptyString, wxITEM_NORMAL );
	EditMenu->Append( EditMenuRename );

	MainMenuBar->Append( EditMenu, wxT("Edit") );

	IEC61131Menu = new wxMenu();
	wxMenuItem* BuildGenerateFrameworkMenu;
	BuildGenerateFrameworkMenu = new wxMenuItem( IEC61131Menu, wxID_ANY, wxString( wxT("Generate Framework") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	BuildGenerateFrameworkMenu->SetBitmaps( wxBitmap( wxT("images/generate.png"), wxBITMAP_TYPE_ANY ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	BuildGenerateFrameworkMenu->SetBitmap( wxBitmap( wxT("images/generate.png"), wxBITMAP_TYPE_ANY ) );
	#endif
	IEC61131Menu->Append( BuildGenerateFrameworkMenu );

	wxMenuItem* OpenBeremizMenu;
	OpenBeremizMenu = new wxMenuItem( IEC61131Menu, wxID_ANY, wxString( wxT("Open Beremiz Editor") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	OpenBeremizMenu->SetBitmaps( wxBitmap( wxT("images/brz.png"), wxBITMAP_TYPE_ANY ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	OpenBeremizMenu->SetBitmap( wxBitmap( wxT("images/brz.png"), wxBITMAP_TYPE_ANY ) );
	#endif
	IEC61131Menu->Append( OpenBeremizMenu );

	MainMenuBar->Append( IEC61131Menu, wxT("IEC61131") );

	BuildMenu = new wxMenu();
	wxMenuItem* BuildCleanupMenu;
	BuildCleanupMenu = new wxMenuItem( BuildMenu, wxID_ANY, wxString( wxT("Cleanup") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	BuildCleanupMenu->SetBitmaps( wxBitmap( wxT("images/clean.png"), wxBITMAP_TYPE_ANY ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	BuildCleanupMenu->SetBitmap( wxBitmap( wxT("images/clean.png"), wxBITMAP_TYPE_ANY ) );
	#endif
	BuildMenu->Append( BuildCleanupMenu );

	wxMenuItem* BuildBuildMenu;
	BuildBuildMenu = new wxMenuItem( BuildMenu, wxID_ANY, wxString( wxT("Build") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	BuildBuildMenu->SetBitmaps( wxBitmap( wxT("images/build.png"), wxBITMAP_TYPE_ANY ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	BuildBuildMenu->SetBitmap( wxBitmap( wxT("images/build.png"), wxBITMAP_TYPE_ANY ) );
	#endif
	BuildMenu->Append( BuildBuildMenu );

	MainMenuBar->Append( BuildMenu, wxT("Build") );

	OptionsMenu = new wxMenu();
	wxMenuItem* OptionsGeneralMenu;
	OptionsGeneralMenu = new wxMenuItem( OptionsMenu, wxID_ANY, wxString( wxT("General") ) , wxEmptyString, wxITEM_NORMAL );
	OptionsMenu->Append( OptionsGeneralMenu );

	wxMenuItem* OptionsShowPluginVersionMenu;
	OptionsShowPluginVersionMenu = new wxMenuItem( OptionsMenu, wxID_ANY, wxString( wxT("Show plugin version") ) , wxEmptyString, wxITEM_NORMAL );
	OptionsMenu->Append( OptionsShowPluginVersionMenu );

	wxMenuItem* OptionsCloseEditorsMenu;
	OptionsCloseEditorsMenu = new wxMenuItem( OptionsMenu, wxID_ANY, wxString( wxT("Close all editors") ) , wxEmptyString, wxITEM_NORMAL );
	OptionsMenu->Append( OptionsCloseEditorsMenu );

	MainMenuBar->Append( OptionsMenu, wxT("Options") );

	HelpMenu = new wxMenu();
	wxMenuItem* HelpAboutMenu;
	HelpAboutMenu = new wxMenuItem( HelpMenu, wxID_ANY, wxString( wxT("About...") ) , wxEmptyString, wxITEM_NORMAL );
	HelpMenu->Append( HelpAboutMenu );

	MainMenuBar->Append( HelpMenu, wxT("Help") );

	this->SetMenuBar( MainMenuBar );

	wxBoxSizer* MainSizer;
	MainSizer = new wxBoxSizer( wxVERTICAL );

	MainVerticalSplitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	MainVerticalSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( CBaseFrame::MainVerticalSplitterOnIdle ), NULL, this );
	MainVerticalSplitter->SetMinimumPaneSize( 100 );

	TreePanel = new wxPanel( MainVerticalSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* TreeSizer;
	TreeSizer = new wxBoxSizer( wxVERTICAL );

	ProjectTree = new wxTreeCtrl( TreePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT );
	TreeSizer->Add( ProjectTree, 1, wxEXPAND|wxBOTTOM|wxLEFT, 5 );


	TreePanel->SetSizer( TreeSizer );
	TreePanel->Layout();
	TreeSizer->Fit( TreePanel );
	RightMainPanel = new wxPanel( MainVerticalSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* RightMainSizer;
	RightMainSizer = new wxBoxSizer( wxVERTICAL );

	MainHorizontalSplitter = new wxSplitterWindow( RightMainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	MainHorizontalSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( CBaseFrame::MainHorizontalSplitterOnIdle ), NULL, this );
	MainHorizontalSplitter->SetMinimumPaneSize( 100 );

	TopRightPanel = new wxPanel( MainHorizontalSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	BottomRightPanel = new wxPanel( MainHorizontalSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	LogTextCtrl = new wxTextCtrl( BottomRightPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH2 );
	bSizer8->Add( LogTextCtrl, 1, wxEXPAND|wxBOTTOM|wxRIGHT, 5 );


	BottomRightPanel->SetSizer( bSizer8 );
	BottomRightPanel->Layout();
	bSizer8->Fit( BottomRightPanel );
	MainHorizontalSplitter->SplitHorizontally( TopRightPanel, BottomRightPanel, -150 );
	RightMainSizer->Add( MainHorizontalSplitter, 1, wxEXPAND, 5 );

	ChkClearBeforeBuild = new wxCheckBox( RightMainPanel, wxID_ANY, wxT("Clear before build"), wxDefaultPosition, wxDefaultSize, 0 );
	ChkClearBeforeBuild->SetValue(true);
	RightMainSizer->Add( ChkClearBeforeBuild, 0, wxBOTTOM|wxLEFT, 5 );


	RightMainPanel->SetSizer( RightMainSizer );
	RightMainPanel->Layout();
	RightMainSizer->Fit( RightMainPanel );
	MainVerticalSplitter->SplitVertically( TreePanel, RightMainPanel, 250 );
	MainSizer->Add( MainVerticalSplitter, 1, wxEXPAND, 5 );


	this->SetSizer( MainSizer );
	this->Layout();
	MainTimer.SetOwner( this, wxID_ANY );
	MainToolbar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	ToolNew = MainToolbar->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("images/new.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("New project"), wxEmptyString, NULL );

	ToolOpen = MainToolbar->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("images/open.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Open project"), wxEmptyString, NULL );

	ToolSave = MainToolbar->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("images/save.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Save project"), wxEmptyString, NULL );

	MainToolbar->AddSeparator();

	ToolCut = MainToolbar->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("images/cut.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Cut"), wxEmptyString, NULL );

	ToolCopy = MainToolbar->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("images/copy.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Copy"), wxEmptyString, NULL );

	ToolPaste = MainToolbar->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("images/paste.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Paste"), wxEmptyString, NULL );

	MainToolbar->AddSeparator();

	ToolClean = MainToolbar->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("images/clean.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Clean project"), wxEmptyString, NULL );

	ToolBuild = MainToolbar->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("images/build.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Build project"), wxEmptyString, NULL );

	MainToolbar->Realize();


	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CBaseFrame::OnClose ) );
	ProjectMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnProjectNewMenu ), this, ProjectNewMenu->GetId());
	ProjectMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnProjectOpenMenu ), this, ProjectOpenMenu->GetId());
	ProjectMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnProjectSaveMenu ), this, ProjectSaveMenu->GetId());
	ProjectMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnProjectCloseMenu ), this, ProjectCloseMenu->GetId());
	ProjectMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnProjectExitMenu ), this, ProjectExitMenu->GetId());
	EditMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnMenuEditCut ), this, EditMenuCut->GetId());
	EditMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnMenuEditCopy ), this, EditMenuCopy->GetId());
	EditMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnEditMenuPaste ), this, EditMenuPaste->GetId());
	EditMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnMenuEditDelete ), this, EditMenuDelete->GetId());
	EditMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnEditMenuRename ), this, EditMenuRename->GetId());
	IEC61131Menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnGenerateFrameworkMenu ), this, BuildGenerateFrameworkMenu->GetId());
	IEC61131Menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnOpenBeremizEditor ), this, OpenBeremizMenu->GetId());
	BuildMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnBuildCleanupMenu ), this, BuildCleanupMenu->GetId());
	BuildMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnBuildMenu ), this, BuildBuildMenu->GetId());
	OptionsMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnOptionsGeneralMenu ), this, OptionsGeneralMenu->GetId());
	OptionsMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnShowPluginVersionMenu ), this, OptionsShowPluginVersionMenu->GetId());
	OptionsMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnOptionsCloseEditors ), this, OptionsCloseEditorsMenu->GetId());
	HelpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CBaseFrame::OnHelpAboutMenu ), this, HelpAboutMenu->GetId());
	ProjectTree->Connect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( CBaseFrame::OnTreeDoubleClick ), NULL, this );
	ProjectTree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( CBaseFrame::OnTreeSelChanged ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( CBaseFrame::OnMainTimer ) );
	this->Connect( ToolNew->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnProjectNewMenu ) );
	this->Connect( ToolOpen->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnProjectOpenMenu ) );
	this->Connect( ToolSave->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnProjectSaveMenu ) );
	this->Connect( ToolCut->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnMenuEditCut ) );
	this->Connect( ToolCopy->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnMenuEditCopy ) );
	this->Connect( ToolPaste->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnMenuEditPaste ) );
	this->Connect( ToolClean->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnBuildCleanupMenu ) );
	this->Connect( ToolBuild->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnBuildMenu ) );
}

CBaseFrame::~CBaseFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CBaseFrame::OnClose ) );
	ProjectTree->Disconnect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( CBaseFrame::OnTreeDoubleClick ), NULL, this );
	ProjectTree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( CBaseFrame::OnTreeSelChanged ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( CBaseFrame::OnMainTimer ) );
	this->Disconnect( ToolNew->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnProjectNewMenu ) );
	this->Disconnect( ToolOpen->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnProjectOpenMenu ) );
	this->Disconnect( ToolSave->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnProjectSaveMenu ) );
	this->Disconnect( ToolCut->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnMenuEditCut ) );
	this->Disconnect( ToolCopy->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnMenuEditCopy ) );
	this->Disconnect( ToolPaste->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnMenuEditPaste ) );
	this->Disconnect( ToolClean->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnBuildCleanupMenu ) );
	this->Disconnect( ToolBuild->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( CBaseFrame::OnBuildMenu ) );

}

CSelectionCPUDialog::CSelectionCPUDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("CPU Model") ), wxVERTICAL );

	wxArrayString CPUModelChoiceChoices;
	CPUModelChoice = new wxChoice( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, CPUModelChoiceChoices, 0 );
	CPUModelChoice->SetSelection( 0 );
	sbSizer2->Add( CPUModelChoice, 0, wxALL|wxEXPAND, 5 );

	CPUInformation = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_NO_VSCROLL|wxTE_READONLY );
	CPUInformation->SetMinSize( wxSize( -1,75 ) );

	sbSizer2->Add( CPUInformation, 0, wxEXPAND|wxALL, 5 );


	bSizer2->Add( sbSizer2, 1, wxEXPAND|wxALL, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );


	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );

	OKBtn = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( OKBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );

	CancelBtn = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( CancelBtn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer2 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	CPUModelChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( CSelectionCPUDialog::OnCPUModelChoice ), NULL, this );
	OKBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSelectionCPUDialog::OnOKButton ), NULL, this );
	CancelBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSelectionCPUDialog::OnCancelButton ), NULL, this );
}

CSelectionCPUDialog::~CSelectionCPUDialog()
{
	// Disconnect Events
	CPUModelChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( CSelectionCPUDialog::OnCPUModelChoice ), NULL, this );
	OKBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSelectionCPUDialog::OnOKButton ), NULL, this );
	CancelBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSelectionCPUDialog::OnCancelButton ), NULL, this );

}

CPluginInfoDialog::CPluginInfoDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 4, 2, 0, 0 );

	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("Plugin name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	gSizer1->Add( m_staticText9, 0, wxALL|wxALIGN_RIGHT, 5 );

	LblPluginName = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	LblPluginName->Wrap( -1 );
	gSizer1->Add( LblPluginName, 0, wxALL, 5 );

	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("CPU Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	gSizer1->Add( m_staticText11, 0, wxALL|wxALIGN_RIGHT, 5 );

	LBLCPUName = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	LBLCPUName->Wrap( -1 );
	gSizer1->Add( LBLCPUName, 0, wxALL, 5 );

	m_staticText13 = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	gSizer1->Add( m_staticText13, 0, wxALL|wxALIGN_RIGHT, 5 );

	LblVersion = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	LblVersion->Wrap( -1 );
	gSizer1->Add( LblVersion, 0, wxALL, 5 );


	bSizer13->Add( gSizer1, 1, wxEXPAND, 5 );

	m_button5 = new wxButton( this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_button5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	this->SetSizer( bSizer13 );
	this->Layout();

	this->Centre( wxBOTH );
}

CPluginInfoDialog::~CPluginInfoDialog()
{
}

AboutDialog::AboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* container;
	container = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* sizer;
	sizer = new wxBoxSizer( wxVERTICAL );

	m_staticText11 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	sizer->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	ImageLogo = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("icon_96_96"), wxBITMAP_TYPE_RESOURCE ), wxDefaultPosition, wxDefaultSize, 0 );
	ImageLogo->SetMinSize( wxSize( 96,96 ) );

	sizer->Add( ImageLogo, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM, 5 );

	m_staticText12 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	sizer->Add( m_staticText12, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	name = new wxStaticText( this, wxID_ANY, wxT("Beremiz Project Manager"), wxDefaultPosition, wxDefaultSize, 0 );
	name->Wrap( -1 );
	name->SetFont( wxFont( 18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	sizer->Add( name, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM, 10 );

	description = new wxStaticText( this, wxID_ANY, wxT("Project Manager for Open Source Beremiz IEC61131-3 IDE"), wxDefaultPosition, wxDefaultSize, 0 );
	description->Wrap( 400 );
	sizer->Add( description, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM, 5 );

	VersionStr = new wxStaticText( this, wxID_ANY, wxT("Version"), wxDefaultPosition, wxDefaultSize, 0 );
	VersionStr->Wrap( -1 );
	sizer->Add( VersionStr, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL, 5 );

	wxcredit = new wxStaticText( this, wxID_ANY, wxT("Beremiz Project Manager is built using wxWidgets 3.2"), wxDefaultPosition, wxDefaultSize, 0 );
	wxcredit->Wrap( -1 );
	sizer->Add( wxcredit, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM, 5 );

	copyright = new wxStaticText( this, wxID_ANY, wxT("(C) Benoit BOUCHEZ (BEB) - 2021/2024"), wxDefaultPosition, wxDefaultSize, 0 );
	copyright->Wrap( -1 );
	sizer->Add( copyright, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM, 10 );


	container->Add( sizer, 0, wxEXPAND, 5 );

	wxBoxSizer* BtnSizer;
	BtnSizer = new wxBoxSizer( wxVERTICAL );


	BtnSizer->Add( 0, 0, 1, wxEXPAND, 5 );

	BtnClose = new wxButton( this, wxID_CANCEL, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	BtnSizer->Add( BtnClose, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	container->Add( BtnSizer, 0, wxALIGN_CENTER_HORIZONTAL, 5 );


	this->SetSizer( container );
	this->Layout();

	this->Centre( wxBOTH );
}

AboutDialog::~AboutDialog()
{
}

CProjectManagerOptionsDialog::CProjectManagerOptionsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("PLC base files location") ), wxVERTICAL );

	EditBaseFilesLocation = new wxTextCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( EditBaseFilesLocation, 0, wxALL|wxEXPAND, 5 );

	PLCBaseFilesBrowseBtn = new wxButton( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( PLCBaseFilesBrowseBtn, 0, wxALL, 5 );


	bSizer14->Add( sbSizer5, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

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
	PLCBaseFilesBrowseBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CProjectManagerOptionsDialog::OnBrowseButton ), NULL, this );
	m_sdbSizer1Cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CProjectManagerOptionsDialog::OnCancelBtn ), NULL, this );
	m_sdbSizer1OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CProjectManagerOptionsDialog::OnOKBtn ), NULL, this );
}

CProjectManagerOptionsDialog::~CProjectManagerOptionsDialog()
{
	// Disconnect Events
	PLCBaseFilesBrowseBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CProjectManagerOptionsDialog::OnBrowseButton ), NULL, this );
	m_sdbSizer1Cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CProjectManagerOptionsDialog::OnCancelBtn ), NULL, this );
	m_sdbSizer1OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CProjectManagerOptionsDialog::OnOKBtn ), NULL, this );

}

NoParamPanel::NoParamPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	ProjectEntitySizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Project element") ), wxVERTICAL );

	EditableLabel = new wxStaticText( ProjectEntitySizer->GetStaticBox(), wxID_ANY, wxT("No editable parameter for this element"), wxDefaultPosition, wxDefaultSize, 0 );
	EditableLabel->Wrap( -1 );
	ProjectEntitySizer->Add( EditableLabel, 0, wxALL, 5 );


	bSizer13->Add( ProjectEntitySizer, 1, wxEXPAND|wxALL, 5 );


	this->SetSizer( bSizer13 );
	this->Layout();
}

NoParamPanel::~NoParamPanel()
{
}
