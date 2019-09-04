#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int resumestate; scalar_t__* resume; int /*<<< orphan*/  nodetype; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringValue_LocalName ; 
 int /*<<< orphan*/  StringValue_QualifiedName ; 
 int /*<<< orphan*/  StringValue_Value ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmlNodeType_ProcessingInstruction ; 
#define  XmlReadResumeState_Initial 129 
 int XmlReadResumeState_PIBody ; 
#define  XmlReadResumeState_PITarget 128 
 size_t XmlReadResume_Body ; 
 int /*<<< orphan*/  debug_strval (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_wchar_space (char) ; 
 void* reader_get_cur (TYPE_1__*) ; 
 char* reader_get_ptr (TYPE_1__*) ; 
 char* reader_get_ptr2 (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  reader_init_strvalue (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_parse_pitarget (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_set_strvalue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_shrink (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_skipn (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strval_empty ; 

__attribute__((used)) static HRESULT reader_parse_pi(xmlreader *reader)
{
    strval target;
    WCHAR *ptr;
    UINT start;
    HRESULT hr;

    switch (reader->resumestate)
    {
    case XmlReadResumeState_Initial:
        /* skip '<?' */
        reader_skipn(reader, 2);
        reader_shrink(reader);
        reader->resumestate = XmlReadResumeState_PITarget;
    case XmlReadResumeState_PITarget:
        hr = reader_parse_pitarget(reader, &target);
        if (FAILED(hr)) return hr;
        reader_set_strvalue(reader, StringValue_LocalName, &target);
        reader_set_strvalue(reader, StringValue_QualifiedName, &target);
        reader_set_strvalue(reader, StringValue_Value, &strval_empty);
        reader->resumestate = XmlReadResumeState_PIBody;
        reader->resume[XmlReadResume_Body] = reader_get_cur(reader);
    default:
        ;
    }

    start = reader->resume[XmlReadResume_Body];
    ptr = reader_get_ptr(reader);
    while (*ptr)
    {
        if (ptr[0] == '?')
        {
            if (ptr[1] == '>')
            {
                UINT cur = reader_get_cur(reader);
                strval value;

                /* strip all leading whitespace chars */
                while (start < cur)
                {
                    ptr = reader_get_ptr2(reader, start);
                    if (!is_wchar_space(*ptr)) break;
                    start++;
                }

                reader_init_strvalue(start, cur-start, &value);

                /* skip '?>' */
                reader_skipn(reader, 2);
                TRACE("%s\n", debug_strval(reader, &value));
                reader->nodetype = XmlNodeType_ProcessingInstruction;
                reader->resumestate = XmlReadResumeState_Initial;
                reader->resume[XmlReadResume_Body] = 0;
                reader_set_strvalue(reader, StringValue_Value, &value);
                return S_OK;
            }
        }

        reader_skipn(reader, 1);
        ptr = reader_get_ptr(reader);
    }

    return S_OK;
}