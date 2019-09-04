#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nmtti ;
struct TYPE_7__ {int idFrom; int /*<<< orphan*/  code; } ;
struct TYPE_9__ {TYPE_2__ hdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int member_0; int member_1; int member_6; int /*<<< orphan*/  member_5; TYPE_1__ member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_3__ TBBUTTON ;
typedef  TYPE_4__ NMTTDISPINFOW ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  CCM_SETUNICODEFORMAT ; 
 int /*<<< orphan*/ * CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NUM_MSG_SEQUENCES ; 
 int /*<<< orphan*/  PARENT_SEQ_INDEX ; 
 scalar_t__ SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TBSTATE_ENABLED ; 
 int /*<<< orphan*/  TB_ADDBUTTONSA ; 
 int /*<<< orphan*/  TB_GETTOOLTIPS ; 
 int /*<<< orphan*/  TOOLBARCLASSNAMEA ; 
 int TRUE ; 
 int /*<<< orphan*/  TTN_GETDISPINFOW ; 
 int /*<<< orphan*/  WM_NOTIFY ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  flush_sequences (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_ResetDispTextPtr ; 
 int /*<<< orphan*/  hMainWnd ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rebuild_toolbar (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sequences ; 
 int /*<<< orphan*/  ttgetdispinfo_parent_seq ; 

__attribute__((used)) static void test_tooltip(void)
{
    HWND hToolbar = NULL;
    const TBBUTTON buttons_disp[] = {
        {-1, 20, TBSTATE_ENABLED, 0, {0, }, 0, -1},
        {0,  21, TBSTATE_ENABLED, 0, {0, }, 0, -1},
    };
    NMTTDISPINFOW nmtti;
    HWND tooltip;

    rebuild_toolbar(&hToolbar);

    SendMessageA(hToolbar, TB_ADDBUTTONSA, 2, (LPARAM)buttons_disp);

    /* W used to get through toolbar code that assumes tooltip is always Unicode */
    memset(&nmtti, 0, sizeof(nmtti));
    nmtti.hdr.code = TTN_GETDISPINFOW;
    nmtti.hdr.idFrom = 20;

    SendMessageA(hToolbar, CCM_SETUNICODEFORMAT, FALSE, 0);

    flush_sequences(sequences, NUM_MSG_SEQUENCES);
    SendMessageA(hToolbar, WM_NOTIFY, 0, (LPARAM)&nmtti);
    ok_sequence(sequences, PARENT_SEQ_INDEX, ttgetdispinfo_parent_seq,
                "dispinfo from tooltip", FALSE);

    g_ResetDispTextPtr = TRUE;
    SendMessageA(hToolbar, WM_NOTIFY, 0, (LPARAM)&nmtti);
    g_ResetDispTextPtr = FALSE;

    DestroyWindow(hToolbar);

    /* TBSTYLE_TOOLTIPS */
    hToolbar = CreateWindowExA(0, TOOLBARCLASSNAMEA, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
        hMainWnd, (HMENU)5, GetModuleHandleA(NULL), NULL);
    tooltip = (HWND)SendMessageA(hToolbar, TB_GETTOOLTIPS, 0, 0);
    ok(tooltip == NULL, "got %p\n", tooltip);
    DestroyWindow(hToolbar);
}