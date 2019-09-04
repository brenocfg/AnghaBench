#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bi ;
struct TYPE_2__ {int cbSize; char* pszText; int /*<<< orphan*/  dwMask; } ;
typedef  TYPE_1__ TBBUTTONINFOA ;
typedef  int LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int CCS_BOTTOM ; 
 int CCS_VERT ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SetWindowLongA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TBIF_TEXT ; 
 int TBSTYLE_EX_MIXEDBUTTONS ; 
 int TBSTYLE_TOOLTIPS ; 
 int TBSTYLE_TRANSPARENT ; 
 int TBSTYLE_WRAPABLE ; 
 int /*<<< orphan*/  TB_GETEXTENDEDSTYLE ; 
 int /*<<< orphan*/  TB_GETSTYLE ; 
 int /*<<< orphan*/  TB_INSERTBUTTONA ; 
 int /*<<< orphan*/  TB_SETBUTTONINFOA ; 
 int /*<<< orphan*/  TB_SETEXTENDEDSTYLE ; 
 int /*<<< orphan*/  TB_SETSTYLE ; 
 int /*<<< orphan*/ * buttons3 ; 
 int did_recalc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  prepare_recalc_test (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  restore_recalc_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_recalc(void)
{
    HWND hToolbar = NULL;
    TBBUTTONINFOA bi;
    CHAR test[] = "Test";
    const int EX_STYLES_COUNT = 5;
    int i;
    BOOL recalc;
    DWORD style;

    /* Like TB_ADDBUTTONSA tested in test_sized, inserting a button without text
     * results in a relayout, while adding one with text forces a recalc */
    prepare_recalc_test(&hToolbar);
    SendMessageA(hToolbar, TB_INSERTBUTTONA, 1, (LPARAM)&buttons3[0]);
    recalc = did_recalc(hToolbar);
    ok(!recalc, "Unexpected recalc - adding button without text\n");

    prepare_recalc_test(&hToolbar);
    SendMessageA(hToolbar, TB_INSERTBUTTONA, 1, (LPARAM)&buttons3[3]);
    recalc = did_recalc(hToolbar);
    ok(recalc, "Expected a recalc - adding button with text\n");

    /* TB_SETBUTTONINFOA, even when adding a text, results only in a relayout */
    prepare_recalc_test(&hToolbar);
    bi.cbSize = sizeof(bi);
    bi.dwMask = TBIF_TEXT;
    bi.pszText = test;
    SendMessageA(hToolbar, TB_SETBUTTONINFOA, 1, (LPARAM)&bi);
    recalc = did_recalc(hToolbar);
    ok(!recalc, "Unexpected recalc - setting a button text\n");

    /* most extended styled doesn't force a recalc (testing all the bits gives
     * the same results, but prints some ERRs while testing) */
    for (i = 0; i < EX_STYLES_COUNT; i++)
    {
        if (i == 1 || i == 3)  /* an undoc style and TBSTYLE_EX_MIXEDBUTTONS */
            continue;
        prepare_recalc_test(&hToolbar);
        expect(0, (int)SendMessageA(hToolbar, TB_GETEXTENDEDSTYLE, 0, 0));
        SendMessageA(hToolbar, TB_SETEXTENDEDSTYLE, 0, (1 << i));
        recalc = did_recalc(hToolbar);
        ok(!recalc, "Unexpected recalc - setting bit %d\n", i);
        SendMessageA(hToolbar, TB_SETEXTENDEDSTYLE, 0, 0);
        recalc = did_recalc(hToolbar);
        ok(!recalc, "Unexpected recalc - clearing bit %d\n", i);
        expect(0, (int)SendMessageA(hToolbar, TB_GETEXTENDEDSTYLE, 0, 0));
    }

    /* TBSTYLE_EX_MIXEDBUTTONS does a recalc on change */
    prepare_recalc_test(&hToolbar);
    SendMessageA(hToolbar, TB_SETEXTENDEDSTYLE, 0, TBSTYLE_EX_MIXEDBUTTONS);
    recalc = did_recalc(hToolbar);
    if (recalc)
    {
        ok(recalc, "Expected a recalc - setting TBSTYLE_EX_MIXEDBUTTONS\n");
        restore_recalc_state(hToolbar);
        SendMessageA(hToolbar, TB_SETEXTENDEDSTYLE, 0, TBSTYLE_EX_MIXEDBUTTONS);
        recalc = did_recalc(hToolbar);
        ok(!recalc, "Unexpected recalc - setting TBSTYLE_EX_MIXEDBUTTONS again\n");
        restore_recalc_state(hToolbar);
        SendMessageA(hToolbar, TB_SETEXTENDEDSTYLE, 0, 0);
        recalc = did_recalc(hToolbar);
        ok(recalc, "Expected a recalc - clearing TBSTYLE_EX_MIXEDBUTTONS\n");
    }
    else win_skip( "No recalc on TBSTYLE_EX_MIXEDBUTTONS\n" );

    /* undocumented exstyle 0x2 seems to change the top margin, which
     * interferes with these tests */

    /* Show that a change in TBSTYLE_WRAPABLE causes a recalc */
    prepare_recalc_test(&hToolbar);
    style = SendMessageA(hToolbar, TB_GETSTYLE, 0, 0);
    SendMessageA(hToolbar, TB_SETSTYLE, 0, style);
    recalc = did_recalc(hToolbar);
    ok(!recalc, "recalc %d\n", recalc);

    SendMessageA(hToolbar, TB_SETSTYLE, 0, style | TBSTYLE_TOOLTIPS | TBSTYLE_TRANSPARENT | CCS_BOTTOM);
    recalc = did_recalc(hToolbar);
    ok(!recalc, "recalc %d\n", recalc);

    SendMessageA(hToolbar, TB_SETSTYLE, 0, style | TBSTYLE_WRAPABLE);
    recalc = did_recalc(hToolbar);
    ok(recalc, "recalc %d\n", recalc);
    restore_recalc_state(hToolbar);

    SendMessageA(hToolbar, TB_SETSTYLE, 0, style | TBSTYLE_WRAPABLE);
    recalc = did_recalc(hToolbar);
    ok(!recalc, "recalc %d\n", recalc);

    SendMessageA(hToolbar, TB_SETSTYLE, 0, style);
    recalc = did_recalc(hToolbar);
    ok(recalc, "recalc %d\n", recalc);
    restore_recalc_state(hToolbar);

    /* Changing CCS_VERT does not recalc */
    SendMessageA(hToolbar, TB_SETSTYLE, 0, style | CCS_VERT);
    recalc = did_recalc(hToolbar);
    ok(!recalc, "recalc %d\n", recalc);
    restore_recalc_state(hToolbar);

    SendMessageA(hToolbar, TB_SETSTYLE, 0, style);
    recalc = did_recalc(hToolbar);
    ok(!recalc, "recalc %d\n", recalc);
    restore_recalc_state(hToolbar);

    /* Setting the window's style directly also causes recalc */
    SetWindowLongA(hToolbar, GWL_STYLE, style | TBSTYLE_WRAPABLE);
    recalc = did_recalc(hToolbar);
    ok(recalc, "recalc %d\n", recalc);

    DestroyWindow(hToolbar);
}