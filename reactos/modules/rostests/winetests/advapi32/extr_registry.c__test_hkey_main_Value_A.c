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
typedef  char* LPCSTR ;
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
 int RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  hkey_main ; 
 int /*<<< orphan*/  lok (int,char*,int,...) ; 
 int lstrlenA (char*) ; 
 scalar_t__ memcmp (int*,char*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  wine_debugstr_an (char*,int) ; 

__attribute__((used)) static void _test_hkey_main_Value_A(int line, LPCSTR name, LPCSTR string,
                                   DWORD full_byte_len)
{
    DWORD ret, type, cbData;
    DWORD str_byte_len;
    BYTE* value;

    type=0xdeadbeef;
    cbData=0xdeadbeef;
    /* When successful RegQueryValueExA() leaves GLE as is,
     * so we must reset it to detect unimplemented functions.
     */
    SetLastError(0xdeadbeef);
    ret = RegQueryValueExA(hkey_main, name, NULL, &type, NULL, &cbData);
    GLE = GetLastError();
    lok(ret == ERROR_SUCCESS, "RegQueryValueExA/1 failed: %d, GLE=%d\n", ret, GLE);
    /* It is wrong for the Ansi version to not be implemented */
    ok(GLE == 0xdeadbeef, "RegQueryValueExA set GLE = %u\n", GLE);
    if(GLE == ERROR_CALL_NOT_IMPLEMENTED) return;

    str_byte_len = (string ? lstrlenA(string) : 0) + 1;
    lok(type == REG_SZ, "RegQueryValueExA/1 returned type %d\n", type);
    lok(cbData == full_byte_len, "cbData=%d instead of %d or %d\n", cbData, full_byte_len, str_byte_len);

    value = HeapAlloc(GetProcessHeap(), 0, cbData+1);
    memset(value, 0xbd, cbData+1);
    type=0xdeadbeef;
    ret = RegQueryValueExA(hkey_main, name, NULL, &type, value, &cbData);
    GLE = GetLastError();
    lok(ret == ERROR_SUCCESS, "RegQueryValueExA/2 failed: %d, GLE=%d\n", ret, GLE);
    if (!string)
    {
        /* When cbData == 0, RegQueryValueExA() should not modify the buffer */
        lok(*value == 0xbd, "RegQueryValueExA overflowed: cbData=%u *value=%02x\n", cbData, *value);
    }
    else
    {
        lok(memcmp(value, string, cbData) == 0, "RegQueryValueExA/2 failed: %s/%d != %s/%d\n",
           wine_debugstr_an((char*)value, cbData), cbData,
           wine_debugstr_an(string, full_byte_len), full_byte_len);
        lok(*(value+cbData) == 0xbd, "RegQueryValueExA/2 overflowed at offset %u: %02x != bd\n", cbData, *(value+cbData));
    }
    HeapFree(GetProcessHeap(), 0, value);
}