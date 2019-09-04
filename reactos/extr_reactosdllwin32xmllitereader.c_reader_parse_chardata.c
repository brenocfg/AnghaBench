#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct reader_position {int dummy; } ;
struct TYPE_11__ {struct reader_position position; } ;
struct TYPE_12__ {scalar_t__ resumestate; void* nodetype; scalar_t__* resume; TYPE_1__ empty_element; struct reader_position position; } ;
typedef  TYPE_2__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringValue_Value ; 
 int /*<<< orphan*/  WC_E_CDSECTEND ; 
 void* XmlNodeType_Text ; 
 void* XmlNodeType_Whitespace ; 
 scalar_t__ XmlReadResumeState_CharData ; 
 scalar_t__ XmlReadResumeState_Initial ; 
 size_t XmlReadResume_Body ; 
 scalar_t__ is_wchar_space (char) ; 
 int /*<<< orphan*/  reader_cmp (TYPE_2__*,char const*) ; 
 scalar_t__ reader_get_cur (TYPE_2__*) ; 
 char* reader_get_ptr (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_init_strvalue (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_parse_reference (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_set_strvalue (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_shrink (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_skipn (TYPE_2__*,int) ; 

__attribute__((used)) static HRESULT reader_parse_chardata(xmlreader *reader)
{
    struct reader_position position;
    WCHAR *ptr;
    UINT start;

    if (reader->resumestate == XmlReadResumeState_CharData)
    {
        start = reader->resume[XmlReadResume_Body];
        ptr = reader_get_ptr(reader);
    }
    else
    {
        reader_shrink(reader);
        ptr = reader_get_ptr(reader);
        start = reader_get_cur(reader);
        /* There's no text */
        if (!*ptr || *ptr == '<') return S_OK;
        reader->nodetype = is_wchar_space(*ptr) ? XmlNodeType_Whitespace : XmlNodeType_Text;
        reader->resume[XmlReadResume_Body] = start;
        reader->resumestate = XmlReadResumeState_CharData;
        reader_set_strvalue(reader, StringValue_Value, NULL);
    }

    position = reader->position;
    while (*ptr)
    {
        static const WCHAR ampW[] = {'&',0};

        /* CDATA closing sequence ']]>' is not allowed */
        if (ptr[0] == ']' && ptr[1] == ']' && ptr[2] == '>')
            return WC_E_CDSECTEND;

        /* Found next markup part */
        if (ptr[0] == '<')
        {
            strval value;

            reader->empty_element.position = position;
            reader_init_strvalue(start, reader_get_cur(reader)-start, &value);
            reader_set_strvalue(reader, StringValue_Value, &value);
            reader->resume[XmlReadResume_Body] = 0;
            reader->resumestate = XmlReadResumeState_Initial;
            return S_OK;
        }

        /* this covers a case when text has leading whitespace chars */
        if (!is_wchar_space(*ptr)) reader->nodetype = XmlNodeType_Text;

        if (!reader_cmp(reader, ampW))
            reader_parse_reference(reader);
        else
            reader_skipn(reader, 1);

        ptr = reader_get_ptr(reader);
    }

    return S_OK;
}