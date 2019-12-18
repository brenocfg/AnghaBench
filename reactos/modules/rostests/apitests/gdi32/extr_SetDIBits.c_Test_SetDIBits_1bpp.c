#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
typedef  int UINT ;
struct TYPE_5__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int biClrUsed; scalar_t__ biClrImportant; scalar_t__ biYPelsPerMeter; scalar_t__ biXPelsPerMeter; scalar_t__ biSizeImage; int /*<<< orphan*/  biCompression; } ;
struct TYPE_7__ {TYPE_2__* bmiColors; TYPE_1__ bmiHeader; } ;
struct TYPE_6__ {int rgbBlue; int rgbGreen; int rgbRed; } ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int COLORREF ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_3__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/ * CreateBitmap (int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int GetPixel (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SetDIBits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*) ; 

void Test_SetDIBits_1bpp()
{
    char buffer[sizeof(BITMAPINFOHEADER)+2*sizeof(RGBQUAD)];
    HDC hdc;
    BITMAPINFO* pBMI = (BITMAPINFO*)buffer;
    char bits1bpp[] = {0x80, 0, 0, 0};
    HBITMAP hbmp;
    int ret;
    COLORREF color;

    hdc = CreateCompatibleDC(0);
    if(!hdc)
    {
        trace("No device contexr !?\n");
        return;
    }

    ZeroMemory(buffer, sizeof(buffer));

    pBMI->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
    pBMI->bmiHeader.biWidth=2;
    pBMI->bmiHeader.biHeight=1;
    pBMI->bmiHeader.biPlanes=1;
    pBMI->bmiHeader.biBitCount=1;
    pBMI->bmiHeader.biCompression=BI_RGB;
    pBMI->bmiHeader.biSizeImage=0;
    pBMI->bmiHeader.biXPelsPerMeter=0;
    pBMI->bmiHeader.biYPelsPerMeter=0;
    pBMI->bmiHeader.biClrUsed=2;
    pBMI->bmiHeader.biClrImportant=0;
    pBMI->bmiColors[0].rgbBlue = 0xFF;
    pBMI->bmiColors[0].rgbGreen = 0xFF;
    pBMI->bmiColors[0].rgbRed = 0xFF;

    hbmp = CreateBitmap(2, 1, 1, 1, NULL);
    ok(hbmp!=NULL, "Failed to create a monochrome bitmap\n");

    ret = SetDIBits(NULL, hbmp, 0, 1, bits1bpp, pBMI, DIB_RGB_COLORS);
    ok(ret == 1, "Copied %i scanlines\n", ret);

    hbmp = SelectObject(hdc, hbmp);
    ok(hbmp != NULL, "Could not select the bitmap into the context.\n");
    color = GetPixel(hdc, 0,0);
    ok(color == 0, "Wrong color at 0,0 : 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 1,0);
    ok(color == 0xFFFFFF, "Wrong color at 1,0 : 0x%08x\n", (UINT)color);

    hbmp = SelectObject(hdc, hbmp);

    /* Try something else than 0xFFFFFF */
    pBMI->bmiColors[0].rgbBlue = 0xFF;
    pBMI->bmiColors[0].rgbGreen = 0;
    pBMI->bmiColors[0].rgbRed = 0;

    ret = SetDIBits(NULL, hbmp, 0, 1, bits1bpp, pBMI, DIB_RGB_COLORS);
    ok(ret == 1, "Copied %i scanlines\n", ret);

    hbmp = SelectObject(hdc, hbmp);
    ok(hbmp != NULL, "Could not select the bitmap into the context.\n");
    color = GetPixel(hdc, 0,0);
    ok(color == 0, "Wrong color at 0,0 : 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 1,0);
    ok(color == 0xFFFFFF, "Wrong color at 1,0 : 0x%08x\n", (UINT)color);

    hbmp = SelectObject(hdc, hbmp);

    /* Special : try 0 */
    pBMI->bmiColors[0].rgbBlue = 0;
    pBMI->bmiColors[0].rgbGreen = 0;
    pBMI->bmiColors[0].rgbRed = 0;

    ret = SetDIBits(NULL, hbmp, 0, 1, bits1bpp, pBMI, DIB_RGB_COLORS);
    ok(ret == 1, "Copied %i scanlines\n", ret);

    hbmp = SelectObject(hdc, hbmp);
    ok(hbmp != NULL, "Could not select the bitmap into the context.\n");
    color = GetPixel(hdc, 0,0);
    ok(color == 0, "Wrong color at 0,0 : 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 1,0);
    ok(color == 0xFFFFFF, "Wrong color at 1,0 : 0x%08x\n", (UINT)color);

    hbmp = SelectObject(hdc, hbmp);
    DeleteObject(hbmp);
    DeleteDC(hdc);
}