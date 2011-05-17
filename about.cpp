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


BEGIN_EVENT_TABLE(About, wxFrame)
END_EVENT_TABLE()

About::About(const wxString& title) : wxFrame(NULL, -1, title, wxPoint(-1, -1), 
#ifdef __WXMSW__
		wxSize(455, 400)
#else
		wxSize(550, 400)
#endif	
) {

//	SetIcon(wxIcon(ebook2cw_xpm));

	wxPanel *panel = new wxPanel(this, -1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText *about = new wxStaticText(panel, wxID_ANY,
				wxT("ebook2cw-gui v0.1.0 - FAPPPP\n\nWe are le fap."));
	about->Wrap(500);
	hbox1->Add(about);

	vbox->Add(hbox1);

	panel->SetSizer(vbox);
	Centre();
}


