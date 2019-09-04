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
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GETTEXTMARGIN ; 
 int /*<<< orphan*/  BCM_SETTEXTMARGIN ; 
 scalar_t__ BS_DEFCOMMANDLINK ; 
 scalar_t__ BS_PUSHBUTTON ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int EqualRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IsRectEmpty (int /*<<< orphan*/ *) ; 
 int SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  SetRectEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_button (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_get_set_textmargin(void)
{
    HWND hwnd;
    RECT margin_in;
    RECT margin_out;
    BOOL ret;
    DWORD type;

    SetRect(&margin_in, 2, 1, 3, 4);
    for (type = BS_PUSHBUTTON; type <= BS_DEFCOMMANDLINK; type++)
    {
        hwnd = create_button(type, NULL);
        ok(hwnd != NULL, "Expect hwnd not null\n");

        /* Get text margin when it is unset */
        ret = SendMessageA(hwnd, BCM_GETTEXTMARGIN, 0, (LPARAM)&margin_out);
        ok(ret, "Expect ret to be true\n");
        ok(IsRectEmpty(&margin_out), "Expect margin empty\n");

        /* Successful get and set text margin */
        ret = SendMessageA(hwnd, BCM_SETTEXTMARGIN, 0, (LPARAM)&margin_in);
        ok(ret, "Expect ret to be true\n");
        SetRectEmpty(&margin_out);
        ret = SendMessageA(hwnd, BCM_GETTEXTMARGIN, 0, (LPARAM)&margin_out);
        ok(ret, "Expect ret to be true\n");
        ok(EqualRect(&margin_in, &margin_out), "Expect margins to be equal\n");

        /* BCM_SETTEXTMARGIN null pointer handling */
        ret = SendMessageA(hwnd, BCM_SETTEXTMARGIN, 0, 0);
        ok(!ret, "Expect ret to be false\n");
        SetRectEmpty(&margin_out);
        ret = SendMessageA(hwnd, BCM_GETTEXTMARGIN, 0, (LPARAM)&margin_out);
        ok(ret, "Expect ret to be true\n");
        ok(EqualRect(&margin_in, &margin_out), "Expect margins to be equal\n");

        /* BCM_GETTEXTMARGIN null pointer handling */
        ret = SendMessageA(hwnd, BCM_SETTEXTMARGIN, 0, (LPARAM)&margin_in);
        ok(ret, "Expect ret to be true\n");
        ret = SendMessageA(hwnd, BCM_GETTEXTMARGIN, 0, 0);
        ok(!ret, "Expect ret to be true\n");

        DestroyWindow(hwnd);
    }
}