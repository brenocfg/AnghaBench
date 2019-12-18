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
typedef  char const WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 scalar_t__ DeleteFileA (char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char const*,int) ; 
 int /*<<< orphan*/  lok (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_reg_exe (char*,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ write_file (char const*,int) ; 

__attribute__((used)) static BOOL import_reg(unsigned line, const char *contents, BOOL unicode, DWORD *rc)
{
    int lenA;
    BOOL ret;

    lenA = strlen(contents);

    if (unicode)
    {
        int len = MultiByteToWideChar(CP_UTF8, 0, contents, lenA, NULL, 0);
        int size = len * sizeof(WCHAR);
        WCHAR *wstr = HeapAlloc(GetProcessHeap(), 0, size);
        if (!wstr) return FALSE;
        MultiByteToWideChar(CP_UTF8, 0, contents, lenA, wstr, len);

        ret = write_file(wstr, size);
        HeapFree(GetProcessHeap(), 0, wstr);
    }
    else
        ret = write_file(contents, lenA);

    if (!ret) return FALSE;

    run_reg_exe("reg import test.reg", rc);

    ret = DeleteFileA("test.reg");
    lok(ret, "DeleteFile failed: %u\n", GetLastError());

    return ret;
}