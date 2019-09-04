#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xmlreader ;
typedef  int /*<<< orphan*/  strval ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WC_E_QUOTE ; 
 int /*<<< orphan*/  debug_strval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_char (char) ; 
 scalar_t__ reader_get_cur (int /*<<< orphan*/ *) ; 
 char* reader_get_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_init_strvalue (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_skipn (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT reader_parse_sys_literal(xmlreader *reader, strval *literal)
{
    WCHAR *cur = reader_get_ptr(reader), quote;
    UINT start;

    if (*cur != '"' && *cur != '\'') return WC_E_QUOTE;

    quote = *cur;
    reader_skipn(reader, 1);

    cur = reader_get_ptr(reader);
    start = reader_get_cur(reader);
    while (is_char(*cur) && *cur != quote)
    {
        reader_skipn(reader, 1);
        cur = reader_get_ptr(reader);
    }
    reader_init_strvalue(start, reader_get_cur(reader)-start, literal);
    if (*cur == quote) reader_skipn(reader, 1);

    TRACE("%s\n", debug_strval(reader, literal));
    return S_OK;
}