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
typedef  int UINT ;
struct TYPE_3__ {int xHotspot; int yHotspot; scalar_t__ hbmColor; scalar_t__ hbmMask; void* fIcon; } ;
typedef  int PixelFormat ;
typedef  int ImageType ;
typedef  TYPE_1__ ICONINFO ;
typedef  int /*<<< orphan*/ * HICON ;
typedef  scalar_t__ HBITMAP ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ CreateBitmap (int,int,int,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * CreateIconIndirect (TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int GdipCreateBitmapFromHICON (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int GdipGetImageHeight (int /*<<< orphan*/ *,int*) ; 
 int GdipGetImagePixelFormat (int /*<<< orphan*/ *,int*) ; 
 int GdipGetImageType (int /*<<< orphan*/ *,int*) ; 
 int GdipGetImageWidth (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ImageFormatMemoryBMP ; 
 int ImageTypeBitmap ; 
 int InvalidParameter ; 
 int Ok ; 
 int PixelFormat32bppARGB ; 
 void* TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expect_rawformat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_fromhicon(void)
{
    static const BYTE bmp_bits[1024];
    HBITMAP hbmMask, hbmColor;
    ICONINFO info;
    HICON hIcon;
    GpStatus stat;
    GpBitmap *bitmap = NULL;
    UINT dim;
    ImageType type;
    PixelFormat format;

    /* NULL */
    stat = GdipCreateBitmapFromHICON(NULL, NULL);
    expect(InvalidParameter, stat);
    stat = GdipCreateBitmapFromHICON(NULL, &bitmap);
    expect(InvalidParameter, stat);

    /* color icon 1 bit */
    hbmMask = CreateBitmap(16, 16, 1, 1, bmp_bits);
    ok(hbmMask != 0, "CreateBitmap failed\n");
    hbmColor = CreateBitmap(16, 16, 1, 1, bmp_bits);
    ok(hbmColor != 0, "CreateBitmap failed\n");
    info.fIcon = TRUE;
    info.xHotspot = 8;
    info.yHotspot = 8;
    info.hbmMask = hbmMask;
    info.hbmColor = hbmColor;
    hIcon = CreateIconIndirect(&info);
    ok(hIcon != 0, "CreateIconIndirect failed\n");
    DeleteObject(hbmMask);
    DeleteObject(hbmColor);

    stat = GdipCreateBitmapFromHICON(hIcon, &bitmap);
    ok(stat == Ok ||
       broken(stat == InvalidParameter), /* Win98 */
       "Expected Ok, got %.8x\n", stat);
    if(stat == Ok){
       /* check attributes */
       stat = GdipGetImageHeight((GpImage*)bitmap, &dim);
       expect(Ok, stat);
       expect(16, dim);
       stat = GdipGetImageWidth((GpImage*)bitmap, &dim);
       expect(Ok, stat);
       expect(16, dim);
       stat = GdipGetImageType((GpImage*)bitmap, &type);
       expect(Ok, stat);
       expect(ImageTypeBitmap, type);
       stat = GdipGetImagePixelFormat((GpImage*)bitmap, &format);
       expect(Ok, stat);
       expect(PixelFormat32bppARGB, format);
       /* raw format */
       expect_rawformat(&ImageFormatMemoryBMP, (GpImage*)bitmap, __LINE__, FALSE);
       GdipDisposeImage((GpImage*)bitmap);
    }
    DestroyIcon(hIcon);

    /* color icon 8 bpp */
    hbmMask = CreateBitmap(16, 16, 1, 8, bmp_bits);
    ok(hbmMask != 0, "CreateBitmap failed\n");
    hbmColor = CreateBitmap(16, 16, 1, 8, bmp_bits);
    ok(hbmColor != 0, "CreateBitmap failed\n");
    info.fIcon = TRUE;
    info.xHotspot = 8;
    info.yHotspot = 8;
    info.hbmMask = hbmMask;
    info.hbmColor = hbmColor;
    hIcon = CreateIconIndirect(&info);
    ok(hIcon != 0, "CreateIconIndirect failed\n");
    DeleteObject(hbmMask);
    DeleteObject(hbmColor);

    stat = GdipCreateBitmapFromHICON(hIcon, &bitmap);
    expect(Ok, stat);
    if(stat == Ok){
        /* check attributes */
        stat = GdipGetImageHeight((GpImage*)bitmap, &dim);
        expect(Ok, stat);
        expect(16, dim);
        stat = GdipGetImageWidth((GpImage*)bitmap, &dim);
        expect(Ok, stat);
        expect(16, dim);
        stat = GdipGetImageType((GpImage*)bitmap, &type);
        expect(Ok, stat);
        expect(ImageTypeBitmap, type);
        stat = GdipGetImagePixelFormat((GpImage*)bitmap, &format);
	expect(Ok, stat);
        expect(PixelFormat32bppARGB, format);
        /* raw format */
        expect_rawformat(&ImageFormatMemoryBMP, (GpImage*)bitmap, __LINE__, FALSE);
        GdipDisposeImage((GpImage*)bitmap);
    }
    DestroyIcon(hIcon);
}