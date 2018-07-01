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
    ID_NewConnection = 1,
    ID_Disconnect,

    SOCKET_ID
};

wxBEGIN_EVENT_TABLE(OncFrame, wxFrame)
  EVT_MENU(ID_NewConnection, OncFrame::OnNewConnection)
  EVT_MENU(wxID_EXIT,  OncFrame::OnExit)
  EVT_MENU(wxID_ABOUT, OncFrame::OnAbout)
  EVT_SOCKET(SOCKET_ID, OncFrame::OnSocketEvent)
  EVT_TEXT_ENTER(-1, OncFrame::OnEntryEnter)
wxEND_EVENT_TABLE()

OncFrame::OncFrame(const wxString& title, const wxPoint& pos,
  const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size),
  m_socket(NULL)
{
  // Create file menu.
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(ID_NewConnection, "&New Connection...\tCtrl-H",
    "Make a new chat connection");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);

  // Create help menu.
  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");
  SetMenuBar(menuBar);

  CreateStatusBar();
  SetStatusText("Create a new connection to get started!");

  wxPanel *panel = new wxPanel(this, wxID_ANY);

  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

  m_text = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition,
      wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);

  vbox->Add(m_text, 1, wxEXPAND, 1);

  m_entry = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition,
      wxDefaultSize, wxTE_PROCESS_ENTER);

  vbox->Add(m_entry, 0, wxEXPAND, 1);
  panel->SetSizer(vbox);

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

void OncFrame::OnEntryEnter(wxCommandEvent& event)
{
  if (m_socket == NULL) {
    wxLogMessage("Make a connection first!");
  }

  wxString line = m_entry->GetValue();
  line.append("\n");
  wxCharBuffer buf = line.mb_str(wxConvUTF8);

  m_socket->Write(buf.data(), strlen(buf.data()) + 1);

  m_entry->Clear();
}

void OncFrame::OnNewConnection(wxCommandEvent& event)
{

  wxIPV4address addr;
  addr.Hostname("mikekohn.net");
  addr.Service(6666);

  m_socket = new wxSocketClient();

  // Setup the event handler and subscribe to most events.
  m_socket->SetEventHandler(*this, SOCKET_ID);
  m_socket->SetNotify(wxSOCKET_CONNECTION_FLAG | wxSOCKET_INPUT_FLAG |
      wxSOCKET_LOST_FLAG);
  m_socket->Notify(true);

  // Fire connect
  m_socket->Connect(addr, false);
}

void OncFrame::OnSocketEvent(wxSocketEvent& event)
{
  // The socket that had the event
  wxSocketBase* sock = event.GetSocket();

  // Common buffer shared by the events
  char buf[2048];

  switch(event.GetSocketEvent()) {
  case wxSOCKET_CONNECTION:
  {
    m_text->AppendText(_("\nConnected to server.\n"));

#if 0
    // Fill the arry with the numbers 0 through 9 as characters
    char mychar = '0';
    for (int i = 0; i < 10; i++) {
      buf[i] = mychar++;
    }
    // Send the characters to the server
    sock->Write(buf, sizeof(buf));
    m_text->AppendText(_("Wrote string to server.\n"));
#endif

    break;
  }
  case wxSOCKET_INPUT:
  {
    sock->Read(buf, sizeof(buf));
    wxUint32 sz = sock->LastReadCount();
    buf[sz] = '\0';

    m_text->AppendText(buf);
//    m_text->AppendText("\n");

    break;
  }

  // The server hangs up after sending the data
  case wxSOCKET_LOST:
  {
    sock->Destroy();

    m_text->AppendText(_("Connection lost.\n"));

    break;
  }
  }
}

