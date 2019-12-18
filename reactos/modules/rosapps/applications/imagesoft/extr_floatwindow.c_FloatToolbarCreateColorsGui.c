#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* fltColors; } ;
struct TYPE_7__ {double right; int bottom; } ;
struct TYPE_6__ {int /*<<< orphan*/  hSelf; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* PMAIN_WND_INFO ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BM_SETIMAGE ; 
 int BS_BITMAP ; 
 int CBS_DROPDOWN ; 
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/ * CreateWindowEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FloatWindowPaintColorPicker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FloatWindowPaintHueSlider (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDB_COLORSMORE ; 
 int /*<<< orphan*/  IMAGE_BITMAP ; 
 int LR_LOADMAP3DCOLORS ; 
 int LR_LOADTRANSPARENT ; 
 scalar_t__ LoadImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MakeFlatCombo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TextOut (int /*<<< orphan*/ ,int,int,scalar_t__,int) ; 
 int /*<<< orphan*/  WC_BUTTON ; 
 int /*<<< orphan*/  WC_COMBOBOX ; 
 int /*<<< orphan*/  WC_STATIC ; 
 int WS_CHILD ; 
 int /*<<< orphan*/  WS_EX_STATICEDGE ; 
 int WS_VISIBLE ; 
 scalar_t__ _T (char*) ; 
 int /*<<< orphan*/  hInstance ; 

BOOL
FloatToolbarCreateColorsGui(PMAIN_WND_INFO Info)
{
    HWND hColorPicker;
    HWND hHueSlider;
    HWND hMouseButton;
    HWND hMore;
    RECT rect;
    HBITMAP hMoreBitmap;

    GetClientRect(Info->fltColors->hSelf,
                  &rect);

    hColorPicker = CreateWindowEx(0,
                                  WC_STATIC,
                                  NULL,
                                  WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
                                  2,
                                  2,
                                  (int) (rect.right * 0.65),
                                  rect.bottom - 2,
                                  Info->fltColors->hSelf,
                                  NULL,
                                  hInstance,
                                  NULL);
    if (hColorPicker == NULL)
        return FALSE;

    hHueSlider = CreateWindowEx(0,
                                WC_STATIC,
                                NULL,
                                WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
                                145,
                                35,
                                25,
                                135,
                                Info->fltColors->hSelf,
                                NULL,
                                hInstance,
                                NULL);
    if (hHueSlider == NULL)
        return FALSE;

    hMouseButton = CreateWindowEx(0,
                                  WC_COMBOBOX,
                                  NULL,
                                  WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
                                  118, 5, 75, 25,
                                  Info->fltColors->hSelf,
                                  NULL,
                                  hInstance,
                                  NULL);
    if (hMouseButton == NULL)
        return FALSE;

    MakeFlatCombo(hMouseButton);

    /* temp, just testing */
    SendMessage(hMouseButton, CB_ADDSTRING, 0, (LPARAM)_T("Primary"));
    SendMessage(hMouseButton, CB_ADDSTRING, 0, (LPARAM)_T("Secondary"));
    SendMessage(hMouseButton, CB_SETCURSEL, 0, 0);


    hMore = CreateWindowEx(WS_EX_STATICEDGE,
                           WC_BUTTON,
                           NULL,
                           WS_CHILD | WS_VISIBLE | BS_BITMAP,
                           rect.right - 15,
                           rect.bottom - 15,
                           15, 15,
                           Info->fltColors->hSelf,
                           NULL,
                           hInstance,
                           NULL);
    if (hMore == NULL)
        return FALSE;

    hMoreBitmap = (HBITMAP)LoadImage(hInstance,
                                     MAKEINTRESOURCE(IDB_COLORSMORE),
                                     IMAGE_BITMAP,
                                     12,
                                     11,
                                     LR_LOADTRANSPARENT | LR_LOADMAP3DCOLORS);
    if (hMoreBitmap != NULL)
    {
        SendMessage(hMore,
                    BM_SETIMAGE,
                    IMAGE_BITMAP,
                    (LPARAM)hMoreBitmap);
    }


    /* temp functions for playing about with possible layouts */
    FloatWindowPaintHueSlider(hHueSlider);
    FloatWindowPaintColorPicker(hColorPicker);

    if (hColorPicker != NULL)
    {
        HDC hDc = GetDC(hColorPicker);
        TextOut(hDc, 8, 75, _T("Possible layout?"), 16);
        ReleaseDC(hColorPicker, hDc);
    }

    return TRUE;

}