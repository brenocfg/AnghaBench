#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WNDPROC ;
typedef  int UINT ;
struct TYPE_12__ {int /*<<< orphan*/  hwndOwner; int /*<<< orphan*/  lpfnHook; int /*<<< orphan*/  rgbResult; int /*<<< orphan*/ * lpCustColors; } ;
struct TYPE_11__ {int h; int s; int l; int nextuserdef; int /*<<< orphan*/  hwndSelf; TYPE_8__* lpcc; int /*<<< orphan*/  fullsize; int /*<<< orphan*/  updating; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  TYPE_1__ CCPRIV ;

/* Variables and functions */
 int CC_CheckDigitsInEdit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CC_EditSetHSL (TYPE_1__*) ; 
 int /*<<< orphan*/  CC_EditSetRGB (TYPE_1__*) ; 
 int /*<<< orphan*/  CC_HSLtoRGB (int,int,int) ; 
 int /*<<< orphan*/  CC_HookCallChk (TYPE_8__*) ; 
 int /*<<< orphan*/  CC_PaintCross (TYPE_1__*) ; 
 int /*<<< orphan*/  CC_PaintSelectedColor (TYPE_1__*) ; 
 int /*<<< orphan*/  CC_PaintTriangle (TYPE_1__*) ; 
 int /*<<< orphan*/  CC_PaintUserColorArray (TYPE_1__*,int,int) ; 
 void* CC_RGBtoHSL (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CC_SwitchToFullSize (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COLOROKSTRINGA ; 
 int /*<<< orphan*/  CallWindowProcA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EN_UPDATE ; 
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetBValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int const) ; 
 int GetGValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetNearestColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetRValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HELPMSGSTRINGA ; 
#define  IDCANCEL 139 
#define  IDC_COLOR_ADD 138 
#define  IDC_COLOR_DEFINE 137 
#define  IDC_COLOR_EDIT_B 136 
#define  IDC_COLOR_EDIT_G 135 
#define  IDC_COLOR_EDIT_H 134 
#define  IDC_COLOR_EDIT_L 133 
#define  IDC_COLOR_EDIT_R 132 
#define  IDC_COLOR_EDIT_S 131 
#define  IDC_COLOR_RES 130 
#define  IDOK 129 
 int LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int RegisterWindowMessageA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_COMMAND ; 
 int /*<<< orphan*/  psh15 ; 
#define  pshHelp 128 

__attribute__((used)) static LRESULT CC_WMCommand(CCPRIV *lpp, WPARAM wParam, LPARAM lParam, WORD notifyCode, HWND hwndCtl)
{
    int  r, g, b, i, xx;
    UINT cokmsg;
    HDC hdc;
    COLORREF *cr;

    TRACE("CC_WMCommand wParam=%lx lParam=%lx\n", wParam, lParam);
    switch (LOWORD(wParam))
    {
        case IDC_COLOR_EDIT_R:  /* edit notify RGB */
        case IDC_COLOR_EDIT_G:
        case IDC_COLOR_EDIT_B:
	       if (notifyCode == EN_UPDATE && !lpp->updating)
			 {
			   i = CC_CheckDigitsInEdit(hwndCtl, 255);
			   r = GetRValue(lpp->lpcc->rgbResult);
			   g = GetGValue(lpp->lpcc->rgbResult);
			   b= GetBValue(lpp->lpcc->rgbResult);
			   xx = 0;
			   switch (LOWORD(wParam))
			   {
			    case IDC_COLOR_EDIT_R: if ((xx = (i != r))) r = i; break;
			    case IDC_COLOR_EDIT_G: if ((xx = (i != g))) g = i; break;
			    case IDC_COLOR_EDIT_B: if ((xx = (i != b))) b = i; break;
			   }
			   if (xx) /* something has changed */
			   {
			    lpp->lpcc->rgbResult = RGB(r, g, b);
			    CC_PaintSelectedColor(lpp);
			    lpp->h = CC_RGBtoHSL('H', lpp->lpcc->rgbResult);
			    lpp->s = CC_RGBtoHSL('S', lpp->lpcc->rgbResult);
			    lpp->l = CC_RGBtoHSL('L', lpp->lpcc->rgbResult);
			    CC_EditSetHSL(lpp);
			    CC_PaintCross(lpp);
			    CC_PaintTriangle(lpp);
			   }
			 }
		 break;

        case IDC_COLOR_EDIT_H:  /* edit notify HSL */
        case IDC_COLOR_EDIT_S:
        case IDC_COLOR_EDIT_L:
	       if (notifyCode == EN_UPDATE && !lpp->updating)
			 {
			   i = CC_CheckDigitsInEdit(hwndCtl , LOWORD(wParam) == IDC_COLOR_EDIT_H ? 239 : 240);
			   xx = 0;
			   switch (LOWORD(wParam))
			   {
			    case IDC_COLOR_EDIT_H: if ((xx = ( i != lpp->h))) lpp->h = i; break;
			    case IDC_COLOR_EDIT_S: if ((xx = ( i != lpp->s))) lpp->s = i; break;
			    case IDC_COLOR_EDIT_L: if ((xx = ( i != lpp->l))) lpp->l = i; break;
			   }
			   if (xx) /* something has changed */
			   {
			    lpp->lpcc->rgbResult = CC_HSLtoRGB(lpp->h, lpp->s, lpp->l);
			    CC_PaintSelectedColor(lpp);
			    CC_EditSetRGB(lpp);
			    CC_PaintCross(lpp);
			    CC_PaintTriangle(lpp);
			   }
			 }
	       break;

        case IDC_COLOR_DEFINE:
               CC_SwitchToFullSize(lpp, &lpp->fullsize);
	       SetFocus( GetDlgItem(lpp->hwndSelf, IDC_COLOR_EDIT_H));
	       break;

        case IDC_COLOR_ADD:    /* add colors ... column by column */
               cr = lpp->lpcc->lpCustColors;
               cr[(lpp->nextuserdef % 2) * 8 + lpp->nextuserdef / 2] = lpp->lpcc->rgbResult;
               if (++lpp->nextuserdef == 16)
		   lpp->nextuserdef = 0;
	       CC_PaintUserColorArray(lpp, 2, 8);
	       break;

        case IDC_COLOR_RES:              /* resulting color */
	       hdc = GetDC(lpp->hwndSelf);
	       lpp->lpcc->rgbResult = GetNearestColor(hdc, lpp->lpcc->rgbResult);
	       ReleaseDC(lpp->hwndSelf, hdc);
	       CC_EditSetRGB(lpp);
	       CC_PaintSelectedColor(lpp);
	       lpp->h = CC_RGBtoHSL('H', lpp->lpcc->rgbResult);
	       lpp->s = CC_RGBtoHSL('S', lpp->lpcc->rgbResult);
	       lpp->l = CC_RGBtoHSL('L', lpp->lpcc->rgbResult);
	       CC_EditSetHSL(lpp);
	       CC_PaintCross(lpp);
	       CC_PaintTriangle(lpp);
	       break;

	  case pshHelp:           /* Help! */ /* The Beatles, 1965  ;-) */
	       i = RegisterWindowMessageA(HELPMSGSTRINGA);
                   if (lpp->lpcc->hwndOwner)
		       SendMessageA(lpp->lpcc->hwndOwner, i, 0, (LPARAM)lpp->lpcc);
                   if ( CC_HookCallChk(lpp->lpcc))
		       CallWindowProcA( (WNDPROC) lpp->lpcc->lpfnHook, lpp->hwndSelf,
		          WM_COMMAND, psh15, (LPARAM)lpp->lpcc);
	       break;

          case IDOK :
		cokmsg = RegisterWindowMessageA(COLOROKSTRINGA);
		    if (lpp->lpcc->hwndOwner)
			if (SendMessageA(lpp->lpcc->hwndOwner, cokmsg, 0, (LPARAM)lpp->lpcc))
			break;    /* do NOT close */
		EndDialog(lpp->hwndSelf, 1) ;
		return TRUE ;

	  case IDCANCEL :
		EndDialog(lpp->hwndSelf, 0) ;
		return TRUE ;

       }
       return FALSE;
}