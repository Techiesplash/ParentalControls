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
#include <wx/listbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/gbsizer.h>
#include <wx/statbox.h>
#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/stattext.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainWindow
///////////////////////////////////////////////////////////////////////////////
class MainWindow : public wxFrame
{
	private:

	protected:
		wxListBox* m_listBox4;
		wxPanel* m_panel6;
		wxTextCtrl* m_textinput;
		wxButton* m_add;
		wxButton* m_remove;
		wxButton* m_sync;
		wxButton* m_activate;
		wxButton* m_deactivate;
		wxButton* m_toggleStartup;

		// Virtual event handlers, override them in your derived class
		virtual void m_addOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_removeOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_syncOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_activateOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_deactivateOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_toggleStartupOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Parental Controls Prototype Interface"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 494,353 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainWindow();

};

///////////////////////////////////////////////////////////////////////////////
/// Class PasswordWindow
///////////////////////////////////////////////////////////////////////////////
class PasswordWindow : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_passtext;
		wxButton* m_passwordConfirm;

		// Virtual event handlers, override them in your derived class
		virtual void m_passConfirmOnClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		PasswordWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Password"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 117,101 ), long style = wxDEFAULT_DIALOG_STYLE );

		~PasswordWindow();

};

///////////////////////////////////////////////////////////////////////////////
/// Class noroot
///////////////////////////////////////////////////////////////////////////////
class noroot : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxButton* m_ok;

		// Virtual event handlers, override them in your derived class
		virtual void m_okOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		noroot( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Insufficient Permissions"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~noroot();

};

