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
 int /*<<< orphan*/  WC_E_DIGIT ; 
 int /*<<< orphan*/  WC_E_XMLDECL ; 
 int /*<<< orphan*/  debug_strval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ reader_cmp (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ reader_get_cur (int /*<<< orphan*/ *) ; 
 char* reader_get_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_init_strvalue (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_skipn (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT reader_parse_versionnum(xmlreader *reader, strval *val)
{
    static const WCHAR onedotW[] = {'1','.',0};
    WCHAR *ptr, *ptr2;
    UINT start;

    if (reader_cmp(reader, onedotW)) return WC_E_XMLDECL;

    start = reader_get_cur(reader);
    /* skip "1." */
    reader_skipn(reader, 2);

    ptr2 = ptr = reader_get_ptr(reader);
    while (*ptr >= '0' && *ptr <= '9')
    {
        reader_skipn(reader, 1);
        ptr = reader_get_ptr(reader);
    }

    if (ptr2 == ptr) return WC_E_DIGIT;
    reader_init_strvalue(start, reader_get_cur(reader)-start, val);
    TRACE("version=%s\n", debug_strval(reader, val));
    return S_OK;
}