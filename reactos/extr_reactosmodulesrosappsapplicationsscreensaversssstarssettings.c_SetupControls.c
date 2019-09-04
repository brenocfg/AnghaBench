#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lf ;
typedef  size_t UINT ;
struct TYPE_10__ {size_t bmHeight; } ;
struct TYPE_9__ {int lfHeight; int /*<<< orphan*/  lfFaceName; int /*<<< orphan*/  lfQuality; int /*<<< orphan*/  lfCharSet; int /*<<< orphan*/  lfWeight; } ;
struct TYPE_8__ {size_t cy; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  Strings ;
typedef  TYPE_1__ SIZE ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_2__ LOGFONT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HINSTANCE ;
typedef  scalar_t__ HGDIOBJ ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBITMAP ;
typedef  TYPE_3__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  ANSI_CHARSET ; 
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 scalar_t__ CreateFontIndirect (TYPE_2__*) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FW_THIN ; 
 int /*<<< orphan*/  GWLP_HINSTANCE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetObject (scalar_t__,int,TYPE_3__*) ; 
 int /*<<< orphan*/  GetTextExtentPoint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,TYPE_1__*) ; 
 scalar_t__ GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDB_COSMOS ; 
 int /*<<< orphan*/  IDC_COMBO_ROTATION ; 
 int /*<<< orphan*/  IDC_IMAGE_COSMOS ; 
 int /*<<< orphan*/  IDC_SLIDER_NUM_OF_STARS ; 
 int /*<<< orphan*/  IDC_SLIDER_SPEED ; 
 int /*<<< orphan*/  IDS_DESCRIPTION ; 
 int /*<<< orphan*/  IMAGE_BITMAP ; 
 int LR_CREATEDIBSECTION ; 
 int LR_DEFAULTSIZE ; 
 scalar_t__ LoadImage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t LoadString (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELPARAM (int,int) ; 
 int MAX_STARS ; 
 int MIN_STARS ; 
 int /*<<< orphan*/  PROOF_QUALITY ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 size_t ROTATION_ITEMS ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RotoStrings ; 
 int /*<<< orphan*/  STM_SETIMAGE ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TBM_SETRANGE ; 
 int /*<<< orphan*/  TRANSPARENT ; 
 int /*<<< orphan*/  TextOut (int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * _T (char*) ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SetupControls(HWND hWnd)
{
    TCHAR     Strings[256];
    HINSTANCE hInstance;
    UINT      x, gap;
    LOGFONT   lf;
    HFONT     hFont;
    HBITMAP   hCosmos;
    HDC       hDC, hMemDC;
    HGDIOBJ   hOldBmp, hOldFnt;
    SIZE      sizeReactOS;
    SIZE      sizeStarfield;
    BITMAP    bm;

    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    SendDlgItemMessage(hWnd, IDC_SLIDER_NUM_OF_STARS, TBM_SETRANGE, FALSE, MAKELPARAM(MIN_STARS, MAX_STARS));

    SendDlgItemMessage(hWnd, IDC_SLIDER_SPEED, TBM_SETRANGE, FALSE, MAKELPARAM(1, 100));

    for (x = 0; x < ROTATION_ITEMS; x++)
    {
        LoadString(hInstance, RotoStrings[x], Strings, sizeof(Strings)/sizeof(TCHAR));
        SendDlgItemMessage(hWnd, IDC_COMBO_ROTATION, CB_ADDSTRING, 0, (LPARAM)Strings);
    }

    hCosmos = LoadImage(hInstance, MAKEINTRESOURCE(IDB_COSMOS), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);

    // Create the font for the title
    ZeroMemory(&lf, sizeof(lf));

    lf.lfWeight  = FW_THIN;
    lf.lfCharSet = ANSI_CHARSET;
    lf.lfQuality = PROOF_QUALITY;
    lf.lfHeight  = 36;
    _tcscpy(lf.lfFaceName, _T("Tahoma"));

    hFont = CreateFontIndirect(&lf);

    hOldBmp = SelectObject(hMemDC, hCosmos);
    hOldFnt = SelectObject(hMemDC, hFont);

    SetBkMode(hMemDC, TRANSPARENT);
    SetTextColor(hMemDC, RGB(0xFF, 0xFF, 0xFF));

    x = LoadString(hInstance, IDS_DESCRIPTION, Strings, sizeof(Strings)/sizeof(TCHAR));

    GetTextExtentPoint32(hMemDC, _T("ReactOS"), 7, &sizeReactOS);
    GetTextExtentPoint32(hMemDC, Strings,       x, &sizeStarfield);

    GetObject(hCosmos, sizeof(BITMAP), &bm);

    gap = bm.bmHeight - sizeReactOS.cy - sizeStarfield.cy;

    TextOut(hMemDC, 16, gap * 2 / 5, _T("ReactOS"), 7);
    TextOut(hMemDC, 16, gap * 3 / 5 + sizeReactOS.cy, Strings, x);

    SelectObject(hMemDC, hOldBmp);
    SelectObject(hMemDC, hOldFnt);

    DeleteObject(hFont);

    DeleteDC(hMemDC);
    ReleaseDC(hWnd, hDC);

    SendDlgItemMessage(hWnd, IDC_IMAGE_COSMOS, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hCosmos);
}