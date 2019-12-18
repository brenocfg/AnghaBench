#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_13__ {int /*<<< orphan*/  cy; } ;
struct TYPE_12__ {int /*<<< orphan*/  hInstance; TYPE_6__ spaceSize; scalar_t__ hfont; int /*<<< orphan*/  hmdiclient; } ;
struct TYPE_11__ {int lStructSize; int Flags; int nSizeMax; scalar_t__ nSizeMin; int /*<<< orphan*/  nFontType; int /*<<< orphan*/ * lpszStyle; int /*<<< orphan*/  hInstance; int /*<<< orphan*/ * lpTemplateName; int /*<<< orphan*/ * lpfnHook; scalar_t__ lCustData; int /*<<< orphan*/  rgbColors; int /*<<< orphan*/ * lpLogFont; int /*<<< orphan*/ * hDC; scalar_t__ hwndOwner; } ;
struct TYPE_9__ {int /*<<< orphan*/  hwnd; } ;
struct TYPE_8__ {int /*<<< orphan*/  hwnd; } ;
struct TYPE_10__ {TYPE_2__ right; TYPE_1__ left; } ;
typedef  int /*<<< orphan*/  LOGFONTW ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_3__ ChildWnd ;
typedef  TYPE_4__ CHOOSEFONTW ;

/* Variables and functions */
 int BUFFER_LEN ; 
 int CF_FORCEFONTEXIST ; 
 int CF_INITTOLOGFONTSTRUCT ; 
 int CF_LIMITSIZE ; 
 int CF_NOSCRIPTSEL ; 
 int CF_NOVERTFONTS ; 
 int CF_SCREENFONTS ; 
 scalar_t__ ChooseFontW (TYPE_4__*) ; 
 scalar_t__ CommDlgExtendedError () ; 
 scalar_t__ CreateFontIndirectW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  GWLP_USERDATA ; 
 int /*<<< orphan*/  GW_CHILD ; 
 int /*<<< orphan*/  GW_HWNDNEXT ; 
 int /*<<< orphan*/  GetDC (scalar_t__) ; 
 scalar_t__ GetNextWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetObjectW (scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTextExtentPoint32W (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_6__*) ; 
 scalar_t__ GetWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_5__ Globals ; 
 int /*<<< orphan*/  IDS_FONT_SEL_DLG_NAME ; 
 int /*<<< orphan*/  IDS_FONT_SEL_ERROR ; 
 scalar_t__ IMAGE_HEIGHT ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_SETITEMHEIGHT ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MB_OK ; 
 int /*<<< orphan*/  MessageBoxW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIMULATED_FONTTYPE ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sSpace ; 

__attribute__((used)) static inline void choose_font(HWND hwnd)
{
        WCHAR dlg_name[BUFFER_LEN], dlg_info[BUFFER_LEN];
        CHOOSEFONTW chFont;
        LOGFONTW lFont;

        HDC hdc = GetDC(hwnd);

        GetObjectW(Globals.hfont, sizeof(LOGFONTW), &lFont);

        chFont.lStructSize = sizeof(CHOOSEFONTW);
        chFont.hwndOwner = hwnd;
        chFont.hDC = NULL;
        chFont.lpLogFont = &lFont;
        chFont.Flags = CF_SCREENFONTS | CF_FORCEFONTEXIST | CF_LIMITSIZE | CF_NOSCRIPTSEL | CF_INITTOLOGFONTSTRUCT | CF_NOVERTFONTS;
        chFont.rgbColors = RGB(0,0,0);
        chFont.lCustData = 0;
        chFont.lpfnHook = NULL;
        chFont.lpTemplateName = NULL;
        chFont.hInstance = Globals.hInstance;
        chFont.lpszStyle = NULL;
        chFont.nFontType = SIMULATED_FONTTYPE;
        chFont.nSizeMin = 0;
        chFont.nSizeMax = 24;

        if (ChooseFontW(&chFont)) {
                HWND childWnd;
                HFONT hFontOld;

                DeleteObject(Globals.hfont);
                Globals.hfont = CreateFontIndirectW(&lFont);
                hFontOld = SelectObject(hdc, Globals.hfont);
                GetTextExtentPoint32W(hdc, sSpace, 1, &Globals.spaceSize);

                /* change font in all open child windows */
                for(childWnd=GetWindow(Globals.hmdiclient,GW_CHILD); childWnd; childWnd=GetNextWindow(childWnd,GW_HWNDNEXT)) {
                        ChildWnd* child = (ChildWnd*) GetWindowLongPtrW(childWnd, GWLP_USERDATA);
                        SendMessageW(child->left.hwnd, WM_SETFONT, (WPARAM)Globals.hfont, TRUE);
                        SendMessageW(child->right.hwnd, WM_SETFONT, (WPARAM)Globals.hfont, TRUE);
                        SendMessageW(child->left.hwnd, LB_SETITEMHEIGHT, 1, max(Globals.spaceSize.cy,IMAGE_HEIGHT+3));
                        SendMessageW(child->right.hwnd, LB_SETITEMHEIGHT, 1, max(Globals.spaceSize.cy,IMAGE_HEIGHT+3));
                        InvalidateRect(child->left.hwnd, NULL, TRUE);
                        InvalidateRect(child->right.hwnd, NULL, TRUE);
                }

                SelectObject(hdc, hFontOld);
        }
        else if (CommDlgExtendedError()) {
                LoadStringW(Globals.hInstance, IDS_FONT_SEL_DLG_NAME, dlg_name, BUFFER_LEN);
                LoadStringW(Globals.hInstance, IDS_FONT_SEL_ERROR, dlg_info, BUFFER_LEN);
                MessageBoxW(hwnd, dlg_info, dlg_name, MB_OK);
        }

        ReleaseDC(hwnd, hdc);
}