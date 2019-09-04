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
typedef  int /*<<< orphan*/  UINT_PTR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HMENU ;
typedef  scalar_t__ HICON ;
typedef  scalar_t__ HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  scalar_t__ HBITMAP ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AppendMenuW (scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COLOR_MENU ; 
 scalar_t__ CreateCompatibleBitmap (scalar_t__,int,int) ; 
 scalar_t__ CreateCompatibleDC (scalar_t__) ; 
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DI_NORMAL ; 
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyMenu (scalar_t__) ; 
 int /*<<< orphan*/  DrawIconEx (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawMenuBar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  EnableMenuItem (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GCLP_HICON ; 
 int /*<<< orphan*/  GCLP_HICONSM ; 
 scalar_t__ GetClassLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ GetMenu (int /*<<< orphan*/ ) ; 
 scalar_t__ GetMenuItemCount (scalar_t__) ; 
 scalar_t__ GetMenuItemID (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 scalar_t__ GetSystemMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 scalar_t__ HBMMENU_MBAR_CLOSE ; 
 scalar_t__ HBMMENU_MBAR_CLOSE_D ; 
 scalar_t__ HBMMENU_MBAR_MINIMIZE ; 
 scalar_t__ HBMMENU_MBAR_RESTORE ; 
 int /*<<< orphan*/  ICON_BIG ; 
 int /*<<< orphan*/  ICON_SMALL ; 
 scalar_t__ IDI_WINLOGO ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 int /*<<< orphan*/  InsertMenuA (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LR_DEFAULTCOLOR ; 
 scalar_t__ LoadImageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int MF_BITMAP ; 
 int MF_BYCOMMAND ; 
 int MF_BYPOSITION ; 
 int MF_GRAYED ; 
 int MF_HELP ; 
 int MF_POPUP ; 
 int /*<<< orphan*/  MM_TEXT ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SC_CLOSE ; 
 int /*<<< orphan*/  SC_MAXIMIZE ; 
 scalar_t__ SC_MINIMIZE ; 
 int /*<<< orphan*/  SC_MOVE ; 
 scalar_t__ SC_RESTORE ; 
 int /*<<< orphan*/  SC_SIZE ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 int /*<<< orphan*/  SM_CYSMICON ; 
 scalar_t__ SelectObject (scalar_t__,scalar_t__) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMapMode (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMenuDefaultItem (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_GETICON ; 
 scalar_t__ is_close_enabled (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static BOOL MDI_AugmentFrameMenu( HWND frame, HWND hChild )
{
    HMENU menu = GetMenu( frame );
    HMENU  	hSysPopup;
    HBITMAP hSysMenuBitmap = 0;
    HICON hIcon;
    INT nItems;
    UINT iId;

    TRACE("frame %p,child %p\n",frame,hChild);

    if( !menu ) return FALSE;
//// ReactOS start
    /* if the system buttons already exist do not add them again */
    nItems = GetMenuItemCount(menu) - 1;
    iId = GetMenuItemID(menu,nItems) ;
    if (iId == SC_RESTORE || iId == SC_CLOSE)
    {
        ERR("system buttons already exist\n");
	return FALSE;
    }
//// End
    /* create a copy of sysmenu popup and insert it into frame menu bar */
    if (!(hSysPopup = GetSystemMenu(hChild, FALSE)))
    {
        TRACE("child %p doesn't have a system menu\n", hChild);
        return FALSE;
    }

    AppendMenuW(menu, MF_HELP | MF_BITMAP,
                SC_CLOSE, is_close_enabled(hChild, hSysPopup) ?
                (LPCWSTR)HBMMENU_MBAR_CLOSE : (LPCWSTR)HBMMENU_MBAR_CLOSE_D );
    AppendMenuW(menu, MF_HELP | MF_BITMAP,
                SC_RESTORE, (LPCWSTR)HBMMENU_MBAR_RESTORE );
    AppendMenuW(menu, MF_HELP | MF_BITMAP,
                SC_MINIMIZE, (LPCWSTR)HBMMENU_MBAR_MINIMIZE ) ;

    /* The system menu is replaced by the child icon */
    hIcon = (HICON)SendMessageW(hChild, WM_GETICON, ICON_SMALL, 0);
    if (!hIcon)
        hIcon = (HICON)GetClassLongPtrW(hChild, GCLP_HICONSM);
    if (!hIcon)
        hIcon = (HICON)SendMessageW(hChild, WM_GETICON, ICON_BIG, 0);
    if (!hIcon)
        hIcon = (HICON)GetClassLongPtrW(hChild, GCLP_HICON);
    if (!hIcon)
        hIcon = LoadImageW(0, (LPWSTR)IDI_WINLOGO, IMAGE_ICON, GetSystemMetrics(SM_CXSMICON),
                           GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
    if (hIcon)
    {
      HDC hMemDC;
      HBITMAP hBitmap, hOldBitmap;
      HBRUSH hBrush;
      HDC hdc = GetDC(hChild);

      if (hdc)
      {
        int cx, cy;
        cx = GetSystemMetrics(SM_CXSMICON);
        cy = GetSystemMetrics(SM_CYSMICON);
        hMemDC = CreateCompatibleDC(hdc);
        hBitmap = CreateCompatibleBitmap(hdc, cx, cy);
        hOldBitmap = SelectObject(hMemDC, hBitmap);
        SetMapMode(hMemDC, MM_TEXT);
        hBrush = CreateSolidBrush(GetSysColor(COLOR_MENU));
        DrawIconEx(hMemDC, 0, 0, hIcon, cx, cy, 0, hBrush, DI_NORMAL);
        SelectObject (hMemDC, hOldBitmap);
        DeleteObject(hBrush);
        DeleteDC(hMemDC);
        ReleaseDC(hChild, hdc);
        hSysMenuBitmap = hBitmap;
      }
    }

    if( !InsertMenuA(menu,0,MF_BYPOSITION | MF_BITMAP | MF_POPUP,
                     (UINT_PTR)hSysPopup, (LPSTR)hSysMenuBitmap))
    {
        TRACE("not inserted\n");
	DestroyMenu(hSysPopup);
        return FALSE;
    }

    EnableMenuItem(hSysPopup, SC_SIZE, MF_BYCOMMAND | MF_GRAYED);
    EnableMenuItem(hSysPopup, SC_MOVE, MF_BYCOMMAND | MF_GRAYED);
    EnableMenuItem(hSysPopup, SC_MAXIMIZE, MF_BYCOMMAND | MF_GRAYED);
    SetMenuDefaultItem(hSysPopup, SC_CLOSE, FALSE);

    /* redraw menu */
    DrawMenuBar(frame);

    return TRUE;
}