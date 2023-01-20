///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-254-gc2ef7767)
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
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/gbsizer.h>
#include <wx/statbox.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainWindow
///////////////////////////////////////////////////////////////////////////////
class MainWindow : public wxFrame
{
	private:

	protected:
		wxPanel* m_panel6;
		wxButton* m_add;
		wxButton* m_remove;
		wxButton* m_activate;
		wxButton* m_deactivate;
		wxButton* m_toggleStartup;

		// Virtual event handlers, override them in your derived class
		virtual void m_addOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_removeOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_activateOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_deactivateOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_toggleStartupOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxListBox* m_listBox4;

		MainWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Parental Controls GUI"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 494,368 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainWindow();

};

///////////////////////////////////////////////////////////////////////////////
/// Class NoRootPopup
///////////////////////////////////////////////////////////////////////////////
class NoRootPopup : public wxDialog
{
	private:

	protected:
		wxStaticText* NoRootText;
		wxButton* m_ok;

		// Virtual event handlers, override them in your derived class
		virtual void m_okOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		NoRootPopup( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Insufficient Permissions"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~NoRootPopup();

};

///////////////////////////////////////////////////////////////////////////////
/// Class AddProgram
///////////////////////////////////////////////////////////////////////////////
class AddProgram : public wxDialog
{
	private:

	protected:
		wxTextCtrl* inputprogram;
		wxButton* m_add;

	public:

		AddProgram( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Add Program"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~AddProgram();

};

