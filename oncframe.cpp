/*
 * Copyright (c) 2017 Devin Smith <devin@devinsmith.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <oncframe.h>

enum
{
    ID_NewConnection = 1
};

wxBEGIN_EVENT_TABLE(OncFrame, wxFrame)
  EVT_MENU(ID_NewConnection, OncFrame::OnNewConnection)
  EVT_MENU(wxID_EXIT,  OncFrame::OnExit)
  EVT_MENU(wxID_ABOUT, OncFrame::OnAbout)
wxEND_EVENT_TABLE()

OncFrame::OncFrame(const wxString& title, const wxPoint& pos,
  const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_NewConnection, "&New Connection...\tCtrl-H",
      "Make a new chat connection");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Create a new connection to get started!");
}

void OncFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void OncFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("onc2 - Chat Client",
      "About onc2", wxOK | wxICON_INFORMATION);
}

void OncFrame::OnNewConnection(wxCommandEvent& event)
{
    wxLogMessage("New connection, not yet implemented!");
}

