#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pCC ;
struct TYPE_5__ {int dwSize; } ;
typedef  int DWORD ;
typedef  TYPE_1__ COMMCONFIG ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int ERROR_BADKEY ; 
 int ERROR_CALL_NOT_IMPLEMENTED ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * emptyA ; 
 char* fmt_comA ; 
 int /*<<< orphan*/  ok (int,char*,int,int /*<<< orphan*/ ,...) ; 
 int pCommConfigDialogA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int pGetDefaultCommConfigA (int /*<<< orphan*/ *,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  trace (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void test_drvCommConfigDialogA(void)
{
    COMMCONFIG  pCC[3];
    CHAR        bufferA[16];
    DWORD       i;
    DWORD       res;
    DWORD       len;


    /* test ports "com1" - "com4" */
    for (i = 1; i < 5 ; i++) {
        sprintf(bufferA, fmt_comA, i);
        len = sizeof(pCC);
        ZeroMemory(pCC, sizeof(pCC));
        SetLastError(0xdeadbeef);
        res = pGetDefaultCommConfigA(bufferA, pCC, &len);
        if (res == ERROR_CALL_NOT_IMPLEMENTED) {
            /* NT does not implement the ANSI API */
            win_skip("*A not implemented\n");
            return;
        }

        if (res == ERROR_SUCCESS) {

            if (winetest_interactive) {
                SetLastError(0xdeadbeef);
                res = pCommConfigDialogA(bufferA, NULL, pCC);
                /* OK: ERROR_SUCCESS,  Cancel: ERROR_CANCELLED */
                trace("returned %u with %u for '%s'\n", res, GetLastError(), bufferA);
            }

            ZeroMemory(pCC, sizeof(pCC));
            SetLastError(0xdeadbeef);
            res = pCommConfigDialogA(bufferA, NULL, pCC);
            ok( res == ERROR_INSUFFICIENT_BUFFER,
                "returned %u with %u for '%s' (expected ERROR_INSUFFICIENT_BUFFER)\n",
                res, GetLastError(), bufferA);


            SetLastError(0xdeadbeef);
            res = pCommConfigDialogA(bufferA, NULL, NULL);
            ok( res == ERROR_INVALID_PARAMETER,
                "returned %u with %u for '%s' (expected ERROR_INVALID_PARAMETER)\n",
                res, GetLastError(), bufferA);
        }
    }


    ZeroMemory(pCC, sizeof(pCC));
    SetLastError(0xdeadbeef);
    res = pCommConfigDialogA(emptyA, NULL, pCC);
    ok( res == ERROR_INSUFFICIENT_BUFFER,
        "returned %u with %u (expected ERROR_INSUFFICIENT_BUFFER)\n",
        res, GetLastError());


    ZeroMemory(pCC, sizeof(pCC));
    pCC[0].dwSize = sizeof(COMMCONFIG);
    SetLastError(0xdeadbeef);
    res = pCommConfigDialogA(emptyA, NULL, pCC);
    ok( res == ERROR_BADKEY, "returned %u with %u (expected ERROR_BADKEY)\n",
        res, GetLastError());


    ZeroMemory(pCC, sizeof(pCC));
    SetLastError(0xdeadbeef);
    res = pCommConfigDialogA(NULL, NULL, pCC);
    ok( res == ERROR_INVALID_PARAMETER,
        "returned %u with %u (expected ERROR_INVALID_PARAMETER)\n",
        res, GetLastError());
}