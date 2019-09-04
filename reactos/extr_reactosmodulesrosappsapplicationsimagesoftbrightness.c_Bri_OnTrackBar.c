#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  hPicPrev; void* BlueVal; void* GreenVal; void* RedVal; int /*<<< orphan*/  hPreviewBitmap; int /*<<< orphan*/  hBitmap; } ;
typedef  TYPE_1__* PIMAGEADJUST ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  void* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustBrightness (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,void*) ; 
 void* BASECOLOUR ; 
 scalar_t__ BST_CHECKED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_BRI_BLUE ; 
 int /*<<< orphan*/  IDC_BRI_EDIT ; 
 int /*<<< orphan*/  IDC_BRI_FULL ; 
 int /*<<< orphan*/  IDC_BRI_GREEN ; 
 int /*<<< orphan*/  IDC_BRI_RED ; 
 int /*<<< orphan*/  IDC_BRI_TRACKBAR ; 
 scalar_t__ IsDlgButtonChecked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TBM_GETPOS ; 

__attribute__((used)) static VOID
Bri_OnTrackBar(PIMAGEADJUST pImgAdj,
           HWND hDlg)
{
    HDC hdcMem;
    DWORD TrackPos;

    TrackPos = (DWORD)SendDlgItemMessage(hDlg,
                                         IDC_BRI_TRACKBAR,
                                         TBM_GETPOS,
                                         0,
                                         0);

    SetDlgItemInt(hDlg,
                  IDC_BRI_EDIT,
                  TrackPos,
                  FALSE);

    if (IsDlgButtonChecked(hDlg, IDC_BRI_FULL) == BST_CHECKED)
    {
        pImgAdj->RedVal = pImgAdj->GreenVal = pImgAdj->BlueVal = TrackPos - BASECOLOUR;
    }
    else if (IsDlgButtonChecked(hDlg, IDC_BRI_RED) == BST_CHECKED)
    {
        pImgAdj->RedVal = TrackPos - BASECOLOUR;
    }
    else if (IsDlgButtonChecked(hDlg, IDC_BRI_GREEN) == BST_CHECKED)
    {
        pImgAdj->GreenVal = TrackPos - BASECOLOUR;
    }
    else if (IsDlgButtonChecked(hDlg, IDC_BRI_BLUE) == BST_CHECKED)
    {
        pImgAdj->BlueVal = TrackPos - BASECOLOUR;
    }

    hdcMem = GetDC(pImgAdj->hPicPrev);

    AdjustBrightness(pImgAdj->hBitmap,
                     pImgAdj->hPreviewBitmap,
                     pImgAdj->hPicPrev,
                     hdcMem,
                     pImgAdj->RedVal,
                     pImgAdj->GreenVal,
                     pImgAdj->BlueVal);

    ReleaseDC(pImgAdj->hPicPrev, hdcMem);
}