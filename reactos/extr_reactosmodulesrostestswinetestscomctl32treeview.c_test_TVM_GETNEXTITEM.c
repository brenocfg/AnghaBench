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
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HTREEITEM ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVGN_CHILD ; 
 int /*<<< orphan*/  TVGN_PARENT ; 
 int /*<<< orphan*/  TVGN_ROOT ; 
 scalar_t__ TVI_ROOT ; 
 int /*<<< orphan*/  TVM_GETNEXTITEM ; 
 int /*<<< orphan*/  create_treeview_control (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hChild ; 
 int /*<<< orphan*/ * hRoot ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *,...) ; 

__attribute__((used)) static void test_TVM_GETNEXTITEM(void)
{
    HTREEITEM item;
    HWND hTree;

    hTree = create_treeview_control(0);
    fill_tree(hTree);

    item = (HTREEITEM)SendMessageA(hTree, TVM_GETNEXTITEM, TVGN_ROOT, 0);
    ok(item == hRoot, "got %p, expected %p\n", item, hRoot);

    item = (HTREEITEM)SendMessageA(hTree, TVM_GETNEXTITEM, TVGN_ROOT, (LPARAM)TVI_ROOT);
    ok(item == hRoot, "got %p, expected %p\n", item, hRoot);

    item = (HTREEITEM)SendMessageA(hTree, TVM_GETNEXTITEM, TVGN_ROOT, (LPARAM)hRoot);
    ok(item == hRoot, "got %p, expected %p\n", item, hRoot);

    item = (HTREEITEM)SendMessageA(hTree, TVM_GETNEXTITEM, TVGN_ROOT, (LPARAM)hChild);
    ok(item == hRoot, "got %p, expected %p\n", item, hRoot);

    item = (HTREEITEM)SendMessageA(hTree, TVM_GETNEXTITEM, TVGN_CHILD, 0);
    ok(item == hRoot, "got %p, expected %p\n", item, hRoot);

    item = (HTREEITEM)SendMessageA(hTree, TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hRoot);
    ok(item == hChild, "got %p, expected %p\n", item, hChild);

    item = (HTREEITEM)SendMessageA(hTree, TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)TVI_ROOT);
    ok(item == hRoot, "got %p, expected %p\n", item, hRoot);

    item = (HTREEITEM)SendMessageA(hTree, TVM_GETNEXTITEM, TVGN_PARENT, 0);
    ok(item == NULL, "got %p\n", item);

    item = (HTREEITEM)SendMessageA(hTree, TVM_GETNEXTITEM, TVGN_PARENT, (LPARAM)hChild);
    ok(item == hRoot, "got %p, expected %p\n", item, hRoot);

    DestroyWindow(hTree);
}