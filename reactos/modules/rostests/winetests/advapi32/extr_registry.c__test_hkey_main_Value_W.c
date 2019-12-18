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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int ERROR_CALL_NOT_IMPLEMENTED ; 
 int ERROR_SUCCESS ; 
 int GLE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int REG_SZ ; 
 int RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  hkey_main ; 
 int /*<<< orphan*/  lok (int,char*,int,...) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_wn (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void _test_hkey_main_Value_W(int line, LPCWSTR name, LPCWSTR string,
                                   DWORD full_byte_len)
{
    DWORD ret, type, cbData;
    BYTE* value;

    type=0xdeadbeef;
    cbData=0xdeadbeef;
    /* When successful RegQueryValueExW() leaves GLE as is,
     * so we must reset it to detect unimplemented functions.
     */
    SetLastError(0xdeadbeef);
    ret = RegQueryValueExW(hkey_main, name, NULL, &type, NULL, &cbData);
    GLE = GetLastError();
    lok(ret == ERROR_SUCCESS, "RegQueryValueExW/1 failed: %d, GLE=%d\n", ret, GLE);
    if(GLE == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("RegQueryValueExW() is not implemented\n");
        return;
    }

    lok(type == REG_SZ, "RegQueryValueExW/1 returned type %d\n", type);
    lok(cbData == full_byte_len,
        "cbData=%d instead of %d\n", cbData, full_byte_len);

    /* Give enough space to overflow by one WCHAR */
    value = HeapAlloc(GetProcessHeap(), 0, cbData+2);
    memset(value, 0xbd, cbData+2);
    type=0xdeadbeef;
    ret = RegQueryValueExW(hkey_main, name, NULL, &type, value, &cbData);
    GLE = GetLastError();
    lok(ret == ERROR_SUCCESS, "RegQueryValueExW/2 failed: %d, GLE=%d\n", ret, GLE);
    if (string)
    {
        lok(memcmp(value, string, cbData) == 0, "RegQueryValueExW failed: %s/%d != %s/%d\n",
           wine_dbgstr_wn((WCHAR*)value, cbData / sizeof(WCHAR)), cbData,
           wine_dbgstr_wn(string, full_byte_len / sizeof(WCHAR)), full_byte_len);
    }
    /* This implies that when cbData == 0, RegQueryValueExW() should not modify the buffer */
    lok(*(value+cbData) == 0xbd, "RegQueryValueExW/2 overflowed at %u: %02x != bd\n", cbData, *(value+cbData));
    lok(*(value+cbData+1) == 0xbd, "RegQueryValueExW/2 overflowed at %u+1: %02x != bd\n", cbData, *(value+cbData+1));
    HeapFree(GetProcessHeap(), 0, value);
}