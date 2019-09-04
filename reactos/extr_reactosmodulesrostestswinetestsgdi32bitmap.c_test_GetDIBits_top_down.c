#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bi ;
struct TYPE_6__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int /*<<< orphan*/  biCompression; } ;
struct TYPE_7__ {TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  TYPE_2__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/ * CreateDIBSection (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ *) ; 
 int GetDIBits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  setup_picture (char*,int) ; 

__attribute__((used)) static void test_GetDIBits_top_down(int bpp)
{
    BITMAPINFO bi;
    HBITMAP bmptb, bmpbt;
    HDC hdc;
    int pictureOut[4];
    int *picture;
    int statusCode;

    memset( &bi, 0, sizeof(bi) );
    bi.bmiHeader.biSize=sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth=2;
    bi.bmiHeader.biHeight=2;
    bi.bmiHeader.biPlanes=1;
    bi.bmiHeader.biBitCount=bpp;
    bi.bmiHeader.biCompression=BI_RGB;

    /*Get the device context for the screen.*/
    hdc = GetDC(NULL);
    ok(hdc != NULL, "Could not get a handle to a device context.\n");

    /*Create the bottom to top image (image's bottom scan line is at the top in memory).*/
    bmpbt = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, (void**)&picture, NULL, 0);
    ok(bmpbt != NULL, "Could not create a DIB section.\n");
    /*Now that we have a pointer to the pixels, we write to them.*/
    setup_picture((char*)picture, bpp);
    /*Create the top to bottom image (images' bottom scan line is at the bottom in memory).*/
    bi.bmiHeader.biHeight=-2; /*We specify that we want a top to bottom image by specifying a negative height.*/
    bmptb = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, (void**)&picture, NULL, 0);
    ok(bmptb != NULL, "Could not create a DIB section.\n");
    /*Write to this top to bottom bitmap.*/
    setup_picture((char*)picture, bpp);

    bi.bmiHeader.biWidth = 1;

    bi.bmiHeader.biHeight = 2;
    statusCode = GetDIBits(hdc, bmpbt, 0, 1, pictureOut, &bi, DIB_RGB_COLORS);
    ok(statusCode, "Failed to call GetDIBits. Status code: %d.\n", statusCode);
    /*Check the first byte of the pixel.*/
    ok((char)pictureOut[0] == 0, "Bottom-up -> bottom-up: first pixel should be 0 but was %d.\n", (char)pictureOut[0]);
    statusCode = GetDIBits(hdc, bmptb, 0, 1, pictureOut, &bi, DIB_RGB_COLORS);
    ok(statusCode, "Failed to call GetDIBits. Status code: %d.\n", statusCode);
    ok((char)pictureOut[0] == 2, "Top-down -> bottom-up: first pixel should be 2 but was %d.\n", (char)pictureOut[0]);
    /*Check second scanline.*/
    statusCode = GetDIBits(hdc, bmptb, 1, 1, pictureOut, &bi, DIB_RGB_COLORS);
    ok(statusCode, "Failed to call GetDIBits. Status code: %d.\n", statusCode);
    ok((char)pictureOut[0] == 0, "Top-down -> bottom-up: first pixel should be 0 but was %d.\n", (char)pictureOut[0]);
    statusCode = GetDIBits(hdc, bmpbt, 1, 1, pictureOut, &bi, DIB_RGB_COLORS);
    ok(statusCode, "Failed to call GetDIBits. Status code: %d.\n", statusCode);
    ok((char)pictureOut[0] == 2, "Bottom-up -> bottom-up: first pixel should be 2 but was %d.\n", (char)pictureOut[0]);
    /*Check both scanlines.*/
    statusCode = GetDIBits(hdc, bmptb, 0, 2, pictureOut, &bi, DIB_RGB_COLORS);
    ok(statusCode, "Failed to call GetDIBits. Status code: %d.\n", statusCode);
    ok((char)pictureOut[0] == 2, "Top-down -> bottom-up: first scanline should be 2 but was %d.\n", (char)pictureOut[0]);
    ok((char)pictureOut[1] == 0, "Top-down -> bottom-up: second scanline should be 0 but was %d.\n", (char)pictureOut[0]);
    statusCode = GetDIBits(hdc, bmpbt, 0, 2, pictureOut, &bi, DIB_RGB_COLORS);
    ok(statusCode, "Failed to call GetDIBits. Status code: %d.\n", statusCode);
    ok((char)pictureOut[0] == 0, "Bottom up -> bottom-up: first scanline should be 0 but was %d.\n", (char)pictureOut[0]);
    ok((char)pictureOut[1] == 2, "Bottom up -> bottom-up: second scanline should be 2 but was %d.\n", (char)pictureOut[0]);

    /*Make destination bitmap top-down.*/
    bi.bmiHeader.biHeight = -2;
    statusCode = GetDIBits(hdc, bmpbt, 0, 1, pictureOut, &bi, DIB_RGB_COLORS);
    ok(statusCode, "Failed to call GetDIBits. Status code: %d.\n", statusCode);
    ok((char)pictureOut[0] == 0, "Bottom-up -> top-down: first pixel should be 0 but was %d.\n", (char)pictureOut[0]);
    statusCode = GetDIBits(hdc, bmptb, 0, 1, pictureOut, &bi, DIB_RGB_COLORS);
    ok(statusCode, "Failed to call GetDIBits. Status code: %d.\n", statusCode);
    ok((char)pictureOut[0] == 2, "Top-down -> top-down: first pixel should be 2 but was %d.\n", (char)pictureOut[0]);
    /*Check second scanline.*/
    statusCode = GetDIBits(hdc, bmptb, 1, 1, pictureOut, &bi, DIB_RGB_COLORS);
    ok(statusCode, "Failed to call GetDIBits. Status code: %d.\n", statusCode);
    ok((char)pictureOut[0] == 0, "Top-down -> bottom-up: first pixel should be 0 but was %d.\n", (char)pictureOut[0]);
    statusCode = GetDIBits(hdc, bmpbt, 1, 1, pictureOut, &bi, DIB_RGB_COLORS);
    ok(statusCode, "Failed to call GetDIBits. Status code: %d.\n", statusCode);
    ok((char)pictureOut[0] == 2, "Top-down -> bottom-up: first pixel should be 2 but was %d.\n", (char)pictureOut[0]);
    /*Check both scanlines.*/
    statusCode = GetDIBits(hdc, bmptb, 0, 2, pictureOut, &bi, DIB_RGB_COLORS);
    ok(statusCode, "Failed to call GetDIBits. Status code: %d.\n", statusCode);
    ok((char)pictureOut[0] == 0, "Top-down -> top-down: first scanline should be 0 but was %d.\n", (char)pictureOut[0]);
    ok((char)pictureOut[1] == 2, "Top-down -> top-down: second scanline should be 2 but was %d.\n", (char)pictureOut[0]);
    statusCode = GetDIBits(hdc, bmpbt, 0, 2, pictureOut, &bi, DIB_RGB_COLORS);
    ok(statusCode, "Failed to call GetDIBits. Status code: %d.\n", statusCode);
    ok((char)pictureOut[0] == 2, "Bottom up -> top-down: first scanline should be 2 but was %d.\n", (char)pictureOut[0]);
    ok((char)pictureOut[1] == 0, "Bottom up -> top-down: second scanline should be 0 but was %d.\n", (char)pictureOut[0]);

    DeleteObject(bmpbt);
    DeleteObject(bmptb);
}