#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WORD ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_9__ {int /*<<< orphan*/  idResult; scalar_t__ hUserFont; int /*<<< orphan*/  yBaseUnit; int /*<<< orphan*/  xBaseUnit; } ;
struct TYPE_8__ {int style; int exStyle; scalar_t__ windowName; scalar_t__ className; scalar_t__ windowNameFree; scalar_t__ data; scalar_t__ id; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_7__ {int style; int /*<<< orphan*/  dialogEx; int /*<<< orphan*/  nbItems; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  scalar_t__ LPCSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ DLG_TEMPLATE ;
typedef  TYPE_2__ DLG_CONTROL_INFO ;
typedef  TYPE_3__ DIALOGINFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BM_SETSTYLE ; 
 int /*<<< orphan*/  BS_PUSHBUTTON ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/ * CreateWindowExA (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateWindowExW (int,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ DIALOG_GetControl32 (int /*<<< orphan*/  const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int DLGC_DEFPUSHBUTTON ; 
 int DS_NOFAILCREATE ; 
 scalar_t__ FALSE ; 
 TYPE_3__* GETDLGINFO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetWindowLongPtrA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_INTRESOURCE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MulDiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SendMessageW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_GETDLGCODE ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int WS_BORDER ; 
 int WS_CHILD ; 
 int WS_EX_CLIENTEDGE ; 
 int WS_EX_NOPARENTNOTIFY ; 
 int WS_POPUP ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__) ; 

__attribute__((used)) static BOOL DIALOG_CreateControls32( HWND hwnd, LPCSTR template, const DLG_TEMPLATE *dlgTemplate,
                                     HINSTANCE hInst, BOOL unicode )
{
    DIALOGINFO * dlgInfo;
    DLG_CONTROL_INFO info;
    HWND hwndCtrl, hwndDefButton = 0;
    INT items = dlgTemplate->nbItems;

    if (!(dlgInfo = GETDLGINFO(hwnd))) return FALSE;

    TRACE(" BEGIN\n" );
    while (items--)
    {
        template = (LPCSTR)DIALOG_GetControl32( (const WORD *)template, &info,
                                                dlgTemplate->dialogEx );
        info.style &= ~WS_POPUP;
        info.style |= WS_CHILD;

        if (info.style & WS_BORDER)
        {
            info.style &= ~WS_BORDER;
            info.exStyle |= WS_EX_CLIENTEDGE;
        }

        if (unicode)
        {
            hwndCtrl = CreateWindowExW( info.exStyle | WS_EX_NOPARENTNOTIFY,
                                        info.className, info.windowName,
                                        info.style | WS_CHILD,
                                        MulDiv(info.x, dlgInfo->xBaseUnit, 4),
                                        MulDiv(info.y, dlgInfo->yBaseUnit, 8),
                                        MulDiv(info.cx, dlgInfo->xBaseUnit, 4),
                                        MulDiv(info.cy, dlgInfo->yBaseUnit, 8),
                                        hwnd, (HMENU)(ULONG_PTR)info.id,
                                        hInst, (LPVOID)info.data );
        }
        else
        {
            LPSTR class = (LPSTR)info.className;
            LPSTR caption = (LPSTR)info.windowName;

            if (!IS_INTRESOURCE(class))
            {
                DWORD len = WideCharToMultiByte( CP_ACP, 0, info.className, -1, NULL, 0, NULL, NULL );
                class = HeapAlloc( GetProcessHeap(), 0, len );
                if (class != NULL)
                    WideCharToMultiByte( CP_ACP, 0, info.className, -1, class, len, NULL, NULL );
            }
            if (!IS_INTRESOURCE(caption))
            {
                DWORD len = WideCharToMultiByte( CP_ACP, 0, info.windowName, -1, NULL, 0, NULL, NULL );
                caption = HeapAlloc( GetProcessHeap(), 0, len );
                if (caption != NULL)
                    WideCharToMultiByte( CP_ACP, 0, info.windowName, -1, caption, len, NULL, NULL );
            }

            if (class != NULL && caption != NULL)
            {
                hwndCtrl = CreateWindowExA( info.exStyle | WS_EX_NOPARENTNOTIFY,
                                            class, caption, info.style | WS_CHILD,
                                            MulDiv(info.x, dlgInfo->xBaseUnit, 4),
                                            MulDiv(info.y, dlgInfo->yBaseUnit, 8),
                                            MulDiv(info.cx, dlgInfo->xBaseUnit, 4),
                                            MulDiv(info.cy, dlgInfo->yBaseUnit, 8),
                                            hwnd, (HMENU)(ULONG_PTR)info.id,
                                            hInst, (LPVOID)info.data );
            }
            else
                hwndCtrl = NULL;
            if (!IS_INTRESOURCE(class)) HeapFree( GetProcessHeap(), 0, class );
            if (!IS_INTRESOURCE(caption)) HeapFree( GetProcessHeap(), 0, caption );
        }

        if (info.windowNameFree)
        {
            HeapFree( GetProcessHeap(), 0, (LPVOID)info.windowName );
        }

        if (!hwndCtrl)
        {
            WARN("control %s %s creation failed\n", debugstr_w(info.className),
                  debugstr_w(info.windowName));
            if (dlgTemplate->style & DS_NOFAILCREATE) continue;
            return FALSE;
        }

        /* Send initialisation messages to the control */
        if (dlgInfo->hUserFont) SendMessageW( hwndCtrl, WM_SETFONT,
                                             (WPARAM)dlgInfo->hUserFont, 0 );
        if (SendMessageW(hwndCtrl, WM_GETDLGCODE, 0, 0) & DLGC_DEFPUSHBUTTON)
        {
            /* If there's already a default push-button, set it back */
            /* to normal and use this one instead. */
            if (hwndDefButton)
                SendMessageW( hwndDefButton, BM_SETSTYLE, BS_PUSHBUTTON, FALSE );
            hwndDefButton = hwndCtrl;
            dlgInfo->idResult = GetWindowLongPtrA( hwndCtrl, GWLP_ID );
        }
    }
    TRACE(" END\n" );
    return TRUE;
}