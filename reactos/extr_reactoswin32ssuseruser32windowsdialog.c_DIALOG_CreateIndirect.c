#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mon_info ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  void* UINT ;
struct TYPE_27__ {scalar_t__ hUserFont; void* flags; void* yBaseUnit; void* xBaseUnit; scalar_t__ hMenu; scalar_t__ hwndFocus; } ;
struct TYPE_26__ {int style; int pointSize; int cx; int cy; int x; int y; scalar_t__ helpId; int /*<<< orphan*/  exStyle; int /*<<< orphan*/  caption; int /*<<< orphan*/  className; int /*<<< orphan*/  faceName; int /*<<< orphan*/  italic; int /*<<< orphan*/  weight; scalar_t__ menuName; } ;
struct TYPE_20__ {int left; int right; int top; int bottom; } ;
struct TYPE_25__ {int cbSize; TYPE_1__ rcWork; } ;
struct TYPE_24__ {int cbSize; int /*<<< orphan*/  lfMessageFont; } ;
struct TYPE_23__ {int x; int y; } ;
struct TYPE_22__ {int left; int top; int right; int bottom; } ;
struct TYPE_21__ {int cx; int cy; } ;
typedef  TYPE_2__ SIZE ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_4__ POINT ;
typedef  TYPE_5__ NONCLIENTMETRICSW ;
typedef  TYPE_6__ MONITORINFO ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  int /*<<< orphan*/ * LPCSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ HMONITOR ;
typedef  scalar_t__ HMENU ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_7__ DLG_TEMPLATE ;
typedef  scalar_t__ DLGPROC ;
typedef  TYPE_8__ DIALOGINFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustWindowRectEx (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHILDID_SELF ; 
 int /*<<< orphan*/  CP_ACP ; 
 int CW_USEDEFAULT ; 
 int CW_USEDEFAULT16 ; 
 int /*<<< orphan*/  ClientToScreen (scalar_t__,TYPE_4__*) ; 
 scalar_t__ CreateFontIndirectW (int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFontW (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateWindowExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEFAULT_CHARSET ; 
 scalar_t__ DIALOG_CreateControls32 (scalar_t__,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIALOG_ParseTemplate32 (int /*<<< orphan*/ ,TYPE_7__*) ; 
 TYPE_8__* DIALOG_get_info (scalar_t__,int /*<<< orphan*/ ) ; 
 int DLGC_HASSETSEL ; 
 int DS_3DLOOK ; 
 int DS_ABSALIGN ; 
 int DS_CENTER ; 
 int DS_CENTERMOUSE ; 
 int DS_CONTROL ; 
 int DS_MODALFRAME ; 
 int DS_SETFONT ; 
 int /*<<< orphan*/  DWLP_DLGPROC ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  DestroyMenu (scalar_t__) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  EVENT_SYSTEM_DIALOGEND ; 
 int /*<<< orphan*/  EVENT_SYSTEM_DIALOGSTART ; 
 int /*<<< orphan*/  EnableWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FF_DONTCARE ; 
 int /*<<< orphan*/  GA_ROOT ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int GdiGetCharDimensions (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ GetActiveWindow () ; 
 scalar_t__ GetAncestor (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCursorPos (TYPE_4__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ GetDesktopWindow () ; 
 void* GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDialogBaseUnits () ; 
 int /*<<< orphan*/  GetMonitorInfoW (scalar_t__,TYPE_6__*) ; 
 scalar_t__ GetNextDlgGroupItem (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetNextDlgTabItem (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetParent (scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int GetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ) ; 
 int GetWindowLongW (scalar_t__,int /*<<< orphan*/ ) ; 
 void* HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_INTRESOURCE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IntNotifyWinEvent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsWindow (scalar_t__) ; 
 scalar_t__ IsWindowEnabled (scalar_t__) ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 void* LOWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ LoadMenuW (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MAKEWPARAM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXLONG ; 
 int /*<<< orphan*/  MONITOR_DEFAULTTOPRIMARY ; 
 scalar_t__ MonitorFromPoint (TYPE_4__,int /*<<< orphan*/ ) ; 
 scalar_t__ MonitorFromRect (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MonitorFromWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int MulDiv (int,void*,int) ; 
 scalar_t__ NtUserGetThreadState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtUserQueryWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJID_WINDOW ; 
 int /*<<< orphan*/  PROOF_QUALITY ; 
 int /*<<< orphan*/  QUERY_WINDOW_FOREGROUND ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXDLGFRAME ; 
 int /*<<< orphan*/  SM_CYDLGFRAME ; 
 int /*<<< orphan*/  SPI_GETNONCLIENTMETRICS ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetFocus (scalar_t__) ; 
 int /*<<< orphan*/  SetForegroundWindow (scalar_t__) ; 
 int /*<<< orphan*/  SetRect (TYPE_3__*,int,int,int,int) ; 
 int /*<<< orphan*/  SetWindowContextHelpId (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SetWindowLongPtrA (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SystemParametersInfoW (int /*<<< orphan*/ ,int,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREADSTATE_FOREGROUNDTHREAD ; 
 int /*<<< orphan*/  TRACE (char*,void*,void*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UIS_INITIALIZE ; 
 int /*<<< orphan*/  UpdateWindow (scalar_t__) ; 
 int /*<<< orphan*/  WM_CHANGEUISTATE ; 
 int /*<<< orphan*/  WM_GETDLGCODE ; 
 int /*<<< orphan*/  WM_INITDIALOG ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int WS_CAPTION ; 
 int WS_CHILD ; 
 int /*<<< orphan*/  WS_EX_CONTROLPARENT ; 
 int /*<<< orphan*/  WS_EX_DLGMODALFRAME ; 
 int WS_POPUP ; 
 int WS_SYSMENU ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HWND DIALOG_CreateIndirect( HINSTANCE hInst, LPCVOID dlgTemplate,
                                   HWND owner, DLGPROC dlgProc, LPARAM param,
                                   BOOL unicode, HWND *modal_owner )
{
    HWND hwnd;
    RECT rect;
    POINT pos;
    SIZE size;
    DLG_TEMPLATE template;
    DIALOGINFO * dlgInfo = NULL;
    DWORD units = GetDialogBaseUnits();
    HWND disabled_owner = NULL;
    HMENU hMenu = 0;
    HFONT hUserFont = 0;
    UINT flags = 0;
    UINT xBaseUnit = LOWORD(units);
    UINT yBaseUnit = HIWORD(units);

      /* Parse dialog template */

    if (!dlgTemplate) return 0;
    dlgTemplate = DIALOG_ParseTemplate32( dlgTemplate, &template );

      /* Load menu */

    if (template.menuName) hMenu = LoadMenuW( hInst, template.menuName );

      /* Create custom font if needed */

    if (template.style & DS_SETFONT)
    {
        HDC dc = GetDC(0);

        if (template.pointSize == 0x7fff)
        {
            /* We get the message font from the non-client metrics */
            NONCLIENTMETRICSW ncMetrics;

            ncMetrics.cbSize = sizeof(NONCLIENTMETRICSW);
            if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS,
                                      sizeof(NONCLIENTMETRICSW), &ncMetrics, 0))
            {
                hUserFont = CreateFontIndirectW( &ncMetrics.lfMessageFont );
            }
        }
        else
        {
            /* We convert the size to pixels and then make it -ve.  This works
             * for both +ve and -ve template.pointSize */
            int pixels = MulDiv(template.pointSize, GetDeviceCaps(dc , LOGPIXELSY), 72);
            hUserFont = CreateFontW( -pixels, 0, 0, 0, template.weight,
                                              template.italic, FALSE, FALSE, DEFAULT_CHARSET, 0, 0,
                                              PROOF_QUALITY, FF_DONTCARE,
                                              template.faceName );
        }

        if (hUserFont)
        {
            SIZE charSize;
            HFONT hOldFont = SelectObject( dc, hUserFont );
            charSize.cx = GdiGetCharDimensions( dc, NULL, &charSize.cy );
            if (charSize.cx)
            {
                xBaseUnit = charSize.cx;
                yBaseUnit = charSize.cy;
            }
            SelectObject( dc, hOldFont );
        }
        ReleaseDC(0, dc);
        TRACE("units = %d,%d\n", xBaseUnit, yBaseUnit );
    }

    /* Create dialog main window */

    SetRect(&rect, 0, 0, MulDiv(template.cx, xBaseUnit, 4), MulDiv(template.cy, yBaseUnit, 8));
    if (template.style & DS_CONTROL)
        template.style &= ~(WS_CAPTION|WS_SYSMENU);
    template.style |= DS_3DLOOK;
    if (template.style & DS_MODALFRAME)
        template.exStyle |= WS_EX_DLGMODALFRAME;
    if ((template.style & DS_CONTROL) || !(template.style & WS_CHILD))
        template.exStyle |= WS_EX_CONTROLPARENT;
    AdjustWindowRectEx( &rect, template.style, (hMenu != 0), template.exStyle );
    pos.x = rect.left;
    pos.y = rect.top;
    size.cx = rect.right - rect.left;
    size.cy = rect.bottom - rect.top;

    if (template.x == CW_USEDEFAULT16)
    {
        pos.x = pos.y = CW_USEDEFAULT;
    }
    else
    {
        HMONITOR monitor = 0;
        MONITORINFO mon_info;

        mon_info.cbSize = sizeof(mon_info);
        if (template.style & DS_CENTER)
        {
            monitor = MonitorFromWindow( owner ? owner : GetActiveWindow(), MONITOR_DEFAULTTOPRIMARY );
            GetMonitorInfoW( monitor, &mon_info );
            pos.x = (mon_info.rcWork.left + mon_info.rcWork.right - size.cx) / 2;
            pos.y = (mon_info.rcWork.top + mon_info.rcWork.bottom - size.cy) / 2;
        }
        else if (template.style & DS_CENTERMOUSE)
        {
            GetCursorPos( &pos );
            monitor = MonitorFromPoint( pos, MONITOR_DEFAULTTOPRIMARY );
            GetMonitorInfoW( monitor, &mon_info );
        }
        else
        {
            pos.x += MulDiv(template.x, xBaseUnit, 4);
            pos.y += MulDiv(template.y, yBaseUnit, 8);
            //
            // REACTOS : Need an owner to be passed!!!
            //
            if (!(template.style & (WS_CHILD|DS_ABSALIGN)) && owner ) ClientToScreen( owner, &pos );
        }
        if ( !(template.style & WS_CHILD) )
        {
            INT dX, dY;

            /* try to fit it into the desktop */

            if (!monitor)
            {
                SetRect( &rect, pos.x, pos.y, pos.x + size.cx, pos.y + size.cy );
                monitor = MonitorFromRect( &rect, MONITOR_DEFAULTTOPRIMARY );
                GetMonitorInfoW( monitor, &mon_info );
            }
            if ((dX = pos.x + size.cx + GetSystemMetrics(SM_CXDLGFRAME) - mon_info.rcWork.right) > 0)
                pos.x -= dX;
            if ((dY = pos.y + size.cy + GetSystemMetrics(SM_CYDLGFRAME) - mon_info.rcWork.bottom) > 0)
                pos.y -= dY;
            if( pos.x < mon_info.rcWork.left ) pos.x = mon_info.rcWork.left;
            if( pos.y < mon_info.rcWork.top ) pos.y = mon_info.rcWork.top;
        }
    }

    if (modal_owner && owner)
    {
        HWND parent = NULL;
        /*
         * Owner needs to be top level window. We need to duplicate the logic from server,
         * because we need to disable it before creating dialog window. Note that we do that
         * even if dialog has WS_CHILD, but only for modal dialogs, which matched what
         * Windows does.
         */
        while ((GetWindowLongW( owner, GWL_STYLE ) & (WS_POPUP|WS_CHILD)) == WS_CHILD)
        {
            parent = GetParent( owner );
            if (!parent || parent == GetDesktopWindow()) break;
            owner = parent;
        }
        ////// Wine'ie babies need to fix your code!!!! CORE-11633
        if (!parent) parent = GetAncestor( owner, GA_ROOT );

        if (parent)
        {
           owner = parent;

           if (IsWindowEnabled( owner ))
           {
               disabled_owner = owner;
               EnableWindow( disabled_owner, FALSE );
           }
        }
        *modal_owner = owner;
    }

    if (unicode)
    {
        hwnd = CreateWindowExW(template.exStyle, template.className, template.caption,
                               template.style & ~WS_VISIBLE, pos.x, pos.y, size.cx, size.cy,
                               owner, hMenu, hInst, NULL );
    }
    else
    {
        LPCSTR class = (LPCSTR)template.className;
        LPCSTR caption = (LPCSTR)template.caption;
        LPSTR class_tmp = NULL;
        LPSTR caption_tmp = NULL;

        if (!IS_INTRESOURCE(class))
        {
            DWORD len = WideCharToMultiByte( CP_ACP, 0, template.className, -1, NULL, 0, NULL, NULL );
            class_tmp = HeapAlloc( GetProcessHeap(), 0, len );
            WideCharToMultiByte( CP_ACP, 0, template.className, -1, class_tmp, len, NULL, NULL );
            class = class_tmp;
        }
        if (!IS_INTRESOURCE(caption))
        {
            DWORD len = WideCharToMultiByte( CP_ACP, 0, template.caption, -1, NULL, 0, NULL, NULL );
            caption_tmp = HeapAlloc( GetProcessHeap(), 0, len );
            WideCharToMultiByte( CP_ACP, 0, template.caption, -1, caption_tmp, len, NULL, NULL );
            caption = caption_tmp;
        }
        hwnd = CreateWindowExA(template.exStyle, class, caption,
                               template.style & ~WS_VISIBLE, pos.x, pos.y, size.cx, size.cy,
                               owner, hMenu, hInst, NULL );
        HeapFree( GetProcessHeap(), 0, class_tmp );
        HeapFree( GetProcessHeap(), 0, caption_tmp );
    }

    if (!hwnd)
    {
        if (hUserFont) DeleteObject( hUserFont );
        if (hMenu) DestroyMenu( hMenu );
        if (disabled_owner) EnableWindow( disabled_owner, TRUE );
        return 0;
    }

    /* moved this from the top of the method to here as DIALOGINFO structure
    will be valid only after WM_CREATE message has been handled in DefDlgProc
    All the members of the structure get filled here using temp variables */
    dlgInfo = DIALOG_get_info( hwnd, TRUE );
    // ReactOS
    if (dlgInfo == NULL)
    {
        if (hUserFont) DeleteObject( hUserFont );
        if (hMenu) DestroyMenu( hMenu );
        if (disabled_owner) EnableWindow( disabled_owner, TRUE );
        return 0;
    }
    //
    dlgInfo->hwndFocus   = 0;
    dlgInfo->hUserFont   = hUserFont;
    dlgInfo->hMenu       = hMenu;
    dlgInfo->xBaseUnit   = xBaseUnit;
    dlgInfo->yBaseUnit   = yBaseUnit;
    dlgInfo->flags       = flags;

    if (template.helpId) SetWindowContextHelpId( hwnd, template.helpId );

    if (unicode) SetWindowLongPtrW( hwnd, DWLP_DLGPROC, (ULONG_PTR)dlgProc );
    else SetWindowLongPtrA( hwnd, DWLP_DLGPROC, (ULONG_PTR)dlgProc );

    if (dlgProc && dlgInfo->hUserFont)
        SendMessageW( hwnd, WM_SETFONT, (WPARAM)dlgInfo->hUserFont, 0 );

    /* Create controls */

    if (DIALOG_CreateControls32( hwnd, dlgTemplate, &template, hInst, unicode ))
    {
        /* Send initialisation messages and set focus */

        if (dlgProc)
        {
            HWND focus = GetNextDlgTabItem( hwnd, 0, FALSE );
            if (!focus) focus = GetNextDlgGroupItem( hwnd, 0, FALSE );
            if (SendMessageW( hwnd, WM_INITDIALOG, (WPARAM)focus, param ) && IsWindow( hwnd ) &&
                ((~template.style & DS_CONTROL) || (template.style & WS_VISIBLE)))
            {
                /* By returning TRUE, app has requested a default focus assignment.
                 * WM_INITDIALOG may have changed the tab order, so find the first
                 * tabstop control again. */
                focus = GetNextDlgTabItem( hwnd, 0, FALSE );
                if (!focus) focus = GetNextDlgGroupItem( hwnd, 0, FALSE );
                if (focus)
                {
                    if (SendMessageW( focus, WM_GETDLGCODE, 0, 0 ) & DLGC_HASSETSEL)
                        SendMessageW( focus, EM_SETSEL, 0, MAXLONG );
                    SetFocus( focus );
                }
            }
//// ReactOS see 43396, Fixes setting focus on Open and Close dialogs to the FileName edit control in OpenOffice.
//// This now breaks test_SaveRestoreFocus.
            //DEFDLG_SaveFocus( hwnd );
////
        }
//// ReactOS Rev 30613 & 30644
        if (!(GetWindowLongPtrW( hwnd, GWL_STYLE ) & WS_CHILD))
            SendMessageW( hwnd, WM_CHANGEUISTATE, MAKEWPARAM(UIS_INITIALIZE, 0), 0);
////
        if (template.style & WS_VISIBLE && !(GetWindowLongPtrW( hwnd, GWL_STYLE ) & WS_VISIBLE))
        {
           ShowWindow( hwnd, SW_SHOWNORMAL );   /* SW_SHOW doesn't always work */
           UpdateWindow( hwnd );
           IntNotifyWinEvent(EVENT_SYSTEM_DIALOGSTART, hwnd, OBJID_WINDOW, CHILDID_SELF, 0);
        }
        return hwnd;
    }
    if (disabled_owner) EnableWindow( disabled_owner, TRUE );
    IntNotifyWinEvent(EVENT_SYSTEM_DIALOGEND, hwnd, OBJID_WINDOW, CHILDID_SELF, 0);
    if( IsWindow(hwnd) )
    {
      DestroyWindow( hwnd );
      //// ReactOS
      if (owner)
      {  ERR("DIALOG_CreateIndirect 1\n");
         if ( NtUserGetThreadState(THREADSTATE_FOREGROUNDTHREAD) && // Rule #1.
             !NtUserQueryWindow(owner, QUERY_WINDOW_FOREGROUND) )
         { ERR("DIALOG_CreateIndirect SFW\n");
            SetForegroundWindow(owner);
         }
      }
      ////
    }
    return 0;
}