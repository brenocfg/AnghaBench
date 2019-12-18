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
typedef  int /*<<< orphan*/  bi ;
typedef  size_t UINT ;
struct TYPE_9__ {int bmWidth; int bmHeight; } ;
struct TYPE_7__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int /*<<< orphan*/  biCompression; } ;
struct TYPE_8__ {TYPE_1__ bmiHeader; } ;
typedef  scalar_t__ LPBYTE ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HINSTANCE ;
typedef  scalar_t__ HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBITMAP ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_2__ BITMAPINFO ;
typedef  TYPE_3__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 scalar_t__ CreateDIBSection (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  GWLP_HINSTANCE ; 
 int /*<<< orphan*/  GetObject (scalar_t__,int,TYPE_3__*) ; 
 scalar_t__ GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDB_STAR ; 
 int /*<<< orphan*/  IMAGE_BITMAP ; 
 int LR_CREATEDIBSECTION ; 
 int LR_DEFAULTSIZE ; 
 scalar_t__ LoadImage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 

__attribute__((used)) static HBITMAP CreateStarBitmap(HWND hWnd, HDC hDC)
{
    BITMAPINFO bi;
    LPBYTE     lpBits;
    LPBYTE    *lppBits;
    HBITMAP    hTextBmp, hFileBmp;
    HDC        hTextDC, hFileDC;
    HGDIOBJ    hOldText, hOldFile;
    UINT       i;
    DWORD     *Ptr32;
    BITMAP     bm;
    HINSTANCE  hInstance;

    // Get instance for loading the texture
    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    // Load the texture
    hFileBmp = (HBITMAP)
              LoadImage(
                    hInstance,
                    MAKEINTRESOURCE(IDB_STAR),
                    IMAGE_BITMAP,
                    0, 0,
                    LR_CREATEDIBSECTION | LR_DEFAULTSIZE
              );

    // Get texture specs
    GetObject(hFileBmp, sizeof(BITMAP), &bm);

    // Allocate new 32 bit texture
    ZeroMemory(&bi, sizeof(bi));

    bi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth       = bm.bmWidth;
    bi.bmiHeader.biHeight      = -bm.bmHeight;
    bi.bmiHeader.biPlanes      = 1;
    bi.bmiHeader.biBitCount    = 32;
    bi.bmiHeader.biCompression = BI_RGB;

    // Makes GCC happy ;-|
    lppBits = &lpBits;

    hTextBmp = CreateDIBSection(hDC,
                                (BITMAPINFO*)&bi,
                                DIB_RGB_COLORS,
                                (void**)lppBits,
                                NULL,
                                0);

    // Save new texture specs
//    GetObject(hTextBmp, sizeof(BITMAP), &bmStarTex);
//    bmStarTex.bmBits = lpBits;

    // Copy 24 bit texture in 32 texture
    hTextDC = CreateCompatibleDC(hDC);
    hFileDC = CreateCompatibleDC(hDC);

    hOldText = SelectObject(hTextDC, hTextBmp);
    hOldFile = SelectObject(hFileDC, hFileBmp);

    BitBlt(hTextDC, 0, 0, bm.bmWidth, bm.bmHeight, hFileDC, 0, 0, SRCCOPY);

    SelectObject(hTextDC, hOldText);
    SelectObject(hFileDC, hOldFile);

    DeleteDC(hTextDC);
    DeleteDC(hFileDC);

    // Delete 24 bit texture
    DeleteObject(hFileBmp);

    GetObject(hTextBmp, sizeof(BITMAP), &bm);

    // Apply ALPHA channel to new texture
    for (Ptr32=(DWORD *)lpBits, i=0; i < (UINT)(bm.bmWidth * bm.bmHeight); i++)
    {
        DWORD Color = Ptr32[i] & 0x00FFFFFF;
        DWORD Alpha = Color & 0xFF;

        Color |= Alpha << 24;

        Ptr32[i] = Color;
    }

    return hTextBmp;
}