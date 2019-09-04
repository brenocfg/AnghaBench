#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ hwnd; scalar_t__ message; } ;
struct TYPE_6__ {void* state; void* mask; void* hItem; void* stateMask; } ;
typedef  TYPE_1__ TVITEMA ;
typedef  TYPE_2__ MSG ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HWND ;
typedef  void* HIMAGELIST ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  DispatchMessageA (TYPE_2__*) ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 scalar_t__ GetMessageA (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetWindowLongA (scalar_t__,int /*<<< orphan*/ ) ; 
 void* INDEXTOSTATEIMAGEMASK (int) ; 
 scalar_t__ SendMessageA (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongA (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 void* TVIF_STATE ; 
 void* TVIS_STATEIMAGEMASK ; 
 int /*<<< orphan*/  TVM_GETIMAGELIST ; 
 int /*<<< orphan*/  TVM_GETITEMA ; 
 int /*<<< orphan*/  TVM_SETIMAGELIST ; 
 int /*<<< orphan*/  TVM_SETITEMA ; 
 int /*<<< orphan*/  TVSIL_STATE ; 
 int TVS_CHECKBOXES ; 
 int /*<<< orphan*/  TranslateMessage (TYPE_2__*) ; 
 scalar_t__ WM_PAINT ; 
 scalar_t__ create_treeview_control (int) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fill_tree (scalar_t__) ; 
 void* hChild ; 
 void* hRoot ; 
 int /*<<< orphan*/  ok (int,char*,void*,...) ; 

__attribute__((used)) static void test_TVS_CHECKBOXES(void)
{
    HIMAGELIST himl, himl2;
    HWND hTree, hTree2;
    TVITEMA item;
    DWORD ret;
    MSG msg;

    hTree = create_treeview_control(0);
    fill_tree(hTree);

    himl = (HIMAGELIST)SendMessageA(hTree, TVM_GETIMAGELIST, TVSIL_STATE, 0);
    ok(himl == NULL, "got %p\n", himl);

    item.hItem = hRoot;
    item.mask = TVIF_STATE;
    item.state = INDEXTOSTATEIMAGEMASK(1);
    item.stateMask = TVIS_STATEIMAGEMASK;
    ret = SendMessageA(hTree, TVM_GETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);
    ok(item.state == 0, "got 0x%x\n", item.state);

    /* set some index for a child */
    item.hItem = hChild;
    item.mask = TVIF_STATE;
    item.state = INDEXTOSTATEIMAGEMASK(4);
    item.stateMask = TVIS_STATEIMAGEMASK;
    ret = SendMessageA(hTree, TVM_SETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);

    /* enabling check boxes set all items to 1 state image index */
    SetWindowLongA(hTree, GWL_STYLE, GetWindowLongA(hTree, GWL_STYLE) | TVS_CHECKBOXES);
    himl = (HIMAGELIST)SendMessageA(hTree, TVM_GETIMAGELIST, TVSIL_STATE, 0);
    ok(himl != NULL, "got %p\n", himl);

    himl2 = (HIMAGELIST)SendMessageA(hTree, TVM_GETIMAGELIST, TVSIL_STATE, 0);
    ok(himl2 != NULL, "got %p\n", himl2);
    ok(himl2 == himl, "got %p, expected %p\n", himl2, himl);

    item.hItem = hRoot;
    item.mask = TVIF_STATE;
    item.state = 0;
    item.stateMask = TVIS_STATEIMAGEMASK;
    ret = SendMessageA(hTree, TVM_GETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);
    ok(item.state == INDEXTOSTATEIMAGEMASK(1), "got 0x%x\n", item.state);

    item.hItem = hChild;
    item.mask = TVIF_STATE;
    item.state = 0;
    item.stateMask = TVIS_STATEIMAGEMASK;
    ret = SendMessageA(hTree, TVM_GETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);
    ok(item.state == INDEXTOSTATEIMAGEMASK(1), "got 0x%x\n", item.state);

    /* create another control and check its checkbox list */
    hTree2 = create_treeview_control(0);
    fill_tree(hTree2);

    /* set some index for a child */
    item.hItem = hChild;
    item.mask = TVIF_STATE;
    item.state = INDEXTOSTATEIMAGEMASK(4);
    item.stateMask = TVIS_STATEIMAGEMASK;
    ret = SendMessageA(hTree2, TVM_SETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);

    /* enabling check boxes set all items to 1 state image index */
    SetWindowLongA(hTree2, GWL_STYLE, GetWindowLongA(hTree, GWL_STYLE) | TVS_CHECKBOXES);
    himl2 = (HIMAGELIST)SendMessageA(hTree2, TVM_GETIMAGELIST, TVSIL_STATE, 0);
    ok(himl2 != NULL, "got %p\n", himl2);
    ok(himl != himl2, "got %p, expected %p\n", himl2, himl);

    DestroyWindow(hTree2);
    DestroyWindow(hTree);

    /* the same, but initially created with TVS_CHECKBOXES */
    hTree = create_treeview_control(TVS_CHECKBOXES);
    fill_tree(hTree);
    himl = (HIMAGELIST)SendMessageA(hTree, TVM_GETIMAGELIST, TVSIL_STATE, 0);
    ok(himl == NULL, "got %p\n", himl);

    item.hItem = hRoot;
    item.mask = TVIF_STATE;
    item.state = 0;
    item.stateMask = TVIS_STATEIMAGEMASK;
    ret = SendMessageA(hTree, TVM_GETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);
    ok(item.state == INDEXTOSTATEIMAGEMASK(1), "got 0x%x\n", item.state);

    item.hItem = hChild;
    item.mask = TVIF_STATE;
    item.state = 0;
    item.stateMask = TVIS_STATEIMAGEMASK;
    ret = SendMessageA(hTree, TVM_GETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);
    ok(item.state == INDEXTOSTATEIMAGEMASK(1), "got 0x%x\n", item.state);

    item.hItem = hChild;
    item.mask = TVIF_STATE;
    item.state = INDEXTOSTATEIMAGEMASK(2);
    item.stateMask = TVIS_STATEIMAGEMASK;
    ret = SendMessageA(hTree, TVM_SETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);

    item.hItem = hChild;
    item.mask = TVIF_STATE;
    item.state = 0;
    ret = SendMessageA(hTree, TVM_GETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);
    ok(item.state == INDEXTOSTATEIMAGEMASK(2), "got 0x%x\n", item.state);

    while(GetMessageA(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);

        if((msg.hwnd == hTree) && (msg.message == WM_PAINT))
            break;
    }

    item.hItem = hChild;
    item.mask = TVIF_STATE;
    item.state = 0;
    ret = SendMessageA(hTree, TVM_GETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);
    ok(item.state == INDEXTOSTATEIMAGEMASK(1), "got 0x%x\n", item.state);

    himl = (HIMAGELIST)SendMessageA(hTree, TVM_GETIMAGELIST, TVSIL_STATE, 0);
    ok(himl != NULL, "got %p\n", himl);

    DestroyWindow(hTree);

    /* check what happens if TVSIL_STATE image list is removed */
    hTree = create_treeview_control(0);
    fill_tree(hTree);
    himl = (HIMAGELIST)SendMessageA(hTree, TVM_GETIMAGELIST, TVSIL_STATE, 0);
    ok(himl == NULL, "got %p\n", himl);

    SetWindowLongA(hTree, GWL_STYLE, GetWindowLongA(hTree, GWL_STYLE) | TVS_CHECKBOXES);
    himl = (HIMAGELIST)SendMessageA(hTree, TVM_GETIMAGELIST, TVSIL_STATE, 0);
    ok(himl != NULL, "got %p\n", himl);

    himl2 = (HIMAGELIST)SendMessageA(hTree, TVM_SETIMAGELIST, TVSIL_STATE, 0);
    ok(himl2 == himl, "got %p\n", himl2);

    himl2 = (HIMAGELIST)SendMessageA(hTree, TVM_GETIMAGELIST, TVSIL_STATE, 0);
    ok(himl2 == NULL, "got %p\n", himl2);

    item.hItem = hChild;
    item.mask = TVIF_STATE;
    item.state = INDEXTOSTATEIMAGEMASK(2);
    item.stateMask = TVIS_STATEIMAGEMASK;
    ret = SendMessageA(hTree, TVM_SETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);

    item.hItem = hChild;
    item.mask = TVIF_STATE;
    item.state = 0;
    ret = SendMessageA(hTree, TVM_GETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);
    ok(item.state == INDEXTOSTATEIMAGEMASK(2), "got 0x%x\n", item.state);

    while(GetMessageA(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);

        if((msg.hwnd == hTree) && (msg.message == WM_PAINT))
            break;
    }

    item.hItem = hChild;
    item.mask = TVIF_STATE;
    item.state = 0;
    ret = SendMessageA(hTree, TVM_GETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);
    ok(item.state == INDEXTOSTATEIMAGEMASK(1), "got 0x%x\n", item.state);

    himl = (HIMAGELIST)SendMessageA(hTree, TVM_GETIMAGELIST, TVSIL_STATE, 0);
    ok(himl != NULL, "got %p\n", himl);

    DestroyWindow(hTree);
}