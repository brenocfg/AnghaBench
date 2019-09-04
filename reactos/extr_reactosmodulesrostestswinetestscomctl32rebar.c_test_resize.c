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
struct TYPE_2__ {int cx; int cy; int x; int y; scalar_t__ flags; int /*<<< orphan*/ * hwndInsertAfter; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ WINDOWPOS ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int CCS_BOTTOM ; 
 int CCS_NODIVIDER ; 
 int CCS_NOMOVEY ; 
 int CCS_NOPARENTALIGN ; 
 int CCS_NORESIZE ; 
 int CCS_RIGHT ; 
 int CCS_TOP ; 
 int CCS_VERT ; 
 int /*<<< orphan*/  CreateWindowA (int /*<<< orphan*/ ,char*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAKELONG (int,int) ; 
 int /*<<< orphan*/  MoveWindow (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_DELETEBAND ; 
 int /*<<< orphan*/  REBARCLASSNAMEA ; 
 int /*<<< orphan*/  SIZE_RESTORED ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SIZE ; 
 int /*<<< orphan*/  WM_WINDOWPOSCHANGED ; 
 int /*<<< orphan*/  WM_WINDOWPOSCHANGING ; 
 int WS_BORDER ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  add_band_w (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_client () ; 
 int /*<<< orphan*/  comment (char*,int) ; 
 int /*<<< orphan*/  hMainWnd ; 
 int /*<<< orphan*/  height_change_notify_rect ; 

__attribute__((used)) static void test_resize(void)
{
    DWORD dwStyles[] = {CCS_TOP, CCS_TOP | CCS_NODIVIDER, CCS_BOTTOM, CCS_BOTTOM | CCS_NODIVIDER, CCS_VERT, CCS_RIGHT,
        CCS_NOPARENTALIGN, CCS_NOPARENTALIGN | CCS_NODIVIDER, CCS_NORESIZE, CCS_NOMOVEY, CCS_NOMOVEY | CCS_VERT,
        CCS_TOP | WS_BORDER, CCS_NOPARENTALIGN | CCS_NODIVIDER | WS_BORDER, CCS_NORESIZE | WS_BORDER,
        CCS_NOMOVEY | WS_BORDER};

    const int styles_count = ARRAY_SIZE(dwStyles);
    int i;

    for (i = 0; i < styles_count; i++)
    {
        HWND hRebar;

        comment("style %08x", dwStyles[i]);
        SetRect(&height_change_notify_rect, -1, -1, -1, -1);
        hRebar = CreateWindowA(REBARCLASSNAMEA, "A", dwStyles[i] | WS_CHILD | WS_VISIBLE, 10, 5, 500, 15, hMainWnd, NULL, GetModuleHandleA(NULL), 0);
        check_client();
        add_band_w(hRebar, NULL, 70, 100, 0);
        if (dwStyles[i] & CCS_NOPARENTALIGN)  /* the window drifts downward for CCS_NOPARENTALIGN without CCS_NODIVIDER */
            check_client();
        add_band_w(hRebar, NULL, 70, 100, 0);
        check_client();
        MoveWindow(hRebar, 10, 10, 100, 100, TRUE);
        check_client();
        MoveWindow(hRebar, 0, 0, 0, 0, TRUE);
        check_client();
        /* try to fool the rebar by sending invalid width/height - won't work */
        if (dwStyles[i] & (CCS_NORESIZE | CCS_NOPARENTALIGN))
        {
            WINDOWPOS pos;
            pos.hwnd = hRebar;
            pos.hwndInsertAfter = NULL;
            pos.cx = 500;
            pos.cy = 500;
            pos.x = 10;
            pos.y = 10;
            pos.flags = 0;
            SendMessageA(hRebar, WM_WINDOWPOSCHANGING, 0, (LPARAM)&pos);
            SendMessageA(hRebar, WM_WINDOWPOSCHANGED, 0, (LPARAM)&pos);
            check_client();
            SendMessageA(hRebar, WM_SIZE, SIZE_RESTORED, MAKELONG(500, 500));
            check_client();
        }
        SendMessageA(hRebar, RB_DELETEBAND, 0, 0);
        check_client();
        SendMessageA(hRebar, RB_DELETEBAND, 0, 0);
        MoveWindow(hRebar, 0, 0, 100, 100, TRUE);
        check_client();
        DestroyWindow(hRebar);
    }
}