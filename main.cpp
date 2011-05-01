/* 
ebook2cwgui - A GUI for ebook2cw

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

#include "main.h"
#include "ebook2cwgui.h"

        IMPLEMENT_APP(MyApp)


bool MyApp::OnInit() {
	Ebook2cw *ebook2cw = new Ebook2cw(wxT("ebook2cw-gui v0.1.0"));
	ebook2cw->Show(true);
	return true;
}

