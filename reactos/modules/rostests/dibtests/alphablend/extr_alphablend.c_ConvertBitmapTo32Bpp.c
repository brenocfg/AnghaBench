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
struct TYPE_7__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int biSizeImage; int /*<<< orphan*/  biCompression; } ;
struct TYPE_9__ {TYPE_1__ bmiHeader; } ;
struct TYPE_8__ {int bmWidth; int bmHeight; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBITMAP ;
typedef  int COLORREF ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  BITMAPINFO ;
typedef  TYPE_2__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 scalar_t__ CreateDIBSection (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetPixel (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ GetRValue (int /*<<< orphan*/ ) ; 
 scalar_t__ H32BppBitmap ; 
 int /*<<< orphan*/  HInst ; 
 int /*<<< orphan*/  HMemDC ; 
 int /*<<< orphan*/  IMAGE_BITMAP ; 
 scalar_t__ LoadImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 
 TYPE_3__ bmpi ; 
 int* pBmpBits ; 

BOOL ConvertBitmapTo32Bpp(HDC hDC, BITMAP *bmp)
{
  ZeroMemory(&bmpi, sizeof(BITMAPINFO));
  bmpi.bmiHeader.biSize = sizeof(BITMAPINFO);
  bmpi.bmiHeader.biWidth = bmp->bmWidth;
  bmpi.bmiHeader.biHeight = bmp->bmHeight;
  bmpi.bmiHeader.biPlanes = 1;
  bmpi.bmiHeader.biBitCount = 32;
  bmpi.bmiHeader.biCompression = BI_RGB;
  bmpi.bmiHeader.biSizeImage = 4 * bmpi.bmiHeader.biWidth * bmpi.bmiHeader.biHeight;
  H32BppBitmap = CreateDIBSection(hDC, &bmpi, DIB_RGB_COLORS, &pBmpBits, 0, 0);
  if(H32BppBitmap)
  {
    HBITMAP bmpalpha;
    SelectObject(hDC, H32BppBitmap);
    BitBlt(hDC, 0, 0, bmp->bmWidth, bmp->bmHeight, HMemDC, 0, 0, SRCCOPY);

    /* load and apply alpha channel */
    bmpalpha = LoadImage(HInst, MAKEINTRESOURCE(2000), IMAGE_BITMAP,
                            0, 0, 0);
    if(bmpalpha)
    {
      COLORREF *col = pBmpBits;
      int x, y;
      HDC hdcTemp = CreateCompatibleDC(NULL);
      if(!hdcTemp)
      {
        DeleteObject(bmpalpha);
        return FALSE;
      }
      SelectObject(hdcTemp, bmpalpha);

      for(y = 0; y < bmp->bmHeight; y++)
      {
        for(x = 0; x < bmp->bmWidth; x++)
        {
          COLORREF Color = (COLORREF)GetRValue(GetPixel(hdcTemp, x, y)) << 24;
          *col++ |= Color;
        }
      }

      DeleteObject(bmpalpha);
      DeleteDC(hdcTemp);
      return TRUE;
    }
    return FALSE;
  }
  return FALSE;
}