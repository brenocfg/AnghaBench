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
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  cmd_DeletePortW ; 
 int /*<<< orphan*/  hXcv ; 
 int lstrlenW (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pXcvDataPort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ tempfileW ; 

__attribute__((used)) static void test_XcvDataPort_DeletePort(void)
{
    DWORD   res;
    DWORD   needed;


    /* cleanup: just to make sure */
    needed = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_DeletePortW, (PBYTE) tempfileW, (lstrlenW(tempfileW) + 1) * sizeof(WCHAR), NULL, 0, &needed);
    ok( !res  || (res == ERROR_FILE_NOT_FOUND),
        "returned %d with %u (expected ERROR_SUCCESS or ERROR_FILE_NOT_FOUND)\n",
        res, GetLastError());


    /* ToDo: cmd_AddPortW for tempfileW, then cmd_DeletePortW for the existing Port */


    /* try to delete a nonexistent Port */
    needed = (DWORD) 0xdeadbeef;
    SetLastError(0xdeadbeef);
    res = pXcvDataPort(hXcv, cmd_DeletePortW, (PBYTE) tempfileW, (lstrlenW(tempfileW) + 1) * sizeof(WCHAR), NULL, 0, &needed);
    ok( res == ERROR_FILE_NOT_FOUND,
        "returned %d with %u (expected ERROR_FILE_NOT_FOUND)\n", res, GetLastError());

    /* emptyW as Portname: ERROR_FILE_NOT_FOUND is returned */
    /* NULL as Portname: Native localspl.dll crashed */

}