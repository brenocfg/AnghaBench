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
struct TYPE_9__ {int resumestate; scalar_t__* resume; int /*<<< orphan*/  nodetype; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringValue_LocalName ; 
 int /*<<< orphan*/  StringValue_QualifiedName ; 
 int /*<<< orphan*/  StringValue_Value ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmlNodeType_Whitespace ; 
#define  XmlReadResumeState_Initial 129 
#define  XmlReadResumeState_Whitespace 128 
 size_t XmlReadResume_Body ; 
 int /*<<< orphan*/  debug_strval (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_reader_pending (TYPE_1__*) ; 
 scalar_t__ reader_get_cur (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_init_strvalue (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_set_strvalue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_shrink (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_skipspaces (TYPE_1__*) ; 
 int /*<<< orphan*/  strval_empty ; 

__attribute__((used)) static HRESULT reader_parse_whitespace(xmlreader *reader)
{
    switch (reader->resumestate)
    {
    case XmlReadResumeState_Initial:
        reader_shrink(reader);
        reader->resumestate = XmlReadResumeState_Whitespace;
        reader->resume[XmlReadResume_Body] = reader_get_cur(reader);
        reader->nodetype = XmlNodeType_Whitespace;
        reader_set_strvalue(reader, StringValue_LocalName, &strval_empty);
        reader_set_strvalue(reader, StringValue_QualifiedName, &strval_empty);
        reader_set_strvalue(reader, StringValue_Value, &strval_empty);
        /* fallthrough */
    case XmlReadResumeState_Whitespace:
    {
        strval value;
        UINT start;

        reader_skipspaces(reader);
        if (is_reader_pending(reader)) return S_OK;

        start = reader->resume[XmlReadResume_Body];
        reader_init_strvalue(start, reader_get_cur(reader)-start, &value);
        reader_set_strvalue(reader, StringValue_Value, &value);
        TRACE("%s\n", debug_strval(reader, &value));
        reader->resumestate = XmlReadResumeState_Initial;
    }
    default:
        ;
    }

    return S_OK;
}