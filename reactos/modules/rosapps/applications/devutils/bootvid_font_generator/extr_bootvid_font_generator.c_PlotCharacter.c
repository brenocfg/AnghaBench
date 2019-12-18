#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int biSize; int biBitCount; int biPlanes; int /*<<< orphan*/  biWidth; int /*<<< orphan*/  biHeight; } ;
struct TYPE_5__ {TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  TYPE_2__* PBITMAPINFO ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/ * HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BmpInfo ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  int /*<<< orphan*/  BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateCompatibleBitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDIBits (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  HEIGHT ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TextOutA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WIDTH ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static BOOL PlotCharacter(HDC hDC, HFONT hFont, INT XOffset, INT YOffset, CHAR Character, DWORD BmpBits[])
{
    BOOL bReturnValue = FALSE;
    HBITMAP hOldBmp;
    HFONT hOldFont;
    HBITMAP hBmp = NULL;
    BYTE BmpInfo[sizeof(BITMAPINFO) + sizeof(RGBQUAD)];
    PBITMAPINFO pBmpInfo = (PBITMAPINFO)&BmpInfo;

    hBmp = CreateCompatibleBitmap(hDC, WIDTH, HEIGHT);
    if (!hBmp)
    {
        fprintf(stderr, "CreateCompatibleBitmap failed with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    hOldBmp  = SelectObject(hDC, hBmp);
    hOldFont = SelectObject(hDC, hFont);
    SetBkColor(hDC, RGB(0, 0, 0));
    SetTextColor(hDC, RGB(255, 255, 255));
    TextOutA(hDC, XOffset, YOffset, &Character, 1);

    /*
     * Use enough memory for BITMAPINFO and one additional color in the color table.
     * BITMAPINFO already contains a color table entry for a single color and
     * GetDIBits needs space for two colors (black and white).
     */
    ZeroMemory(&BmpInfo, sizeof(BmpInfo));
    pBmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pBmpInfo->bmiHeader.biHeight = -HEIGHT;
    pBmpInfo->bmiHeader.biWidth = WIDTH;
    pBmpInfo->bmiHeader.biBitCount = 1;
    pBmpInfo->bmiHeader.biPlanes = 1;

    bReturnValue = TRUE;

    if (!GetDIBits(hDC, hBmp, 0, HEIGHT, BmpBits, pBmpInfo, 0))
    {
        fprintf(stderr, "GetDIBits failed with error %lu!\n", GetLastError());
        bReturnValue = FALSE;
    }

    SelectObject(hDC, hOldBmp);
    SelectObject(hDC, hOldFont);

Cleanup:
    if (hBmp)
        DeleteObject(hBmp);

    return bReturnValue;
}