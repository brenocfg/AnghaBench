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
typedef  scalar_t__ UINT_PTR ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ CreateWindowExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GA_PARENT ; 
 int /*<<< orphan*/  GW_OWNER ; 
 scalar_t__ GetCapture () ; 
 scalar_t__ GetDesktopWindow () ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetParent (scalar_t__) ; 
 scalar_t__ GetWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsChild (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IsWindow (scalar_t__) ; 
 int /*<<< orphan*/  SetCapture (scalar_t__) ; 
 scalar_t__ SetParent (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WND_CHILD_ID ; 
 int /*<<< orphan*/  WS_CHILD ; 
 int /*<<< orphan*/  WS_OVERLAPPEDWINDOW ; 
 int /*<<< orphan*/  WS_POPUP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  destroy_window_with_children ; 
 int /*<<< orphan*/  flush_sequence () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pGetAncestor (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_DestroyWindow_flag ; 
 int /*<<< orphan*/  trace (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void test_DestroyWindow(void)
{
    BOOL ret;
    HWND parent, child1, child2, child3, child4, test;
    UINT_PTR child_id = WND_CHILD_ID + 1;

    parent = CreateWindowExA(0, "TestWindowClass", NULL, WS_OVERLAPPEDWINDOW,
			     100, 100, 200, 200, 0, 0, 0, NULL);
    assert(parent != 0);
    child1 = CreateWindowExA(0, "TestWindowClass", NULL, WS_CHILD,
			     0, 0, 50, 50, parent, (HMENU)child_id++, 0, NULL);
    assert(child1 != 0);
    child2 = CreateWindowExA(0, "TestWindowClass", NULL, WS_CHILD,
			     0, 0, 50, 50, GetDesktopWindow(), (HMENU)child_id++, 0, NULL);
    assert(child2 != 0);
    child3 = CreateWindowExA(0, "TestWindowClass", NULL, WS_CHILD,
			     0, 0, 50, 50, child1, (HMENU)child_id++, 0, NULL);
    assert(child3 != 0);
    child4 = CreateWindowExA(0, "TestWindowClass", NULL, WS_POPUP,
			     0, 0, 50, 50, parent, 0, 0, NULL);
    assert(child4 != 0);

    /* test owner/parent of child2 */
    test = GetParent(child2);
    ok(test == GetDesktopWindow(), "wrong parent %p\n", test);
    ok(!IsChild(parent, child2), "wrong parent/child %p/%p\n", parent, child2);
    if(pGetAncestor) {
        test = pGetAncestor(child2, GA_PARENT);
        ok(test == GetDesktopWindow(), "wrong parent %p\n", test);
    }
    test = GetWindow(child2, GW_OWNER);
    ok(!test, "wrong owner %p\n", test);

    test = SetParent(child2, parent);
    ok(test == GetDesktopWindow(), "wrong old parent %p\n", test);

    /* test owner/parent of the parent */
    test = GetParent(parent);
    ok(!test, "wrong parent %p\n", test);
    ok(!IsChild(GetDesktopWindow(), parent), "wrong parent/child %p/%p\n", GetDesktopWindow(), parent);
    if(pGetAncestor) {
        test = pGetAncestor(parent, GA_PARENT);
        ok(test == GetDesktopWindow(), "wrong parent %p\n", test);
    }
    test = GetWindow(parent, GW_OWNER);
    ok(!test, "wrong owner %p\n", test);

    /* test owner/parent of child1 */
    test = GetParent(child1);
    ok(test == parent, "wrong parent %p\n", test);
    ok(IsChild(parent, child1), "wrong parent/child %p/%p\n", parent, child1);
    if(pGetAncestor) {
        test = pGetAncestor(child1, GA_PARENT);
        ok(test == parent, "wrong parent %p\n", test);
    }
    test = GetWindow(child1, GW_OWNER);
    ok(!test, "wrong owner %p\n", test);

    /* test owner/parent of child2 */
    test = GetParent(child2);
    ok(test == parent, "wrong parent %p\n", test);
    ok(IsChild(parent, child2), "wrong parent/child %p/%p\n", parent, child2);
    if(pGetAncestor) {
        test = pGetAncestor(child2, GA_PARENT);
        ok(test == parent, "wrong parent %p\n", test);
    }
    test = GetWindow(child2, GW_OWNER);
    ok(!test, "wrong owner %p\n", test);

    /* test owner/parent of child3 */
    test = GetParent(child3);
    ok(test == child1, "wrong parent %p\n", test);
    ok(IsChild(parent, child3), "wrong parent/child %p/%p\n", parent, child3);
    if(pGetAncestor) {
        test = pGetAncestor(child3, GA_PARENT);
        ok(test == child1, "wrong parent %p\n", test);
    }
    test = GetWindow(child3, GW_OWNER);
    ok(!test, "wrong owner %p\n", test);

    /* test owner/parent of child4 */
    test = GetParent(child4);
    ok(test == parent, "wrong parent %p\n", test);
    ok(!IsChild(parent, child4), "wrong parent/child %p/%p\n", parent, child4);
    if(pGetAncestor) {
        test = pGetAncestor(child4, GA_PARENT);
        ok(test == GetDesktopWindow(), "wrong parent %p\n", test);
    }
    test = GetWindow(child4, GW_OWNER);
    ok(test == parent, "wrong owner %p\n", test);

    flush_sequence();

    trace("parent %p, child1 %p, child2 %p, child3 %p, child4 %p\n",
	   parent, child1, child2, child3, child4);

    SetCapture(child4);
    test = GetCapture();
    ok(test == child4, "wrong capture window %p\n", test);

    test_DestroyWindow_flag = TRUE;
    ret = DestroyWindow(parent);
    ok( ret, "DestroyWindow() error %d\n", GetLastError());
    test_DestroyWindow_flag = FALSE;
    ok_sequence(destroy_window_with_children, "destroy window with children", FALSE);

    ok(!IsWindow(parent), "parent still exists\n");
    ok(!IsWindow(child1), "child1 still exists\n");
    ok(!IsWindow(child2), "child2 still exists\n");
    ok(!IsWindow(child3), "child3 still exists\n");
    ok(!IsWindow(child4), "child4 still exists\n");

    test = GetCapture();
    ok(!test, "wrong capture window %p\n", test);
}