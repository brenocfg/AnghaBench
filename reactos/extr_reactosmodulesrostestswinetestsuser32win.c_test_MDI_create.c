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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  char WCHAR ;
struct TYPE_2__ {char* szClass; char* szTitle; int style; scalar_t__ lParam; void* cy; void* cx; void* y; void* x; int /*<<< orphan*/  hOwner; } ;
typedef  TYPE_1__ MDICREATESTRUCTA ;
typedef  void* LPCSTR ;
typedef  scalar_t__ LPARAM ;
typedef  scalar_t__ INT_PTR ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/ * HMENU ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 void* CW_USEDEFAULT ; 
 scalar_t__ CreateMDIWindowA (char*,char*,int,void*,void*,void*,void*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ CreateMDIWindowW (char const*,char const*,int /*<<< orphan*/ ,void*,void*,void*,void*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int,void*,void*,void*,void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ CreateWindowExW (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,void*,void*,void*,void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * GetMenu (scalar_t__) ; 
 scalar_t__ GetMenuItemCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int GetWindowLongA (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowLongPtrA (scalar_t__,int /*<<< orphan*/ ) ; 
 int GetWindowLongW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindow (scalar_t__) ; 
 int MDIS_ALLCHILDSTYLES ; 
 scalar_t__ SendMessageA (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_MDICREATE ; 
 int /*<<< orphan*/  WM_MDIDESTROY ; 
 int /*<<< orphan*/  WM_MDIGETACTIVE ; 
 int WS_CAPTION ; 
 int WS_CHILD ; 
 int /*<<< orphan*/  WS_EX_MDICHILD ; 
 int WS_MAXIMIZE ; 
 int WS_POPUP ; 
 int WS_THICKFRAME ; 
 int WS_VISIBLE ; 
 scalar_t__ mdi_lParam_test_message ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_MDI_create(HWND parent, HWND mdi_client, INT_PTR first_id)
{
    MDICREATESTRUCTA mdi_cs;
    HWND mdi_child, hwnd, exp_hwnd;
    INT_PTR id;
    static const WCHAR classW[] = {'M','D','I','_','c','h','i','l','d','_','C','l','a','s','s','_','1',0};
    static const WCHAR titleW[] = {'M','D','I',' ','c','h','i','l','d',0};
    BOOL isWin9x = FALSE;
    HMENU frame_menu = GetMenu(parent);

    ok(frame_menu != NULL, "Frame window didn't have a menu\n");

    mdi_cs.szClass = "MDI_child_Class_1";
    mdi_cs.szTitle = "MDI child";
    mdi_cs.hOwner = GetModuleHandleA(NULL);
    mdi_cs.x = CW_USEDEFAULT;
    mdi_cs.y = CW_USEDEFAULT;
    mdi_cs.cx = CW_USEDEFAULT;
    mdi_cs.cy = CW_USEDEFAULT;
    mdi_cs.style = 0;
    mdi_cs.lParam = (LPARAM)mdi_lParam_test_message;
    mdi_child = (HWND)SendMessageA(mdi_client, WM_MDICREATE, 0, (LPARAM)&mdi_cs);
    ok(mdi_child != 0, "MDI child creation failed\n");
    id = GetWindowLongPtrA(mdi_child, GWLP_ID);
    ok(id == first_id, "wrong child id %ld\n", id);
    hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
    exp_hwnd = (GetWindowLongW(mdi_child, GWL_STYLE) & WS_VISIBLE) ? mdi_child : 0;
    ok(hwnd == exp_hwnd, "WM_MDIGETACTIVE should return %p, got %p\n", exp_hwnd, hwnd);
    SendMessageA(mdi_client, WM_MDIDESTROY, (WPARAM)mdi_child, 0);
    ok(!IsWindow(mdi_child), "WM_MDIDESTROY failed\n");

    mdi_cs.style = 0x7fffffff; /* without WS_POPUP */
    mdi_child = (HWND)SendMessageA(mdi_client, WM_MDICREATE, 0, (LPARAM)&mdi_cs);
    ok(mdi_child != 0, "MDI child creation failed\n");
    id = GetWindowLongPtrA(mdi_child, GWLP_ID);
    ok(id == first_id, "wrong child id %ld\n", id);
    hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
    ok(!hwnd, "WM_MDIGETACTIVE should return 0, got %p\n", hwnd);
    SendMessageA(mdi_client, WM_MDIDESTROY, (WPARAM)mdi_child, 0);
    ok(!IsWindow(mdi_child), "WM_MDIDESTROY failed\n");

    mdi_cs.style = 0xffffffff; /* with WS_POPUP */
    mdi_child = (HWND)SendMessageA(mdi_client, WM_MDICREATE, 0, (LPARAM)&mdi_cs);
    if (GetWindowLongA(mdi_client, GWL_STYLE) & MDIS_ALLCHILDSTYLES)
    {
        ok(!mdi_child, "MDI child with WS_POPUP and with MDIS_ALLCHILDSTYLES should fail\n");
    }
    else
    {
        ok(mdi_child != 0, "MDI child creation failed\n");
        id = GetWindowLongPtrA(mdi_child, GWLP_ID);
        ok(id == first_id, "wrong child id %ld\n", id);
        hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
        ok(!hwnd, "WM_MDIGETACTIVE should return 0, got %p\n", hwnd);
        ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
        SendMessageA(mdi_client, WM_MDIDESTROY, (WPARAM)mdi_child, 0);
        ok(!IsWindow(mdi_child), "WM_MDIDESTROY failed\n");
    }

    /* test MDICREATESTRUCT A<->W mapping */
    /* MDICREATESTRUCTA and MDICREATESTRUCTW have the same layout */
    mdi_cs.style = 0;
    mdi_cs.szClass = (LPCSTR)classW;
    mdi_cs.szTitle = (LPCSTR)titleW;
    SetLastError(0xdeadbeef);
    mdi_child = (HWND)SendMessageW(mdi_client, WM_MDICREATE, 0, (LPARAM)&mdi_cs);
    if (!mdi_child)
    {
        if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
            isWin9x = TRUE;
        else
            ok(mdi_child != 0, "MDI child creation failed\n");
    }
    else
    {
        id = GetWindowLongPtrA(mdi_child, GWLP_ID);
        ok(id == first_id, "wrong child id %ld\n", id);
        hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
        exp_hwnd = (GetWindowLongW(mdi_child, GWL_STYLE) & WS_VISIBLE) ? mdi_child : 0;
        ok(hwnd == exp_hwnd, "WM_MDIGETACTIVE should return %p, got %p\n", exp_hwnd, hwnd);
        ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
        SendMessageA(mdi_client, WM_MDIDESTROY, (WPARAM)mdi_child, 0);
        ok(!IsWindow(mdi_child), "WM_MDIDESTROY failed\n");
    }

    mdi_child = CreateMDIWindowA("MDI_child_Class_1", "MDI child",
                                 0,
                                 CW_USEDEFAULT, CW_USEDEFAULT,
                                 CW_USEDEFAULT, CW_USEDEFAULT,
                                 mdi_client, GetModuleHandleA(NULL),
                                 (LPARAM)mdi_lParam_test_message);
    ok(mdi_child != 0, "MDI child creation failed\n");
    id = GetWindowLongPtrA(mdi_child, GWLP_ID);
    ok(id == first_id, "wrong child id %ld\n", id);
    hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
    exp_hwnd = (GetWindowLongW(mdi_child, GWL_STYLE) & WS_VISIBLE) ? mdi_child : 0;
    ok(hwnd == exp_hwnd, "WM_MDIGETACTIVE should return %p, got %p\n", exp_hwnd, hwnd);
    ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
    SendMessageA(mdi_client, WM_MDIDESTROY, (WPARAM)mdi_child, 0);
    ok(!IsWindow(mdi_child), "WM_MDIDESTROY failed\n");

    mdi_child = CreateMDIWindowA("MDI_child_Class_1", "MDI child",
                                 0x7fffffff, /* without WS_POPUP */
                                 CW_USEDEFAULT, CW_USEDEFAULT,
                                 CW_USEDEFAULT, CW_USEDEFAULT,
                                 mdi_client, GetModuleHandleA(NULL),
                                 (LPARAM)mdi_lParam_test_message);
    ok(mdi_child != 0, "MDI child creation failed\n");
    id = GetWindowLongPtrA(mdi_child, GWLP_ID);
    ok(id == first_id, "wrong child id %ld\n", id);
    hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
    ok(!hwnd, "WM_MDIGETACTIVE should return 0, got %p\n", hwnd);
    ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
    SendMessageA(mdi_client, WM_MDIDESTROY, (WPARAM)mdi_child, 0);
    ok(!IsWindow(mdi_child), "WM_MDIDESTROY failed\n");

    mdi_child = CreateMDIWindowA("MDI_child_Class_1", "MDI child",
                                 0xffffffff, /* with WS_POPUP */
                                 CW_USEDEFAULT, CW_USEDEFAULT,
                                 CW_USEDEFAULT, CW_USEDEFAULT,
                                 mdi_client, GetModuleHandleA(NULL),
                                 (LPARAM)mdi_lParam_test_message);
    if (GetWindowLongA(mdi_client, GWL_STYLE) & MDIS_ALLCHILDSTYLES)
    {
        ok(!mdi_child, "MDI child with WS_POPUP and with MDIS_ALLCHILDSTYLES should fail\n");
    }
    else
    {
        ok(mdi_child != 0, "MDI child creation failed\n");
        id = GetWindowLongPtrA(mdi_child, GWLP_ID);
        ok(id == first_id, "wrong child id %ld\n", id);
        hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
        ok(!hwnd, "WM_MDIGETACTIVE should return 0, got %p\n", hwnd);
        ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
        SendMessageA(mdi_client, WM_MDIDESTROY, (WPARAM)mdi_child, 0);
        ok(!IsWindow(mdi_child), "WM_MDIDESTROY failed\n");
    }

    /* test MDICREATESTRUCT A<->W mapping */
    SetLastError(0xdeadbeef);
    mdi_child = CreateMDIWindowW(classW, titleW,
                                 0,
                                 CW_USEDEFAULT, CW_USEDEFAULT,
                                 CW_USEDEFAULT, CW_USEDEFAULT,
                                 mdi_client, GetModuleHandleA(NULL),
                                 (LPARAM)mdi_lParam_test_message);
    if (!mdi_child)
    {
        if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
            isWin9x = TRUE;
        else
            ok(mdi_child != 0, "MDI child creation failed\n");
    }
    else
    {
        id = GetWindowLongPtrA(mdi_child, GWLP_ID);
        ok(id == first_id, "wrong child id %ld\n", id);
        hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
        exp_hwnd = (GetWindowLongW(mdi_child, GWL_STYLE) & WS_VISIBLE) ? mdi_child : 0;
        ok(hwnd == exp_hwnd, "WM_MDIGETACTIVE should return %p, got %p\n", exp_hwnd, hwnd);
        ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
        SendMessageA(mdi_client, WM_MDIDESTROY, (WPARAM)mdi_child, 0);
        ok(!IsWindow(mdi_child), "WM_MDIDESTROY failed\n");
    }

    mdi_child = CreateWindowExA(WS_EX_MDICHILD, "MDI_child_Class_1", "MDI child",
                                0,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                mdi_client, 0, GetModuleHandleA(NULL),
                                mdi_lParam_test_message);
    ok(mdi_child != 0, "MDI child creation failed\n");
    id = GetWindowLongPtrA(mdi_child, GWLP_ID);
    ok(id == first_id, "wrong child id %ld\n", id);
    hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
    exp_hwnd = (GetWindowLongW(mdi_child, GWL_STYLE) & WS_VISIBLE) ? mdi_child : 0;
    ok(hwnd == exp_hwnd, "WM_MDIGETACTIVE should return %p, got %p\n", exp_hwnd, hwnd);
    ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
    SendMessageA(mdi_client, WM_MDIDESTROY, (WPARAM)mdi_child, 0);
    ok(!IsWindow(mdi_child), "WM_MDIDESTROY failed\n");

    mdi_child = CreateWindowExA(WS_EX_MDICHILD, "MDI_child_Class_1", "MDI child",
                                WS_MAXIMIZE,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                mdi_client, 0, GetModuleHandleA(NULL),
                                mdi_lParam_test_message);
    ok(mdi_child != 0, "MDI child creation failed\n");
    id = GetWindowLongPtrA(mdi_child, GWLP_ID);
    ok(id == first_id, "wrong child id %ld\n", id);
    hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
    exp_hwnd = (GetWindowLongW(mdi_child, GWL_STYLE) & WS_VISIBLE) ? mdi_child : 0;
    ok(hwnd == exp_hwnd, "WM_MDIGETACTIVE should return %p, got %p\n", exp_hwnd, hwnd);
    if (GetWindowLongA(mdi_client, GWL_STYLE) & MDIS_ALLCHILDSTYLES)
        ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
    else
        ok(GetMenuItemCount(frame_menu) == 4, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
    SendMessageA(mdi_client, WM_MDIDESTROY, (WPARAM)mdi_child, 0);
    ok(!IsWindow(mdi_child), "WM_MDIDESTROY failed\n");

    mdi_child = CreateWindowExA(WS_EX_MDICHILD, "MDI_child_Class_1", "MDI child",
                                0x7fffffff, /* without WS_POPUP */
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                mdi_client, 0, GetModuleHandleA(NULL),
                                mdi_lParam_test_message);
    ok(mdi_child != 0, "MDI child creation failed\n");
    id = GetWindowLongPtrA(mdi_child, GWLP_ID);
    ok(id == first_id, "wrong child id %ld\n", id);
    hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
    ok(!hwnd, "WM_MDIGETACTIVE should return 0, got %p\n", hwnd);
    ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
    SendMessageA(mdi_client, WM_MDIDESTROY, (WPARAM)mdi_child, 0);
    ok(!IsWindow(mdi_child), "WM_MDIDESTROY failed\n");

    mdi_child = CreateWindowExA(WS_EX_MDICHILD, "MDI_child_Class_1", "MDI child",
                                0xffffffff, /* with WS_POPUP */
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                mdi_client, 0, GetModuleHandleA(NULL),
                                mdi_lParam_test_message);
    if (GetWindowLongA(mdi_client, GWL_STYLE) & MDIS_ALLCHILDSTYLES)
    {
        ok(!mdi_child, "MDI child with WS_POPUP and with MDIS_ALLCHILDSTYLES should fail\n");
    }
    else
    {
        ok(mdi_child != 0, "MDI child creation failed\n");
        id = GetWindowLongPtrA(mdi_child, GWLP_ID);
        ok(id == first_id, "wrong child id %ld\n", id);
        hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
        ok(!hwnd, "WM_MDIGETACTIVE should return 0, got %p\n", hwnd);
        ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
        SendMessageA(mdi_client, WM_MDIDESTROY, (WPARAM)mdi_child, 0);
        ok(!IsWindow(mdi_child), "WM_MDIDESTROY failed\n");
    }

    /* test MDICREATESTRUCT A<->W mapping */
    SetLastError(0xdeadbeef);
    mdi_child = CreateWindowExW(WS_EX_MDICHILD, classW, titleW,
                                0,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                mdi_client, 0, GetModuleHandleA(NULL),
                                mdi_lParam_test_message);
    if (!mdi_child)
    {
        if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
            isWin9x = TRUE;
        else
            ok(mdi_child != 0, "MDI child creation failed\n");
    }
    else
    {
        id = GetWindowLongPtrA(mdi_child, GWLP_ID);
        ok(id == first_id, "wrong child id %ld\n", id);
        hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
        exp_hwnd = (GetWindowLongW(mdi_child, GWL_STYLE) & WS_VISIBLE) ? mdi_child : 0;
        ok(hwnd == exp_hwnd, "WM_MDIGETACTIVE should return %p, got %p\n", exp_hwnd, hwnd);
        ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
        SendMessageA(mdi_client, WM_MDIDESTROY, (WPARAM)mdi_child, 0);
        ok(!IsWindow(mdi_child), "WM_MDIDESTROY failed\n");
    }

    /* This test fails on Win9x */
    if (!isWin9x)
    {
        mdi_child = CreateWindowExA(WS_EX_MDICHILD, "MDI_child_Class_2", "MDI child",
                                WS_CHILD,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                parent, 0, GetModuleHandleA(NULL),
                                mdi_lParam_test_message);
        ok(!mdi_child, "WS_EX_MDICHILD with a not MDIClient parent should fail\n");
    }

    mdi_child = CreateWindowExA(0, "MDI_child_Class_2", "MDI child",
                                WS_CHILD, /* without WS_POPUP */
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                mdi_client, 0, GetModuleHandleA(NULL),
                                mdi_lParam_test_message);
    ok(mdi_child != 0, "MDI child creation failed\n");
    id = GetWindowLongPtrA(mdi_child, GWLP_ID);
    ok(id == 0, "wrong child id %ld\n", id);
    ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
    hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
    ok(!hwnd, "WM_MDIGETACTIVE should return 0, got %p\n", hwnd);
    DestroyWindow(mdi_child);

    mdi_child = CreateWindowExA(0, "MDI_child_Class_2", "MDI child",
                                WS_CHILD | WS_POPUP, /* with WS_POPUP */
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                mdi_client, 0, GetModuleHandleA(NULL),
                                mdi_lParam_test_message);
    ok(mdi_child != 0, "MDI child creation failed\n");
    id = GetWindowLongPtrA(mdi_child, GWLP_ID);
    ok(id == 0, "wrong child id %ld\n", id);
    hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
    ok(!hwnd, "WM_MDIGETACTIVE should return 0, got %p\n", hwnd);
    ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
    DestroyWindow(mdi_child);

    /* maximized child */
    mdi_child = CreateWindowExA(0, "MDI_child_Class_2", "MDI child",
                                WS_CHILD | WS_MAXIMIZE,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                mdi_client, 0, GetModuleHandleA(NULL),
                                mdi_lParam_test_message);
    ok(mdi_child != 0, "MDI child creation failed\n");
    id = GetWindowLongPtrA(mdi_child, GWLP_ID);
    ok(id == 0, "wrong child id %ld\n", id);
    hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
    ok(!hwnd, "WM_MDIGETACTIVE should return 0, got %p\n", hwnd);
    ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
    DestroyWindow(mdi_child);

    trace("Creating maximized child with a caption\n");
    mdi_child = CreateWindowExA(0, "MDI_child_Class_2", "MDI child",
                                WS_CHILD | WS_MAXIMIZE | WS_CAPTION,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                mdi_client, 0, GetModuleHandleA(NULL),
                                mdi_lParam_test_message);
    ok(mdi_child != 0, "MDI child creation failed\n");
    id = GetWindowLongPtrA(mdi_child, GWLP_ID);
    ok(id == 0, "wrong child id %ld\n", id);
    hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
    ok(!hwnd, "WM_MDIGETACTIVE should return 0, got %p\n", hwnd);
    ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
    DestroyWindow(mdi_child);

    trace("Creating maximized child with a caption and a thick frame\n");
    mdi_child = CreateWindowExA(0, "MDI_child_Class_2", "MDI child",
                                WS_CHILD | WS_MAXIMIZE | WS_CAPTION | WS_THICKFRAME,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                mdi_client, 0, GetModuleHandleA(NULL),
                                mdi_lParam_test_message);
    ok(mdi_child != 0, "MDI child creation failed\n");
    id = GetWindowLongPtrA(mdi_child, GWLP_ID);
    ok(id == 0, "wrong child id %ld\n", id);
    hwnd = (HWND)SendMessageA(mdi_client, WM_MDIGETACTIVE, 0, 0);
    ok(!hwnd, "WM_MDIGETACTIVE should return 0, got %p\n", hwnd);
    ok(GetMenuItemCount(frame_menu) == 0, "Got wrong frame menu item count: %u\n", GetMenuItemCount(frame_menu));
    DestroyWindow(mdi_child);
}