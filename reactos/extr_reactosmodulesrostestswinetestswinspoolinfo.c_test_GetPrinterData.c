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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 int ClosePrinter (int /*<<< orphan*/ ) ; 
 int ERROR_MORE_DATA ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetPrinterDataA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int,int*) ; 
 int MAX_PATH ; 
 int OpenPrinterA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int REG_SZ ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  defaultspooldirectory ; 
 int lstrlenA (scalar_t__*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  on_win9x ; 
 int /*<<< orphan*/  win_skip (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_GetPrinterData(void)
{
    HANDLE hprn = 0;
    DWORD res;
    DWORD type;
    CHAR  buffer[MAX_PATH + 1];
    DWORD needed;
    DWORD len;

    /* ToDo: test parameter validation, test with the default printer */

    SetLastError(0xdeadbeef);
    res = OpenPrinterA(NULL, &hprn, NULL);
    if (!res)
    {
        /* printserver not available on win9x */
        if (!on_win9x)
            win_skip("Unable to open the printserver: %d\n", GetLastError());
        return;
    }

    memset(buffer, '#', sizeof(buffer));
    buffer[MAX_PATH] = 0;
    type = 0xdeadbeef;
    needed = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = GetPrinterDataA(hprn, defaultspooldirectory, &type, (LPBYTE) buffer, sizeof(buffer), &needed);

    len = lstrlenA(buffer) + sizeof(CHAR);
    /* NT4 and w2k require a buffer to save the UNICODE result also for the ANSI function */
    ok( !res && (type == REG_SZ) && ((needed == len) || (needed == (len * sizeof(WCHAR)))),
        "got %d, type %d, needed: %d and '%s' (expected ERROR_SUCCESS, REG_SZ and %d)\n",
        res, type, needed, buffer, len);

    needed = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = GetPrinterDataA(hprn, defaultspooldirectory, NULL, NULL, 0, &needed);
    ok( (res == ERROR_MORE_DATA) && ((needed == len) || (needed == (len * sizeof(WCHAR)))),
        "got %d, needed: %d (expected ERROR_MORE_DATA and %d)\n", res, needed, len);

    /* ToDo: test SPLREG_*  */

    SetLastError(0xdeadbeef);
    res = ClosePrinter(hprn);
    ok(res, "ClosePrinter error %d\n", GetLastError());
}