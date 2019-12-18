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
 int MAX_PATH ; 
 int OpenPrinterA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int REG_SZ ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  defaultspooldirectory ; 
 char* does_not_exist ; 
 int lstrlenA (scalar_t__*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pGetPrinterDataExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  win_skip (char*,...) ; 

__attribute__((used)) static void test_GetPrinterDataEx(void)
{
    HANDLE hprn = 0;
    DWORD res;
    DWORD type;
    CHAR  buffer[MAX_PATH + 1];
    DWORD needed;
    DWORD len;

    /* not present before w2k */
    if (!pGetPrinterDataExA) {
        win_skip("GetPrinterDataEx not found\n");
        return;
    }

    /* ToDo: test parameter validation, test with the default printer */

    SetLastError(0xdeadbeef);
    res = OpenPrinterA(NULL, &hprn, NULL);
    if (!res)
    {
        win_skip("Unable to open the printserver: %d\n", GetLastError());
        return;
    }

    /* keyname is ignored, when hprn is a HANDLE for a printserver */
    memset(buffer, '#', sizeof(buffer));
    buffer[MAX_PATH] = 0;
    type = 0xdeadbeef;
    needed = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pGetPrinterDataExA(hprn, NULL, defaultspooldirectory, &type,
                             (LPBYTE) buffer, sizeof(buffer), &needed);

    len = lstrlenA(buffer) + sizeof(CHAR);
    /* NT4 and w2k require a buffer to save the UNICODE result also for the ANSI function */
    ok( !res && (type == REG_SZ) && ((needed == len) || (needed == (len * sizeof(WCHAR)))),
        "got %d, type %d, needed: %d and '%s' (expected ERROR_SUCCESS, REG_SZ and %d)\n",
        res, type, needed, buffer, len);

    memset(buffer, '#', sizeof(buffer));
    buffer[MAX_PATH] = 0;
    type = 0xdeadbeef;
    needed = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pGetPrinterDataExA(hprn, "", defaultspooldirectory, &type,
                             (LPBYTE) buffer, sizeof(buffer), &needed);
    len = lstrlenA(buffer) + sizeof(CHAR);
    ok( !res && (type == REG_SZ) && ((needed == len) || (needed == (len * sizeof(WCHAR)))),
        "got %d, type %d, needed: %d and '%s' (expected ERROR_SUCCESS, REG_SZ and %d)\n",
        res, type, needed, buffer, len);

    memset(buffer, '#', sizeof(buffer));
    buffer[MAX_PATH] = 0;
    type = 0xdeadbeef;
    needed = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    /* Wine uses GetPrinterDataEx with "PrinterDriverData" to implement GetPrinterData */
    res = pGetPrinterDataExA(hprn, "PrinterDriverData", defaultspooldirectory,
                             &type, (LPBYTE) buffer, sizeof(buffer), &needed);
    len = lstrlenA(buffer) + sizeof(CHAR);
    ok( !res && (type == REG_SZ) && ((needed == len) || (needed == (len * sizeof(WCHAR)))),
        "got %d, type %d, needed: %d and '%s' (expected ERROR_SUCCESS, REG_SZ and %d)\n",
        res, type, needed, buffer, len);


    memset(buffer, '#', sizeof(buffer));
    buffer[MAX_PATH] = 0;
    type = 0xdeadbeef;
    needed = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pGetPrinterDataExA(hprn, does_not_exist, defaultspooldirectory, &type,
                             (LPBYTE) buffer, sizeof(buffer), &needed);
    len = lstrlenA(buffer) + sizeof(CHAR);
    ok( !res && (type == REG_SZ) && ((needed == len) || (needed == (len * sizeof(WCHAR)))),
        "got %d, type %d, needed: %d and '%s' (expected ERROR_SUCCESS, REG_SZ and %d)\n",
        res, type, needed, buffer, len);

    needed = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    /* vista and w2k8 have a bug in GetPrinterDataEx:
       the current LastError value is returned as result */
    res = pGetPrinterDataExA(hprn, NULL, defaultspooldirectory, NULL, NULL, 0, &needed);
    ok( ((res == ERROR_MORE_DATA) || broken(res == 0xdeadbeef)) &&
        ((needed == len) || (needed == (len * sizeof(WCHAR)))),
        "got %d, needed: %d (expected ERROR_MORE_DATA and %d)\n", res, needed, len);

    needed = 0xdeadbeef;
    SetLastError(0xdeaddead);
    res = pGetPrinterDataExA(hprn, NULL, defaultspooldirectory, NULL, NULL, 0, &needed);
    ok( ((res == ERROR_MORE_DATA) || broken(res == 0xdeaddead)) &&
        ((needed == len) || (needed == (len * sizeof(WCHAR)))),
        "got %d, needed: %d (expected ERROR_MORE_DATA and %d)\n", res, needed, len);

    SetLastError(0xdeadbeef);
    res = ClosePrinter(hprn);
    ok(res, "ClosePrinter error %d\n", GetLastError());
}