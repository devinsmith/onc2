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

#ifndef __ONC_FRAME_H__
#define __ONC_FRAME_H__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/socket.h>
#endif

class OncFrame: public wxFrame {
public:
    OncFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    wxTextCtrl *m_text;
    wxTextCtrl *m_entry;
    wxSocketClient *m_socket;

    void OnAbout(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnNewConnection(wxCommandEvent& event);

    void OnEntryEnter(wxCommandEvent& event);

    void OnSocketEvent(wxSocketEvent& event);
    wxDECLARE_EVENT_TABLE();
};

#endif /* __ONC_FRAME_H__ */
