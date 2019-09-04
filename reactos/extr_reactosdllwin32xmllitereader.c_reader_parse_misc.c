#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int resumestate; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ S_FALSE ; 
#define  XmlReadResumeState_Comment 131 
 int XmlReadResumeState_Initial ; 
#define  XmlReadResumeState_PIBody 130 
#define  XmlReadResumeState_PITarget 129 
#define  XmlReadResumeState_Whitespace 128 
 int /*<<< orphan*/  commentW ; 
 scalar_t__ is_wchar_space (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  piW ; 
 int /*<<< orphan*/  reader_cmp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reader_get_ptr (TYPE_1__*) ; 
 scalar_t__ reader_more (TYPE_1__*) ; 
 scalar_t__ reader_parse_comment (TYPE_1__*) ; 
 scalar_t__ reader_parse_pi (TYPE_1__*) ; 
 scalar_t__ reader_parse_whitespace (TYPE_1__*) ; 

__attribute__((used)) static HRESULT reader_parse_misc(xmlreader *reader)
{
    HRESULT hr = S_FALSE;

    if (reader->resumestate != XmlReadResumeState_Initial)
    {
        hr = reader_more(reader);
        if (FAILED(hr)) return hr;

        /* finish current node */
        switch (reader->resumestate)
        {
        case XmlReadResumeState_PITarget:
        case XmlReadResumeState_PIBody:
            return reader_parse_pi(reader);
        case XmlReadResumeState_Comment:
            return reader_parse_comment(reader);
        case XmlReadResumeState_Whitespace:
            return reader_parse_whitespace(reader);
        default:
            ERR("unknown resume state %d\n", reader->resumestate);
        }
    }

    while (1)
    {
        const WCHAR *cur = reader_get_ptr(reader);

        if (is_wchar_space(*cur))
            hr = reader_parse_whitespace(reader);
        else if (!reader_cmp(reader, commentW))
            hr = reader_parse_comment(reader);
        else if (!reader_cmp(reader, piW))
            hr = reader_parse_pi(reader);
        else
            break;

        if (hr != S_FALSE) return hr;
    }

    return hr;
}