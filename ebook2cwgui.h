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


#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/taskbar.h>
#include <wx/filepicker.h>
#include <wx/hyperlink.h>
#include <wx/textfile.h>
#include <wx/stdpaths.h>

class Ebook2cw : public wxFrame
{
	public:
		Ebook2cw(const wxString& title);
		void OnQuit(wxCommandEvent & event);
		void Convert(wxCommandEvent & event);
		void OnFileChange(wxFileDirPickerEvent& event);
		void OnDirChange(wxFileDirPickerEvent& event);
		void OnChapterStringChange(wxCommandEvent & event);
		void OnWpmChange(wxSpinEvent & event);
		void OnWpmeChange(wxSpinEvent & event);
		void OnEwsChange(wxSpinEvent & event);
		void OnQrqChange(wxSpinEvent & event);
		void OnToneChange(wxSpinEvent & event);
		void OnWaveChange (wxCommandEvent & event);
		void OnOutfileChange(wxCommandEvent & event);
		void OnAuthorChange(wxCommandEvent & event);
		void OnTitleChange(wxCommandEvent & event);
		void OnCommentChange(wxCommandEvent & event);
		void OnYearChange(wxCommandEvent & event);
		void OnFormatChange(wxCommandEvent & event);
		void OnResetQrqChange(wxCommandEvent & event);
		void OnNoBTChange(wxCommandEvent & event);
		void OnAddParamChange(wxCommandEvent & event);
		void OnWebsiteLinkHover(wxMouseEvent & event);
		DECLARE_EVENT_TABLE()
	private:
		WX_DECLARE_STRING_HASH_MAP(wxString, ParamH);
		ParamH h; /* Hash for command line params */
		wxString InFilename;
		wxString OutDir;
		wxString AddParam;
		bool ResetQrq, NoBT;
		void ReadConfigFile();
		void SaveConfigFile(wxCommandEvent & event);
		wxString FindConfigFile();
};

