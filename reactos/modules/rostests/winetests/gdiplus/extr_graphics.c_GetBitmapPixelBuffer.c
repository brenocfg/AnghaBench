#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_2__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; scalar_t__ biClrImportant; scalar_t__ biClrUsed; scalar_t__ biYPelsPerMeter; scalar_t__ biXPelsPerMeter; scalar_t__ biSizeImage; int /*<<< orphan*/  biCompression; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ BITMAPINFOHEADER ;
typedef  int /*<<< orphan*/  BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 scalar_t__ GdipAlloc (int) ; 
 int GetDIBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD* GetBitmapPixelBuffer(HDC hdc, HBITMAP hbmp, int width, int height)
{
    BITMAPINFOHEADER bi;
    UINT lines = 0;
    DWORD *buffer = (DWORD *)GdipAlloc(width*height*4);

    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height; /*very Important, set negative, indicating a top-down DIB*/
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    lines = GetDIBits(hdc, hbmp, 0, height, buffer, (BITMAPINFO *)&bi, DIB_RGB_COLORS);
    ok(lines == height, "Expected GetDIBits:%p,%d->%d,%d\n", buffer, height, lines, GetLastError());

    return buffer;
}