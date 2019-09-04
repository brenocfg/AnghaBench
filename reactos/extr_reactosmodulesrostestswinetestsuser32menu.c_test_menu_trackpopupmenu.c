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
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/ * HMENU ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AppendMenuA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int /*<<< orphan*/ * CreatePopupMenu () ; 
 int /*<<< orphan*/ * CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyMenu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int ERROR_INVALID_MENU_HANDLE ; 
 int ERROR_INVALID_WINDOW_HANDLE ; 
 int /*<<< orphan*/  GWLP_WNDPROC ; 
 int GetLastError () ; 
 scalar_t__ MAKEINTATOM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MF_STRING ; 
 int /*<<< orphan*/  MyTrackPopupMenu (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SetWindowLongPtrA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_RETURNCMD ; 
 int /*<<< orphan*/  WS_VISIBLE ; 
 int /*<<< orphan*/  atomMenuCheckClass ; 
 scalar_t__ broken (int) ; 
 scalar_t__ gflag_entermenuloop ; 
 scalar_t__ gflag_initmenu ; 
 scalar_t__ gflag_initmenupopup ; 
 scalar_t__ menu_ownerdraw_wnd_proc ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_menu_trackpopupmenu(void)
{
    BOOL ret;
    HMENU hmenu;
    DWORD gle;
    int Ex;
    HWND hwnd = CreateWindowExA(0, (LPCSTR)MAKEINTATOM(atomMenuCheckClass), NULL,
            WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 200, 200,
            NULL, NULL, NULL, NULL);
    ok(hwnd != NULL, "CreateWindowEx failed with error %d\n", GetLastError());
    if (!hwnd) return;
    SetWindowLongPtrA( hwnd, GWLP_WNDPROC, (LONG_PTR)menu_ownerdraw_wnd_proc);
    for( Ex = 0; Ex < 2; Ex++)
    {
        hmenu = CreatePopupMenu();
        ok(hmenu != NULL, "CreateMenu failed with error %d\n", GetLastError());
        if (!hmenu)
        {
            DestroyWindow(hwnd);
            return;
        }
        /* display the menu */
        /* start with an invalid menu handle */
        SetLastError(0xdeadbeef);

        gflag_initmenupopup = gflag_entermenuloop = gflag_initmenu = 0;
        ret = MyTrackPopupMenu( Ex, NULL, TPM_RETURNCMD, 100,100, hwnd, NULL);
        gle = GetLastError();
        ok( !ret, "TrackPopupMenu%s should have failed\n", Ex ? "Ex" : "");
        ok( gle == ERROR_INVALID_MENU_HANDLE
            || broken (gle == 0xdeadbeef) /* win95 */
            || broken (gle == NO_ERROR) /* win98/ME */
            ,"TrackPopupMenu%s error got %u expected %u\n",
            Ex ? "Ex" : "", gle, ERROR_INVALID_MENU_HANDLE);
        ok( !(gflag_initmenupopup || gflag_entermenuloop || gflag_initmenu),
                "got unexpected message(s)%s%s%s\n",
                gflag_initmenupopup ? " WM_INITMENUPOPUP ": " ",
                gflag_entermenuloop ? "WM_INITMENULOOP ": "",
                gflag_initmenu ? "WM_INITMENU": "");
        /* another one but not NULL */
        SetLastError(0xdeadbeef);
        gflag_initmenupopup = gflag_entermenuloop = gflag_initmenu = 0;
        ret = MyTrackPopupMenu( Ex, (HMENU)hwnd, TPM_RETURNCMD, 100,100, hwnd, NULL);
        gle = GetLastError();
        ok( !ret, "TrackPopupMenu%s should have failed\n", Ex ? "Ex" : "");
        ok( gle == ERROR_INVALID_MENU_HANDLE
            || broken (gle == 0xdeadbeef) /* win95 */
            || broken (gle == NO_ERROR) /* win98/ME */
            ,"TrackPopupMenu%s error got %u expected %u\n",
            Ex ? "Ex" : "", gle, ERROR_INVALID_MENU_HANDLE);
        ok( !(gflag_initmenupopup || gflag_entermenuloop || gflag_initmenu),
                "got unexpected message(s)%s%s%s\n",
                gflag_initmenupopup ? " WM_INITMENUPOPUP ": " ",
                gflag_entermenuloop ? "WM_INITMENULOOP ": "",
                gflag_initmenu ? "WM_INITMENU": "");

        /* invalid window */
        SetLastError(0xdeadbeef);
        gflag_initmenupopup = gflag_entermenuloop = gflag_initmenu = 0;
        ret = MyTrackPopupMenu( Ex, hmenu, TPM_RETURNCMD, 100,100, 0, NULL);
        gle = GetLastError();
        ok( !ret, "TrackPopupMenu%s should have failed\n", Ex ? "Ex" : "");
        ok( gle == ERROR_INVALID_WINDOW_HANDLE, "TrackPopupMenu%s error got %u\n", Ex ? "Ex" : "", gle );
        ok( !(gflag_initmenupopup || gflag_entermenuloop || gflag_initmenu),
                "got unexpected message(s)%s%s%s\n",
                gflag_initmenupopup ? " WM_INITMENUPOPUP ": " ",
                gflag_entermenuloop ? "WM_INITMENULOOP ": "",
                gflag_initmenu ? "WM_INITMENU": "");

        /* now a somewhat successful call */
        SetLastError(0xdeadbeef);
        gflag_initmenupopup = gflag_entermenuloop = gflag_initmenu = 0;
        ret = MyTrackPopupMenu( Ex, hmenu, TPM_RETURNCMD, 100,100, hwnd, NULL);
        gle = GetLastError();
        ok( ret == 0, "TrackPopupMenu%s returned %d expected zero\n", Ex ? "Ex" : "", ret);
        ok( gle == NO_ERROR
            || gle == ERROR_INVALID_MENU_HANDLE /* NT4, win2k */
            || broken (gle == 0xdeadbeef) /* win95 */
            ,"TrackPopupMenu%s error got %u expected %u or %u\n",
            Ex ? "Ex" : "", gle, NO_ERROR, ERROR_INVALID_MENU_HANDLE);
        ok( gflag_initmenupopup && gflag_entermenuloop && gflag_initmenu,
                "missed expected message(s)%s%s%s\n",
                !gflag_initmenupopup ? " WM_INITMENUPOPUP ": " ",
                !gflag_entermenuloop ? "WM_INITMENULOOP ": "",
                !gflag_initmenu ? "WM_INITMENU": "");
        /* and another */
        ret = AppendMenuA( hmenu, MF_STRING, 1, "winetest");
        ok( ret, "AppendMenA has failed!\n");
        SetLastError(0xdeadbeef);
        gflag_initmenupopup = gflag_entermenuloop = gflag_initmenu = 0;
        ret = MyTrackPopupMenu( Ex, hmenu, TPM_RETURNCMD, 100,100, hwnd, NULL);
        gle = GetLastError();
        ok( ret == 0, "TrackPopupMenu%s returned %d expected zero\n", Ex ? "Ex" : "", ret);
        ok( gle == NO_ERROR
            || gle == ERROR_INVALID_MENU_HANDLE /* NT4, win2k and Vista in the TrackPopupMenuEx case */
            || broken (gle == 0xdeadbeef) /* win95 */
            ,"TrackPopupMenu%s error got %u expected %u or %u\n",
            Ex ? "Ex" : "", gle, NO_ERROR, ERROR_INVALID_MENU_HANDLE);
        ok( gflag_initmenupopup && gflag_entermenuloop && gflag_initmenu,
                "missed expected message(s)%s%s%s\n",
                !gflag_initmenupopup ? " WM_INITMENUPOPUP ": " ",
                !gflag_entermenuloop ? "WM_INITMENULOOP ": "",
                !gflag_initmenu ? "WM_INITMENU": "");
        DestroyMenu(hmenu);
    }
    /* clean up */
    DestroyWindow(hwnd);
}