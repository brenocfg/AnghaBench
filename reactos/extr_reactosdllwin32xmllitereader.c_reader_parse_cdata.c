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
struct TYPE_9__ {scalar_t__ resumestate; scalar_t__* resume; int /*<<< orphan*/  nodetype; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringValue_Value ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmlNodeType_CDATA ; 
 scalar_t__ XmlReadResumeState_CDATA ; 
 scalar_t__ XmlReadResumeState_Initial ; 
 size_t XmlReadResume_Body ; 
 int /*<<< orphan*/  debug_strval (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ reader_get_cur (TYPE_1__*) ; 
 char* reader_get_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_init_strvalue (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_set_strvalue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_shrink (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_skipn (TYPE_1__*,int) ; 

__attribute__((used)) static HRESULT reader_parse_cdata(xmlreader *reader)
{
    WCHAR *ptr;
    UINT start;

    if (reader->resumestate == XmlReadResumeState_CDATA)
    {
        start = reader->resume[XmlReadResume_Body];
        ptr = reader_get_ptr(reader);
    }
    else
    {
        /* skip markup '<![CDATA[' */
        reader_skipn(reader, 9);
        reader_shrink(reader);
        ptr = reader_get_ptr(reader);
        start = reader_get_cur(reader);
        reader->nodetype = XmlNodeType_CDATA;
        reader->resume[XmlReadResume_Body] = start;
        reader->resumestate = XmlReadResumeState_CDATA;
        reader_set_strvalue(reader, StringValue_Value, NULL);
    }

    while (*ptr)
    {
        if (*ptr == ']' && *(ptr+1) == ']' && *(ptr+2) == '>')
        {
            strval value;

            reader_init_strvalue(start, reader_get_cur(reader)-start, &value);

            /* skip ']]>' */
            reader_skipn(reader, 3);
            TRACE("%s\n", debug_strval(reader, &value));

            reader_set_strvalue(reader, StringValue_Value, &value);
            reader->resume[XmlReadResume_Body] = 0;
            reader->resumestate = XmlReadResumeState_Initial;
            return S_OK;
        }
        else
        {
            reader_skipn(reader, 1);
            ptr++;
        }
    }

    return S_OK;
}