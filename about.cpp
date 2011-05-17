/* 
ebook2cwgui - a GUI for ebook2cw

Copyright (C) 2011  Fabian Kurz, DJ1YFK

$Id$

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA  02110-1301, USA.

*/


#include "about.h"

enum {
	ABOUT_close = 1
};


BEGIN_EVENT_TABLE(About, wxFrame)
	EVT_BUTTON(ABOUT_close,  About::OnClose)
END_EVENT_TABLE()

About::About(const wxString& title) : wxFrame(NULL, -1, title, wxPoint(-1, -1), 
#ifdef __WXMSW__
		wxSize(455, 400)
#else
		wxSize(450, 200)
#endif	
) {

	wxPanel *panel = new wxPanel(this, -1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	wxStaticText *about = new wxStaticText(panel, wxID_ANY,
	wxT("ebook2cw-gui v0.1.0 - (c) 2011 by Fabian Kurz, DJ1YFK\n\n"
	"A Graphical User Interface (GUI) for ebook2cw\n\n"
	"This is free software, and you are welcome to redistribute it\n"
	"under certain conditions (see COPYING).\n\n"
	"For help and documentation, please refer to the project website:"));
	
	wxHyperlinkCtrl *link = new wxHyperlinkCtrl(panel, wxID_ANY,
       	wxT("http://fkurz.net/ham/ebook2cw.html"), wxT("http://fkurz.net/ham/ebook2cw.html"));

	wxButton *close = new wxButton(panel, ABOUT_close, wxT("Close"));

	vbox->Add(about);
	vbox->Add(link);

	vbox->Add(-1, 10);

	vbox->Add(close);

	panel->SetSizer(vbox);
	Centre();
}

void About::OnClose (wxCommandEvent & WXUNUSED(event)) {
	this->Destroy();
}

