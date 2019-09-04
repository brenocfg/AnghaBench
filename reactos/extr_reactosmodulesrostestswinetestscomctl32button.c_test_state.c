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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BM_GETSTATE ; 
 scalar_t__ BST_UNCHECKED ; 
 scalar_t__ BS_DEFCOMMANDLINK ; 
 scalar_t__ BS_PUSHBUTTON ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_button (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void test_state(void)
{
    HWND hwnd;
    DWORD type;
    LONG state;

    /* Initial button state */
    for (type = BS_PUSHBUTTON; type <= BS_DEFCOMMANDLINK; type++)
    {
        hwnd = create_button(type, NULL);
        state = SendMessageA(hwnd, BM_GETSTATE, 0, 0);
        ok(state == BST_UNCHECKED, "Expect state 0x%08x, got 0x%08x\n", BST_UNCHECKED, state);
        DestroyWindow(hwnd);
    }
}