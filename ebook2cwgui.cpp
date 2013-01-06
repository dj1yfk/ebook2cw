/* 
ebook2cwgui - a GUI for ebook2cw

Copyright (C) 2011 - 2013  Fabian Kurz, DJ1YFK

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

#include "ebook2cwgui.h"
#include "ebook2cw.xpm"

#define MINE2CVERSIONA 0	/* Minimum required ebook2cw version 0.8.2 */
#define MINE2CVERSIONB 8
#define MINE2CVERSIONC 2

enum {
	E2C_infilepick = 1,
	E2C_outdirpick,
	E2C_chapterstring,
	E2C_wpm,
	E2C_wpme,
	E2C_ews,
	E2C_qrq,
	E2C_tone,
	E2C_wave,
	E2C_outfile,
	E2C_author,
	E2C_title,
	E2C_comment,
	E2C_year,
	E2C_fileformat,
	E2C_limitwordsspin,
	E2C_limitsecondsspin,
	E2C_resetqrq,
	E2C_noBT,
	E2C_addparam,
	E2C_saveconf,
	E2C_about,
	E2C_websitelink,
	E2C_convert,
	E2C_quit
};


BEGIN_EVENT_TABLE(Ebook2cw, wxFrame)
	EVT_BUTTON(E2C_quit,  Ebook2cw::OnQuit)
	EVT_BUTTON(E2C_convert,  Ebook2cw::Convert)
	EVT_BUTTON(E2C_saveconf,  Ebook2cw::SaveConfigFile)
	EVT_BUTTON(E2C_about,  Ebook2cw::ShowAbout)
	EVT_FILEPICKER_CHANGED(E2C_infilepick, Ebook2cw::OnFileChange)
	EVT_DIRPICKER_CHANGED(E2C_outdirpick, Ebook2cw::OnDirChange)
	EVT_TEXT(E2C_chapterstring, Ebook2cw::OnChapterStringChange)
	EVT_SPINCTRL(E2C_wpm, Ebook2cw::OnWpmChange) 
	EVT_SPINCTRL(E2C_wpme, Ebook2cw::OnWpmeChange) 
	EVT_SPINCTRL(E2C_ews, Ebook2cw::OnEwsChange) 
	EVT_SPINCTRL(E2C_qrq, Ebook2cw::OnQrqChange) 
	EVT_SPINCTRL(E2C_tone, Ebook2cw::OnToneChange) 
	EVT_SPINCTRL(E2C_limitwordsspin, Ebook2cw::OnLimitWordsChange) 
	EVT_SPINCTRL(E2C_limitsecondsspin, Ebook2cw::OnLimitSecondsChange) 
	EVT_CHOICE(E2C_wave, Ebook2cw::OnWaveChange) 
	EVT_TEXT(E2C_outfile, Ebook2cw::OnOutfileChange)
	EVT_TEXT(E2C_author, Ebook2cw::OnAuthorChange)
	EVT_TEXT(E2C_title, Ebook2cw::OnTitleChange)
	EVT_TEXT(E2C_comment, Ebook2cw::OnCommentChange)
	EVT_TEXT(E2C_year, Ebook2cw::OnYearChange)
	EVT_CHOICE(E2C_fileformat, Ebook2cw::OnFormatChange) 
	EVT_CHECKBOX(E2C_resetqrq, Ebook2cw::OnResetQrqChange) 
	EVT_CHECKBOX(E2C_noBT, Ebook2cw::OnNoBTChange) 
	EVT_TEXT(E2C_addparam, Ebook2cw::OnAddParamChange) 
END_EVENT_TABLE()

Ebook2cw::Ebook2cw(const wxString& title) : wxFrame(NULL, -1, title, wxPoint(-1, -1), 
#ifdef __WXMSW__
		wxSize(455, 480)
#else
		wxSize(500, 550)
#endif	
) {


	long tmp;

#ifdef __WXMSW__
	int spinX = 50;
	int spinY = 21;
#else
	int spinX = wxDefaultSize.x;
	int spinY = wxDefaultSize.y;
#endif	

	Ebook2cwCmd = wxT("ebook2cw");

	SetIcon(wxIcon(ebook2cw_xpm));
	CreateStatusBar();
	SetStatusText(wxT("Initializing ebook2cw-gui"));

	h[wxT("w")] = wxT("25");
	h[wxT("e")] = wxT("0");
	h[wxT("W")] = wxT("0");
	h[wxT("Q")] = wxT("0");
	h[wxT("f")] = wxT("600");
	h[wxT("T")] = wxT("1");
	h[wxT("o")] = wxT("Chapter");
	h[wxT("c")] = wxT("Chapter");

	ReadConfigFile();

	wxPanel *panel = new wxPanel(this, -1);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox6 = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText *t_infile =  new wxStaticText(panel, wxID_ANY, 
			wxT("Ebook text file to convert:"));
	hbox1->Add(t_infile, 0, wxEXPAND);
	vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

	wxFilePickerCtrl *btn_infilepick = new wxFilePickerCtrl(panel, 
			E2C_infilepick, wxEmptyString, wxT("Select file..."), 
			wxT("*.*"), wxDefaultPosition, wxDefaultSize,
			wxFLP_DEFAULT_STYLE | wxFLP_USE_TEXTCTRL 
			);
	vbox->Add(btn_infilepick, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

	wxStaticText *t_outdir =  new wxStaticText(panel, wxID_ANY, 
			wxT("Directory for output files:"));
	hbox3->Add(t_outdir, 0, wxEXPAND);
	vbox->Add(hbox3, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

	wxDirPickerCtrl *btn_outdirpick = new wxDirPickerCtrl(panel, 
			E2C_outdirpick, wxEmptyString, 
			wxT("Select directory..."), 
			wxDefaultPosition, wxDefaultSize,
			wxDIRP_DEFAULT_STYLE | wxDIRP_USE_TEXTCTRL 
			);
	vbox->Add(btn_outdirpick, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);


	wxStaticText *t_chapsep =  new wxStaticText(panel, wxID_ANY, 
			wxT("Chapter separator string:"));
	wxTextCtrl *tc_chapsep = new wxTextCtrl(panel, E2C_chapterstring);
	tc_chapsep->ChangeValue(h[wxT("c")]);
	hbox5->Add(t_chapsep, 1);
	hbox5->Add(tc_chapsep, 2, wxEXPAND);

	vbox->Add(hbox5, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);



	wxStaticBox *box_cwparam = new wxStaticBox(panel, wxID_ANY, wxT("CW parameters"));
	wxStaticBoxSizer *sbox1=new wxStaticBoxSizer(box_cwparam, wxVERTICAL);

	wxFlexGridSizer *flexgrid1 = new wxFlexGridSizer(2,0,0);


	wxStaticText *t_wpm =  new wxStaticText(panel, wxID_ANY, wxT("Speed (WpM):"));
	h[wxT("w")].ToLong(&tmp);
	wxSpinCtrl *spin_wpm = new wxSpinCtrl(panel, E2C_wpm, wxEmptyString, wxDefaultPosition,
		       wxSize(spinX,spinY), wxSP_ARROW_KEYS, 5, 150, tmp);
	
	wxStaticText *t_wpme =  new wxStaticText(panel, wxID_ANY, wxT("eff. Speed (WpM):"));
	h[wxT("e")].ToLong(&tmp);
	wxSpinCtrl *spin_wpme = new wxSpinCtrl(panel, E2C_wpme, wxEmptyString, wxDefaultPosition,
		wxSize(spinX,spinY), wxSP_ARROW_KEYS, 0, 150, tmp);
	
	wxStaticText *t_ews =  new wxStaticText(panel, wxID_ANY, wxT("extra Word space:"));
	h[wxT("W")].ToLong(&tmp);
	wxSpinCtrl *spin_ews = new wxSpinCtrl(panel, E2C_ews, wxEmptyString, wxDefaultPosition,
			                       wxSize(spinX,spinY), wxSP_ARROW_KEYS, 0, 10, tmp);
	
	wxStaticText *t_qrq =  new wxStaticText(panel, wxID_ANY, wxT("QRQ (mins, 0 = off):"));
	h[wxT("Q")].ToLong(&tmp);
	wxSpinCtrl *spin_qrq = new wxSpinCtrl(panel, E2C_qrq, wxEmptyString, wxDefaultPosition,
			                       wxSize(spinX,spinY), wxSP_ARROW_KEYS, 0, 60, tmp);
	
	wxStaticText *t_tone =  new wxStaticText(panel, wxID_ANY, wxT("Tone (Hz):"));
	h[wxT("f")].ToLong(&tmp);
	wxSpinCtrl *spin_tone = new wxSpinCtrl(panel, E2C_tone, wxEmptyString, wxDefaultPosition,
			                       wxSize(spinX,spinY), wxSP_ARROW_KEYS, 200, 1000, tmp);

	wxStaticText *t_wave =  new wxStaticText(panel, wxID_ANY, wxT("Waveform:"));
	wxString choices[3] = {wxT("Sine"), wxT("Sawtooth"), wxT("Square")};
	wxChoice *choice_wave = new wxChoice(panel, E2C_wave, wxDefaultPosition, wxDefaultSize, 3, choices);

	h[wxT("T")].ToLong(&tmp);
	if (tmp > 0 && tmp < 4) /* numerical */
		choice_wave->SetSelection(tmp-1);
	else {
		if (h[wxT("T")] == wxT("SINE"))
			choice_wave->SetSelection(0);
		else if (h[wxT("T")] == wxT("SAWTOOTH"))
			choice_wave->SetSelection(1);
		else if (h[wxT("T")] == wxT("SQUARE"))
			choice_wave->SetSelection(2);
	}

	flexgrid1->Add(t_wpm); flexgrid1->Add(spin_wpm);
	flexgrid1->Add(t_wpme); flexgrid1->Add(spin_wpme);
	flexgrid1->Add(t_ews); flexgrid1->Add(spin_ews);
	flexgrid1->Add(t_qrq); flexgrid1->Add(spin_qrq);
	flexgrid1->Add(t_tone); flexgrid1->Add(spin_tone);
	flexgrid1->Add(t_wave); flexgrid1->Add(choice_wave,1,wxEXPAND);
	flexgrid1->AddGrowableCol(0);

	sbox1->Add(flexgrid1, 1, wxEXPAND);
	hbox6->Add(sbox1, 1);

	wxStaticBox *box_outparam = new wxStaticBox(panel, wxID_ANY, wxT("Output File Options"));
	wxStaticBoxSizer *sbox2=new wxStaticBoxSizer(box_outparam, wxVERTICAL);
	
	wxStaticText *t_filename =  new wxStaticText(panel, wxID_ANY, wxT("Filename:"));
	wxTextCtrl   *tc_filename = new wxTextCtrl(panel, E2C_outfile);
	tc_filename->ChangeValue(h[wxT("o")]);

	wxStaticText *t_author =  new wxStaticText(panel, wxID_ANY, wxT("Author:"));
	wxTextCtrl   *tc_author = new wxTextCtrl(panel, E2C_author);
	tc_author->ChangeValue(h[wxT("a")]);

	wxStaticText *t_title =  new wxStaticText(panel, wxID_ANY, wxT("Title:"));
	wxTextCtrl   *tc_title = new wxTextCtrl(panel, E2C_title);
	tc_title->ChangeValue(h[wxT("t")]);
	
	wxStaticText *t_comment =  new wxStaticText(panel, wxID_ANY, wxT("Comment:"));
	wxTextCtrl   *tc_comment = new wxTextCtrl(panel, E2C_comment);
	tc_comment->ChangeValue(h[wxT("k")]);
	
	wxStaticText *t_year=  new wxStaticText(panel, wxID_ANY, wxT("Year:"));
	wxTextCtrl   *tc_year = new wxTextCtrl(panel, E2C_year);
	tc_comment->ChangeValue(h[wxT("y")]);
	
	wxStaticText *t_format=  new wxStaticText(panel, wxID_ANY, wxT("File Format:"));
	wxString formats[2] = {wxT("MP3"), wxT("OGG")};
	wxChoice *choice_format = new wxChoice(panel, E2C_fileformat, wxDefaultPosition, wxDefaultSize, 2, formats);
	if (h.find(wxT("O")) != h.end())
		choice_format->SetSelection(1);
	else 
		choice_format->SetSelection(0);

	wxFlexGridSizer *flexgrid2 = new wxFlexGridSizer(2,0,0);

	flexgrid2->Add(t_filename); flexgrid2->Add(tc_filename, 1, wxEXPAND);
	flexgrid2->Add(t_author); flexgrid2->Add(tc_author, 1, wxEXPAND);
	flexgrid2->Add(t_title); flexgrid2->Add(tc_title, 1, wxEXPAND);
	flexgrid2->Add(t_comment); flexgrid2->Add(tc_comment, 1, wxEXPAND);
	flexgrid2->Add(t_year); flexgrid2->Add(tc_year, 1, wxEXPAND);
	flexgrid2->Add(t_format); flexgrid2->Add(choice_format, 1, wxEXPAND);
	flexgrid2->AddGrowableCol(1,1);

	sbox2->Add(flexgrid2, 1, wxEXPAND);
	hbox6->Add(sbox2, 1);

	vbox->Add(hbox6, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
	
	wxStaticText *t_limitwords = new wxStaticText(panel, wxID_ANY, wxT("Limit words per chapter to (0 = off): "));
	h[wxT("l")].ToLong(&tmp);
	wxSpinCtrl *spin_limitwords = new wxSpinCtrl(panel, E2C_limitwordsspin, wxEmptyString, wxDefaultPosition,
			                       wxSize(spinX,spinY), wxSP_ARROW_KEYS, 0, 10000, tmp);
	wxStaticText *t_limitseconds = new wxStaticText(panel, wxID_ANY, wxT("Limit chapter duration to (sec, 0 = off): "));
	h[wxT("d")].ToLong(&tmp);
	wxSpinCtrl *spin_limitseconds = new wxSpinCtrl(panel, E2C_limitsecondsspin, wxEmptyString, wxDefaultPosition,
			                       wxSize(spinX,spinY), wxSP_ARROW_KEYS, 0, 10000, tmp);


	wxFlexGridSizer *flexgrid3 = new wxFlexGridSizer(2,0,0);
	flexgrid3->Add(t_limitwords); flexgrid3->Add(spin_limitwords, 1, wxEXPAND);
	flexgrid3->Add(t_limitseconds); flexgrid3->Add(spin_limitseconds, 1, wxEXPAND);
	
	vbox->Add(flexgrid3, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
	
	
	wxBoxSizer *hbox7 = new wxBoxSizer(wxHORIZONTAL);
	wxCheckBox *cb_resetspeed = new wxCheckBox(panel, E2C_resetqrq, wxT("Reset speed for each chapter"));
	wxCheckBox *cb_noBT = new wxCheckBox(panel, E2C_noBT, wxT("Disable <BT> for paragraphs"));
	
	if (h.find(wxT("n")) == h.end()) cb_resetspeed->SetValue(true);
	if (h.find(wxT("p")) != h.end()) cb_noBT->SetValue(true);

	hbox7->Add(cb_resetspeed, 1, wxEXPAND);
	hbox7->Add(cb_noBT);
	vbox->Add(hbox7, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

	 vbox->Add(-1, 10);

	wxBoxSizer *hbox8 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *t_addparams =  new wxStaticText(panel, wxID_ANY, wxT("Additional parameters:"));
	wxTextCtrl *tc_addparams = new wxTextCtrl(panel, E2C_addparam);
	hbox8->Add(t_addparams, 1);
	hbox8->Add(tc_addparams, 2, wxEXPAND);
	vbox->Add(hbox8, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

	 vbox->Add(-1, 15);

	wxBoxSizer *hbox9 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *vbox2 = new wxBoxSizer(wxVERTICAL);
	wxHyperlinkCtrl *projectlink = new wxHyperlinkCtrl(panel, E2C_websitelink, wxT("ebook2cw-gui v0.1.1"), wxT("http://fkurz.net/ham/ebook2cw.html"));	
	wxStaticText *projectlink2 = new wxStaticText(panel, E2C_websitelink, wxT("by Fabian Kurz, DJ1YFK"));	
	vbox2->Add(projectlink);
	vbox2->Add(projectlink2);

	projectlink->Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(Ebook2cw::OnWebsiteLinkHover),NULL,this); 

	wxButton *btn_about = new wxButton(panel, E2C_about, wxT("About"));
	wxButton *btn_saveconf = new wxButton(panel, E2C_saveconf, wxT("Save conf."));
	wxButton *btn_convert = new wxButton(panel, E2C_convert, wxT("Convert"));
	wxButton *btn_exit = new wxButton(panel, E2C_quit, wxT("Quit"));

	hbox9->Add(vbox2, 2, wxEXPAND);
	hbox9->Add(btn_about,1);
	hbox9->Add(btn_saveconf,1);
	hbox9->Add(btn_convert,1);
	hbox9->Add(btn_exit,1);
	vbox->Add(hbox9, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

	panel->SetSizer(vbox);
	Centre();

	FindExecutable();
}



void Ebook2cw::OnFileChange(wxFileDirPickerEvent& event) {
	
	InFilename = event.GetPath();
	
	wxString ptf = IsPlaintext(InFilename);
	
	if (ptf != wxT("yes")) {
		wxMessageBox(wxT("This looks like a ") + ptf + wxT(" file. You should convert it to plain text before translating it with ebook2cw."), wxT("Warning"), wxOK | wxICON_EXCLAMATION);
	}

	// Find out encoding by running ebook2cw -g
	wxArrayString output, errors;
	wxString cmd = Ebook2cwCmd + wxT(" -g\"") + event.GetPath() + wxT("\"");

	int code = wxExecute(cmd, output, errors);

	if (code != -1) {
		output.RemoveAt(output.Count()-1, 1);
		if (output.Last().Contains(wxT("UTF"))) {
			SetStatusText(wxT("File format detected: UTF-8"));
			h[wxT("u")] = wxT("");
		}
		else {
			SetStatusText(wxT("File format detected: ISO 8859-1"));
			h.erase(wxT("u"));
		}
	}
	else {
		SetStatusText(wxT("Unable to detect file format. Assuming UTF-8."));
	}

}

void Ebook2cw::OnDirChange(wxFileDirPickerEvent& event) {
	OutDir = event.GetPath();
	SetStatusText(wxT("Output folder set to: ") + OutDir);
}

void Ebook2cw::OnQuit(wxCommandEvent & WXUNUSED(event)) {
	wxMessageDialog *quit = new wxMessageDialog(NULL, 
		wxT("Are you sure to quit?"), wxT("Question"), 
		wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
	if (quit->ShowModal() == wxID_YES) 
		Close(true);
}

void Ebook2cw::OnChapterStringChange(wxCommandEvent & event) {
	h[wxT("c")] = event.GetString();
}

void Ebook2cw::Convert(wxCommandEvent & WXUNUSED(event)) {
	wxString command;
	wxString tmp;

	/* sanity check: We need at least an input file and out dir */

	if (!wxFileExists(InFilename)) {
		wxMessageBox(wxT("Please select an input file!"), wxT("Error"), wxOK | wxICON_EXCLAMATION);
		return;
	}
	
	if (!(InFilename)) {
		wxMessageBox(wxT("Please select an input file!"), wxT("Error"), wxOK | wxICON_EXCLAMATION);
		return;
	}

	if (!wxDirExists(OutDir)) {
		wxMessageBox(wxT("Please select an output directory!"), wxT("Error"), wxOK | wxICON_EXCLAMATION);
		return;
	}

	SetStatusText(wxT("Running ebook2cw..."));

	/* Assemble parameters from HashMap */
	ParamH::iterator it;
	for (it = h.begin(); it != h.end(); ++it) {
		wxString param = it->first, value = it->second;
		/* params without values */
		if (	param == wxT("O") or param == wxT("n") or
			param == wxT("p") or param == wxT("X") or
			param == wxT("u")) {
			command += wxT("-") + param + wxT(" ");
		}
		/* Disabled commands / value 0*/
		else if (value == wxT("0") and
		(param == wxT("e") or param == wxT("Q") or
		 param == wxT("l") or param == wxT("d"))
				) {
			/* skip completely */
		}
		else {
			if (value != wxT(""))
			command += wxT("-") + param + wxT("\"") + value + wxT("\" ");
		}
	}
	
	command += AddParam + wxT(" \"") + InFilename + wxT("\"");

	wxString oldcwd = wxGetCwd();
	wxSetWorkingDirectory(OutDir);

#ifdef __WXMSW__
	if (wxFileExists(oldcwd + wxT("\\ebook2cw.exe"))) {	/* current dir */
		command = wxT("\"") + oldcwd + wxT("\\ebook2cw.exe\" ") + command;
	}
	else {
		command = wxT("ebook2cw.exe ") + command;	/* in PATH */
	}
	wxExecute(command);
#else
	if (wxFileExists(oldcwd + wxT("/ebook2cw"))) {			/* Current dir */
		command = oldcwd + wxT("/ebook2cw ") + command;
	}
	else {							/* ebook2cw in PATH */
		command = wxT("ebook2cw ") + command;
	}
	wxShell(command);	
#endif

	wxSetWorkingDirectory(oldcwd);
}


void Ebook2cw::OnWpmChange (wxSpinEvent & event) {
	h[wxT("w")].Printf(wxT("%d"), event.GetPosition());
}

void Ebook2cw::OnWpmeChange (wxSpinEvent & event) {
	h[wxT("e")].Printf(wxT("%d"), event.GetPosition());
}


void Ebook2cw::OnEwsChange (wxSpinEvent & event) { 
	h[wxT("W")].Printf(wxT("%d"), event.GetPosition());
}

void Ebook2cw::OnQrqChange (wxSpinEvent & event) { 
	h[wxT("Q")].Printf(wxT("%d"), event.GetPosition());
}

void Ebook2cw::OnToneChange (wxSpinEvent & event) {
	h[wxT("f")].Printf(wxT("%d"), event.GetPosition());
}

void Ebook2cw::OnWaveChange (wxCommandEvent & event) { 
	h[wxT("T")] = event.GetString().Upper(); 
}


void Ebook2cw::OnOutfileChange(wxCommandEvent & event) {
	h[wxT("o")] = event.GetString();
}

void Ebook2cw::OnAuthorChange(wxCommandEvent & event) { 
	h[wxT("a")] = event.GetString(); 
}

void Ebook2cw::OnTitleChange(wxCommandEvent & event) {
	h[wxT("t")] = event.GetString(); 
}

void Ebook2cw::OnCommentChange(wxCommandEvent & event) {
	h[wxT("k")] = event.GetString(); 
}

void Ebook2cw::OnLimitWordsChange (wxSpinEvent & event) {
		h[wxT("l")].Printf(wxT("%d"), event.GetPosition());
}

void Ebook2cw::OnLimitSecondsChange (wxSpinEvent & event) {
		h[wxT("d")].Printf(wxT("%d"), event.GetPosition());
}


void Ebook2cw::OnYearChange(wxCommandEvent & event) {
	wxString tmp = event.GetString(); 
	wxString tmp1;
	long tmp2;

	tmp = tmp.Left(4);
	tmp.ToLong(&tmp2);
	tmp1.Printf(wxT("%d"), tmp2);

	if (tmp1 == tmp) {
		h[wxT("y")] = event.GetString(); 
	}
	else {
		SetStatusText(wxT("Year must be a number."));
	}
}

void Ebook2cw::OnFormatChange (wxCommandEvent & event) {
	
	if (event.GetString() == wxT("OGG")) 
		h[wxT("O")] = wxT("");
	else
		h.erase(wxT("O"));
}

void Ebook2cw::OnResetQrqChange (wxCommandEvent & event) { 
	if (event.IsChecked()) 
		h.erase(wxT("n"));
	else
		h[wxT("n")] = wxT("");
}

void Ebook2cw::OnNoBTChange (wxCommandEvent & event) {
	if (event.IsChecked()) 
		h[wxT("p")] = wxT("");
	else
		h.erase(wxT("p"));
}

void Ebook2cw::OnAddParamChange (wxCommandEvent & event) {
	AddParam = event.GetString(); 
}

void Ebook2cw::ReadConfigFile () {
	wxString line, param, value;
	wxString cfile = FindConfigFile();

	if (!wxFileExists(cfile)) {
		SetStatusText(wxT("ebook2cw.conf not found; using default values"));
		return;
	}

	wxTextFile file(cfile);
	file.Open(wxConvISO8859_1);

	(void) file.GetFirstLine();
	while (!file.Eof()) {
		line = file.GetNextLine();
		if (line.Mid(1,1) == wxT("=")) {
			param = line.BeforeFirst('=');
			value = line.AfterFirst('=');
			/* parameters which should have no value */
			if (	param == wxT("O") or 
				param == wxT("n") or
				param == wxT("p") or
				param == wxT("X") or
				param == wxT("u")) {
				if (value == wxT("1")) {	
					value = wxT("");
				}
				else {
					continue;	/* skip completely */
				}
			}
			h[param] = value;
		}
	}

	file.Close();
	SetStatusText(wxT("Read ") + cfile);

}


void Ebook2cw::SaveConfigFile(wxCommandEvent & event) {
	wxString line, param, value;
	bool mp = false;
	wxArrayString mappings;

	wxString cfile = FindConfigFile();
	wxTextFile file;

	if (wxFileExists(cfile)) {
		file.Open(cfile);

		/* We overwrite the whole [settings] part but [mappings]
		 * must be saved */
		file.GetFirstLine(); /* throw away */
		while (!file.Eof()) {
			line = file.GetNextLine();
			if (line.Mid(0,10) == wxT("[mappings]")) 
				mp = true;
			if (mp == true)
				mappings.Add(line);
		}

		file.Clear();		
	}
	else {
		file.Create(cfile);
	}

	file.AddLine(wxT("# ebook2cw config written by ebook2cw-gui - http://fkurz.net/ham/ebook2cw.html"));
	file.AddLine(wxT("[settings]"));


	ParamH::iterator it;
	for (it = h.begin(); it != h.end(); ++it) {
		wxString param = it->first, value = it->second;
		/* params without values */
		if (	param == wxT("O") or param == wxT("n") or
			param == wxT("p") or param == wxT("X") or
			param == wxT("u")) {
			file.AddLine(param + wxT("=1"));
		}
		/* Disabled commands / value 0*/
		else if (value == wxT("0") and
				(param == wxT("e") or param == wxT("Q"))
				) {
			/* skip completely */
		}
		else {
			if (value != wxT(""))
			file.AddLine(param + wxT("=") + value);
		}
	}

	/* rewrite old mappings */
	if (mp == true) 
		for (size_t i = 0; i < mappings.Count()-1; i++)
			file.AddLine(mappings[i]);

	file.Write();
	file.Close();
	SetStatusText(wxT("Saved ")+ cfile);

}

void Ebook2cw::OnWebsiteLinkHover (wxMouseEvent & event) {
	SetStatusText(wxT("http://fkurz.net/ham/ebook2cw.html"));
}


/* Return location of the config file. */
wxString Ebook2cw::FindConfigFile () {

	/* cwd always preferred */
	if (wxFileExists(wxT("ebook2cw.conf"))) {
		return wxT("ebook2cw.conf");
	}

	/* Otherwise where it "should" be; create if not there */

	wxString dir;
	wxStandardPaths stdPaths;
	dir = stdPaths.GetUserConfigDir();

#ifdef __WXMSW__
	if (!wxDirExists(dir + wxT("\\ebook2cw"))) {
		wxMkdir(dir + wxT("\\ebook2cw"));
	}
	/* if the file itself doesn't exist, it will be created later */
	return dir + wxT("\\ebook2cw\\ebook2cw.conf");
#endif

#ifdef __UNIX__
	if (!wxDirExists(dir + wxT("/.ebook2cw"))) {
		wxMkdir(dir + wxT("/.ebook2cw"));
	}
	return dir + wxT("/.ebook2cw/ebook2cw.conf");
#endif

	
}


void Ebook2cw::FindExecutable () {
	long i;
	wxArrayString foo;

#ifdef __WXMSW__
	if (wxFileExists(wxGetCwd() + wxT("\\ebook2cw.exe"))) {	/* current dir */
		Ebook2cwCmd = wxT("\"") + wxGetCwd() + wxT("\\ebook2cw.exe\" ");
	}
	else {
		Ebook2cwCmd = wxT("ebook2cw.exe");		/* in PATH */
	}
#else
	if (wxFileExists(wxGetCwd() + wxT("/ebook2cw"))) {	/* current dir */
		Ebook2cwCmd =  wxGetCwd() + wxT("/ebook2cw ");
	}
	else {							/* ebook2cw in PATH */
		Ebook2cwCmd = wxT("ebook2cw");
	}
#endif

	i = wxExecute(Ebook2cwCmd + wxT(" -h"), foo, wxEXEC_SYNC);
	if (i) {
		wxMessageBox(wxT("ebook2cw executable not found. Please make sure it is either in the same directory as ebook2cwgui, or somewhere in the executable PATH."), wxT("Warning"), wxOK | wxICON_EXCLAMATION);
		return;
	}

	/* Extract version information and warn on older version than 0.8.2 */
	long int x, y, z;
	foo.Item(0).Mid(9,1).ToLong(&x);
	foo.Item(0).Mid(11,1).ToLong(&y);
	foo.Item(0).Mid(13,1).ToLong(&z);
	wxString v = foo.Item(0).Mid(9, 5);
	wxString recommended;
	recommended.Printf(wxT("%d.%d.%d"), MINE2CVERSIONA, MINE2CVERSIONB, MINE2CVERSIONC);

	if ((100*x+10*y+z) < (MINE2CVERSIONA*100+MINE2CVERSIONB*10+MINE2CVERSIONC)) {
		wxMessageBox(wxT("ebook2cw version (") + v + wxT(") is outdated; some functions may not work. Consider to download a new ebook2cw version (") + recommended+  wxT(" or later)."), wxT("Warning"), wxOK | wxICON_EXCLAMATION);
	}

}

/* IsPlaintext: returns false if the file selected appears not to be a plain
 * text file, e.g. a MS Word document */

wxString Ebook2cw::IsPlaintext(wxString &s) {
	wxFile *f = new wxFile(s.c_str(), wxFile::read);
	char buf[256];

	memset(buf, 0, 256);

	if (!f->IsOpened()) {
		return wxString(wxT("non existent"));	/* shud not happen! */
	}

	/* get first few bytes and test for common magic numbers */

	if (f->Read(buf, 10) != 10) 
		return wxString(wxT("yes")); /* so short? whatever... */

	f->Close();
	delete f;

	if (strncmp(buf, "\xd0\xcf\x11\xe0" , 4) == 0) 
		return wxString(wxT("MS Office"));
	if (strncmp(buf, "%PDF-" , 5) == 0) 
		return wxString(wxT("PDF"));

	return wxString(wxT("yes"));

}


void Ebook2cw::ShowAbout (wxCommandEvent & WXUNUSED(event)) {
       About *abt = new About(wxT("About ebook2cw"));
       abt->Show(true);
       return;
}


