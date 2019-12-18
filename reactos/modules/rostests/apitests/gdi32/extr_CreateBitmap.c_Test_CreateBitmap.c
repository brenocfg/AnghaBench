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
typedef  int /*<<< orphan*/  bitmap ;
typedef  int ULONG ;
struct TYPE_3__ {int bmType; int bmWidth; int bmHeight; int bmWidthBytes; int bmPlanes; int bmBitsPixel; int /*<<< orphan*/  bmBits; } ;
typedef  scalar_t__ HBITMAP ;
typedef  TYPE_1__ BITMAP ;

/* Variables and functions */
 scalar_t__ CreateBitmap (int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEFAULT_BITMAP ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int GetObject (scalar_t__,int,TYPE_1__*) ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_int (int,int) ; 
 int /*<<< orphan*/  ok_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Test_CreateBitmap()
{
    HBITMAP hbmp;
    BITMAP bitmap;
    ULONG cjWidthBytes, cBitsPixel, cExpectedBitsPixel;
    int result, TestBitsPixel, ExpectedBitsPixel;

    hbmp = CreateBitmap(0, 0, 0, 0, NULL);
    ok(hbmp != 0, "should get a 1x1 bitmap\n");
    ok(hbmp == GetStockObject(DEFAULT_BITMAP), "\n");
    ok_int(GetObject(hbmp, sizeof(bitmap), &bitmap), sizeof(BITMAP));
    ok_int(bitmap.bmType, 0);
    ok_int(bitmap.bmWidth, 1);
    ok_int(bitmap.bmHeight, 1);
    ok_int(bitmap.bmWidthBytes, 2);
    ok_int(bitmap.bmPlanes, 1);
    ok_int(bitmap.bmBitsPixel, 1);
    ok_ptr(bitmap.bmBits, 0);
    DeleteObject(hbmp);

    /* Above 32 bpp should fail */
    hbmp = CreateBitmap(1, 2, 1, 33, NULL);
    ok(hbmp == 0, "should fail\n");

    for (TestBitsPixel = 0; TestBitsPixel <= 32; TestBitsPixel++)
    {
        /* CreateBitmap API accepts any number as BitsPixels param.
           but it can only create 1, 4, 8, 16, 24, 32 bpp bitmaps */
        if (TestBitsPixel <= 1)      ExpectedBitsPixel = 1;
        else if(TestBitsPixel <= 4)  ExpectedBitsPixel = 4;
        else if(TestBitsPixel <= 8)  ExpectedBitsPixel = 8;
        else if(TestBitsPixel <= 16) ExpectedBitsPixel = 16;
        else if(TestBitsPixel <= 24) ExpectedBitsPixel = 24;
        else if(TestBitsPixel <= 32) ExpectedBitsPixel = 32;

        /* Calculate proper bmWidthBytes */

        hbmp = CreateBitmap(1, 2, 1, TestBitsPixel, NULL);
        ok(hbmp != 0, "should get a 1x2 bitmap\n");
        result = GetObject(hbmp, sizeof(bitmap), &bitmap);
        ok(result > 0, "result = %d\n", result);
        ok(bitmap.bmType == 0, "bmType = %ld\n", bitmap.bmType);
        ok(bitmap.bmWidth == 1, "bmWidth = %ld\n", bitmap.bmWidth);
        ok(bitmap.bmHeight == 2, "bmHeight = %ld\n", bitmap.bmHeight);
        ok(bitmap.bmPlanes == 1, "bmPlanes = %d\n", bitmap.bmPlanes);
        ok(bitmap.bmBitsPixel == ExpectedBitsPixel, "bmBitsPixel = %d ExpectedBitsPixel= %d \n", bitmap.bmBitsPixel, ExpectedBitsPixel);
        ok(bitmap.bmBits == 0, "bmBits = %p\n", bitmap.bmBits);
        DeleteObject(hbmp);
    }

    hbmp = CreateBitmap(1, 2, 1, 1, NULL);
    ok(hbmp != 0, "should get a 1x2 bitmap\n");
    ok_int(GetObject(hbmp, sizeof(bitmap), &bitmap), sizeof(BITMAP));
    ok_int(bitmap.bmType, 0);
    ok_int(bitmap.bmWidth, 1);
    ok_int(bitmap.bmHeight, 2);
    ok_int(bitmap.bmWidthBytes, 2);
    ok_int(bitmap.bmPlanes, 1);
    ok_int(bitmap.bmBitsPixel, 1);
    ok_ptr(bitmap.bmBits, 0);
    DeleteObject(hbmp);

    for (cBitsPixel = 0; cBitsPixel <= 32; cBitsPixel++)
    {
        /* CreateBitmap API accepts any number as BitsPixels param.
           but it just can create 1, 4, 8, 16, 24, 32 bpp Bitmaps */
        if (cBitsPixel <= 1) cExpectedBitsPixel = 1;
        else if (cBitsPixel <= 4) cExpectedBitsPixel = 4;
        else if (cBitsPixel <= 8) cExpectedBitsPixel = 8;
        else if (cBitsPixel <= 16) cExpectedBitsPixel = 16;
        else if (cBitsPixel <= 24) cExpectedBitsPixel = 24;
        else if (cBitsPixel <= 32) cExpectedBitsPixel = 32;

        hbmp = CreateBitmap(1, 2, 1, cBitsPixel, NULL);
        ok(hbmp != 0, "should get a 1x2 bitmap %ld\n", cBitsPixel);
        ok_int(GetObject(hbmp, sizeof(bitmap), &bitmap), sizeof(BITMAP));

        /* calculate expected line width */
        cjWidthBytes = ((((ULONG)bitmap.bmWidth) * ((ULONG)bitmap.bmBitsPixel) + 15) & ~15) >> 3;

        ok_int(bitmap.bmType, 0);
        ok_int(bitmap.bmWidth, 1);
        ok_int(bitmap.bmHeight, 2);
        ok_int(bitmap.bmPlanes, 1);
        ok_int(bitmap.bmBitsPixel, cExpectedBitsPixel);
        ok_int(bitmap.bmWidthBytes, cjWidthBytes);
        ok_ptr(bitmap.bmBits, 0);
        DeleteObject(hbmp);

    }

    hbmp = CreateBitmap(1, 2, 1, 33, NULL);
    ok(hbmp == 0, "Expected failure for 33 bpp\n");



}