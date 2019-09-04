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
struct TYPE_9__ {int bmWidth; int bmHeight; } ;
struct TYPE_7__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int biSizeImage; scalar_t__ biClrImportant; scalar_t__ biClrUsed; int /*<<< orphan*/  biCompression; } ;
struct TYPE_8__ {TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  size_t* PBYTE ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_2__ BITMAPINFO ;
typedef  TYPE_3__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  CopyMemory (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  FALSE ; 
 int GetBValue (size_t) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDIBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int GetGValue (size_t) ; 
 int /*<<< orphan*/  GetObject (int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int GetRValue (size_t) ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessHeap ; 
 size_t RGB (int,int,int) ; 
 int /*<<< orphan*/  SetDIBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
DisplayInvertedColors(HWND hwnd,
                      HDC hdcMem,
                      HBITMAP hBitmap)
{
    BITMAPINFO bi;
    BITMAP bitmap;
    BOOL bRes;
    DWORD Count = 0;
    INT i, j;
    PBYTE pBits;
    RECT rc;

    GetObject(hBitmap,
              sizeof(BITMAP),
              &bitmap);

    /* Bitmap header */
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = bitmap.bmWidth;
    bi.bmiHeader.biHeight = bitmap.bmHeight;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    bi.bmiHeader.biSizeImage = bitmap.bmWidth * bitmap.bmHeight * 4;
    bi.bmiHeader.biClrUsed = 0;
    bi.bmiHeader.biClrImportant = 0;

    /* Buffer */
    pBits = (PBYTE)HeapAlloc(ProcessHeap,
                             0,
                             bitmap.bmWidth * bitmap.bmHeight * 4);
    if (!pBits)
        return FALSE;

    /* get the bits from the original bitmap */
    bRes = GetDIBits(hdcMem,
                     hBitmap,
                     0,
                     bitmap.bmHeight,
                     pBits,
                     &bi,
                     DIB_RGB_COLORS);

    for (i = 0; i < bitmap.bmHeight; i++)
    {
        for (j = 0; j < bitmap.bmWidth; j++)
        {
            DWORD Val = 0;
            INT b, g, r;

            CopyMemory(&Val,
                       &pBits[Count],
                       4);

            b = 255 - GetRValue(Val);
            g = 255 - GetGValue(Val);
            r = 255 - GetBValue(Val);

            Val = RGB(b, g, r);

            CopyMemory(&pBits[Count],
                       &Val,
                       4);

            Count+=4;
        }
    }

    /* Set the new pixel bits */
    SetDIBits(hdcMem,
              hBitmap,
              0,
              bRes,
              pBits,
              &bi,
              DIB_RGB_COLORS);

    HeapFree(ProcessHeap,
             0,
             pBits);

    GetClientRect(hwnd,
                  &rc);

    InvalidateRect(hwnd,
                   &rc,
                   FALSE);

    return TRUE;
}