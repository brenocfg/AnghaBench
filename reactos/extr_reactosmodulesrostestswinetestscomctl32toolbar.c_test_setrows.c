#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rc ;
struct TYPE_6__ {int expectedRows; int /*<<< orphan*/  bLarger; int /*<<< orphan*/  nRows; } ;
typedef  TYPE_1__ TBBUTTON ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int CCS_NOMOVEY ; 
 int CCS_NOPARENTALIGN ; 
 int CCS_NORESIZE ; 
 int CCS_TOP ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MakeButton (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TBSTYLE_CHECKGROUP ; 
 int TBSTYLE_FLAT ; 
 int /*<<< orphan*/  TB_AUTOSIZE ; 
 int /*<<< orphan*/  TB_GETROWS ; 
 int /*<<< orphan*/  TB_SETROWS ; 
 int WS_CHILD ; 
 int WS_CLIPCHILDREN ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  hMainWnd ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * pCreateToolbarEx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* tbrows_results ; 

__attribute__((used)) static void test_setrows(void)
{
    TBBUTTON buttons[9];
    HWND hToolbar;
    DWORD i;

    for (i=0; i<9; i++)
        MakeButton(buttons+i, 1000+i, TBSTYLE_FLAT | TBSTYLE_CHECKGROUP, 0);

    /* Test 1 - 9 buttons */
    hToolbar = pCreateToolbarEx(hMainWnd,
        WS_VISIBLE | WS_CLIPCHILDREN | WS_CHILD | CCS_NORESIZE | CCS_NOPARENTALIGN
        | CCS_NOMOVEY | CCS_TOP,
        0,
        0, NULL, 0,
        buttons, ARRAY_SIZE(buttons),
        20, 20, 0, 0, sizeof(TBBUTTON));
    ok(hToolbar != NULL, "Toolbar creation\n");
    ok(SendMessageA(hToolbar, TB_AUTOSIZE, 0, 0) == 0, "TB_AUTOSIZE failed\n");

    /* test setting rows to each of 1-10 with bLarger true and false */
    for (i=0; i<ARRAY_SIZE(tbrows_results); i++) {
        RECT rc;
        int rows;

        memset(&rc, 0xCC, sizeof(rc));
        SendMessageA(hToolbar, TB_SETROWS,
                     MAKELONG(tbrows_results[i].nRows, tbrows_results[i].bLarger),
                     (LPARAM) &rc);

        rows = SendMessageA(hToolbar, TB_GETROWS, MAKELONG(0,0), MAKELONG(0,0));
        ok(rows == tbrows_results[i].expectedRows,
                   "[%d] Unexpected number of rows %d (expected %d)\n", i, rows,
                   tbrows_results[i].expectedRows);
    }

    DestroyWindow(hToolbar);
}