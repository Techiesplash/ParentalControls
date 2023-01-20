///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-254-gc2ef7767)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Program List") ), wxVERTICAL );

	m_listBox4 = new wxListBox( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( 480,200 ), 0, NULL, 0 );
	m_listBox4->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWFRAME ) );

	sbSizer3->Add( m_listBox4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_panel6 = new wxPanel( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	m_add = new wxButton( m_panel6, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_add, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_remove = new wxButton( m_panel6, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_remove, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	m_panel6->SetSizer( bSizer6 );
	m_panel6->Layout();
	bSizer6->Fit( m_panel6 );
	sbSizer3->Add( m_panel6, 1, wxEXPAND | wxALL, 5 );

	wxGridBagSizer* gbSizer2;
	gbSizer2 = new wxGridBagSizer( 0, 0 );
	gbSizer2->SetFlexibleDirection( wxBOTH );
	gbSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_activate = new wxButton( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( m_activate, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_deactivate = new wxButton( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Stop"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( m_deactivate, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	m_toggleStartup = new wxButton( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Auto-Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( m_toggleStartup, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	sbSizer3->Add( gbSizer2, 1, wxEXPAND, 5 );


	this->SetSizer( sbSizer3 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_add->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::m_addOnButtonClick ), NULL, this );
	m_remove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::m_removeOnButtonClick ), NULL, this );
	m_activate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::m_activateOnButtonClick ), NULL, this );
	m_deactivate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::m_deactivateOnButtonClick ), NULL, this );
	m_toggleStartup->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::m_toggleStartupOnButtonClick ), NULL, this );
}

MainWindow::~MainWindow()
{
	// Disconnect Events
	m_add->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::m_addOnButtonClick ), NULL, this );
	m_remove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::m_removeOnButtonClick ), NULL, this );
	m_activate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::m_activateOnButtonClick ), NULL, this );
	m_deactivate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::m_deactivateOnButtonClick ), NULL, this );
	m_toggleStartup->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::m_toggleStartupOnButtonClick ), NULL, this );

}

NoRootPopup::NoRootPopup( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	NoRootText = new wxStaticText( this, wxID_ANY, wxT("This program requires Root permissions to do things. Please try launching this as root."), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	NoRootText->Wrap( 250 );
	bSizer3->Add( NoRootText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_ok = new wxButton( this, wxID_ANY, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );

	m_ok->SetBitmapPosition( wxBOTTOM );
	bSizer3->Add( m_ok, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	this->SetSizer( bSizer3 );
	this->Layout();
	bSizer3->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	m_ok->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoRootPopup::m_okOnButtonClick ), NULL, this );
}

NoRootPopup::~NoRootPopup()
{
	// Disconnect Events
	m_ok->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoRootPopup::m_okOnButtonClick ), NULL, this );

}

AddProgram::AddProgram( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	inputprogram = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxPoint( -1,-1 ), wxSize( 200,-1 ), 0 );
	bSizer3->Add( inputprogram, 0, wxALL, 5 );

	m_add = new wxButton( this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_add, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	this->SetSizer( bSizer3 );
	this->Layout();
	bSizer3->Fit( this );

	this->Centre( wxBOTH );
}

AddProgram::~AddProgram()
{
}
