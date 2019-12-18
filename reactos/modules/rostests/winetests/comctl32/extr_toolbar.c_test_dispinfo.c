#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int member_0; int member_1; int member_6; int /*<<< orphan*/  member_5; TYPE_1__ member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_2__ TBBUTTON ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CCM_GETUNICODEFORMAT ; 
 int /*<<< orphan*/  CCM_SETUNICODEFORMAT ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 long FALSE ; 
 scalar_t__ HINST_COMMCTRL ; 
 long IDB_HIST_SMALL_COLOR ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  SW_SHOW ; 
 scalar_t__ SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TBNF_IMAGE ; 
 int /*<<< orphan*/  TBSTATE_ENABLED ; 
 int /*<<< orphan*/  TB_ADDBUTTONSA ; 
 int /*<<< orphan*/  TB_LOADIMAGES ; 
 long TRUE ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compare (scalar_t__,long,char*) ; 
 scalar_t__ g_dwExpectedDispInfoMask ; 
 int /*<<< orphan*/  rebuild_toolbar (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_dispinfo(void)
{
    HWND hToolbar = NULL;
    const TBBUTTON buttons_disp[] = {
        {-1, 20, TBSTATE_ENABLED, 0, {0, }, 0, -1},
        {0,  21, TBSTATE_ENABLED, 0, {0, }, 0, -1},
    };
    BOOL ret;

    rebuild_toolbar(&hToolbar);
    SendMessageA(hToolbar, TB_LOADIMAGES, IDB_HIST_SMALL_COLOR, (LPARAM)HINST_COMMCTRL);
    SendMessageA(hToolbar, TB_ADDBUTTONSA, 2, (LPARAM)buttons_disp);
    g_dwExpectedDispInfoMask = TBNF_IMAGE;
    /* Some TBN_GETDISPINFO tests will be done in MyWnd_Notify function.
     * We will receive TBN_GETDISPINFOW even if the control is ANSI */
    compare((BOOL)SendMessageA(hToolbar, CCM_GETUNICODEFORMAT, 0, 0), 0, "%d");
    ShowWindow(hToolbar, SW_SHOW);
    UpdateWindow(hToolbar);

    ret = (BOOL)SendMessageA(hToolbar, CCM_SETUNICODEFORMAT, TRUE, 0);
    compare(ret, FALSE, "%d");
    compare(SendMessageA(hToolbar, CCM_GETUNICODEFORMAT, 0, 0), 1L, "%ld");
    InvalidateRect(hToolbar, NULL, FALSE);
    UpdateWindow(hToolbar);

    ret = (BOOL)SendMessageA(hToolbar, CCM_SETUNICODEFORMAT, FALSE, 0);
    compare(ret, TRUE, "%d");
    compare(SendMessageA(hToolbar, CCM_GETUNICODEFORMAT, 0, 0), 0L, "%ld");
    InvalidateRect(hToolbar, NULL, FALSE);
    UpdateWindow(hToolbar);

    DestroyWindow(hToolbar);
    g_dwExpectedDispInfoMask = 0;
}