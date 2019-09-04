#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct test_data   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct test_data {int /*<<< orphan*/  res_x; int /*<<< orphan*/  res_y; int /*<<< orphan*/  scale; int /*<<< orphan*/  pen_unit; int /*<<< orphan*/  page_unit; int /*<<< orphan*/  pen_width; scalar_t__ cx; scalar_t__ cy; scalar_t__ path_cx; scalar_t__ path_cy; } ;
struct TYPE_8__ {int Stride; scalar_t__ Scan0; } ;
struct TYPE_7__ {double X; double Y; } ;
typedef  int /*<<< orphan*/  REAL ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  GpUnit ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpPointF ;
typedef  int /*<<< orphan*/  GpPen ;
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  TYPE_2__ BitmapData ;
typedef  int BYTE ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_6__ const*) ; 
 int /*<<< orphan*/  CoordinateSpaceDevice ; 
 int /*<<< orphan*/  CoordinateSpaceWorld ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathLine (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  GdipBitmapLockBits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GdipBitmapSetResolution (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipBitmapUnlockBits (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  GdipClosePathFigure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipCreateBitmapFromScan0 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePen1 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDrawLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  GdipDrawPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipGraphicsClear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GdipSetPageScale (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetPageUnit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipTransformPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ImageLockModeRead ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PixelFormat24bppRGB ; 
#define  UnitInch 130 
#define  UnitPixel 129 
#define  UnitWorld 128 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void test_pen_thickness(void)
{
    static const struct test_data
    {
        REAL res_x, res_y, scale;
        GpUnit pen_unit, page_unit;
        REAL pen_width;
        INT cx, cy, path_cx, path_cy;
    } td[] =
    {
        { 10.0, 10.0, 1.0, UnitPixel, UnitPixel, 1.0, 1, 1, 1, 1 },
        { 10.0, 10.0, 1.0, UnitPixel, UnitPixel, 0.0, 0, 0, 1, 1 },
        { 10.0, 10.0, 1.0, UnitPixel, UnitPixel, 0.1, 1, 1, 1, 1 },
        { 10.0, 10.0, 3.0, UnitPixel, UnitPixel, 2.0, 2, 2, 2, 2 },
        { 10.0, 10.0, 30.0, UnitPixel, UnitInch, 1.0, 1, 1, 1, 1 },
        { 10.0, 10.0, 1.0, UnitWorld, UnitPixel, 1.0, 1, 1, 1, 1 },
        { 10.0, 10.0, 1.0, UnitWorld, UnitPixel, 0.0, 1, 1, 1, 1 },
        { 10.0, 10.0, 3.0, UnitWorld, UnitPixel, 2.0, 6, 6, 6, 6 },
        { 10.0, 10.0, 2.0, UnitWorld, UnitInch, 1.0, 20, 20, 20, 20 },
    };
    GpStatus status;
    int i, j;
    GpGraphics *graphics;
    union
    {
        GpBitmap *bitmap;
        GpImage *image;
    } u;
    GpPen *pen;
    GpPointF corner;
    GpPath *path;
    BitmapData bd;
    INT min, max, size;

    for (i = 0; i < ARRAY_SIZE(td); i++)
    {
        status = GdipCreateBitmapFromScan0(100, 100, 0, PixelFormat24bppRGB, NULL, &u.bitmap);
        expect(Ok, status);

        status = GdipBitmapSetResolution(u.bitmap, td[i].res_x, td[i].res_y);
        expect(Ok, status);

        status = GdipGetImageGraphicsContext(u.image, &graphics);
        expect(Ok, status);

        status = GdipSetPageUnit(graphics, td[i].page_unit);
        expect(Ok, status);

        status = GdipSetPageScale(graphics, td[i].scale);
        expect(Ok, status);

        status = GdipCreatePen1(0xffffffff, td[i].pen_width, td[i].pen_unit, &pen);
        expect(Ok, status);

        corner.X = corner.Y = 100.0;
        status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, &corner, 1);
        expect(Ok, status);

        status = GdipDrawLine(graphics, pen, corner.X/2, 0, corner.X/2, corner.Y);
        expect(Ok, status);

        status = GdipDrawLine(graphics, pen, 0, corner.Y/2, corner.X, corner.Y/2);
        expect(Ok, status);

        status = GdipBitmapLockBits(u.bitmap, NULL, ImageLockModeRead, PixelFormat24bppRGB, &bd);
        expect(Ok, status);

        min = -1;
        max = -2;

        for (j=0; j<100; j++)
        {
            if (((BYTE*)bd.Scan0)[j*3] == 0xff)
            {
                min = j;
                break;
            }
        }

        for (j=99; j>=0; j--)
        {
            if (((BYTE*)bd.Scan0)[j*3] == 0xff)
            {
                max = j;
                break;
            }
        }

        size = max-min+1;

        ok(size == td[i].cx, "%u: expected %d, got %d\n", i, td[i].cx, size);

        min = -1;
        max = -2;

        for (j=0; j<100; j++)
        {
            if (((BYTE*)bd.Scan0)[bd.Stride*j] == 0xff)
            {
                min = j;
                break;
            }
        }

        for (j=99; j>=0; j--)
        {
            if (((BYTE*)bd.Scan0)[bd.Stride*j] == 0xff)
            {
                max = j;
                break;
            }
        }

        size = max-min+1;

        ok(size == td[i].cy, "%u: expected %d, got %d\n", i, td[i].cy, size);

        status = GdipBitmapUnlockBits(u.bitmap, &bd);
        expect(Ok, status);

        status = GdipGraphicsClear(graphics, 0xff000000);
        expect(Ok, status);

        status = GdipCreatePath(FillModeAlternate, &path);
        expect(Ok, status);

        status = GdipAddPathLine(path, corner.X/2, 0, corner.X/2, corner.Y);
        expect(Ok, status);

        status = GdipClosePathFigure(path);
        expect(Ok, status);

        status = GdipAddPathLine(path, 0, corner.Y/2, corner.X, corner.Y/2);
        expect(Ok, status);

        status = GdipDrawPath(graphics, pen, path);
        expect(Ok, status);

        GdipDeletePath(path);

        status = GdipBitmapLockBits(u.bitmap, NULL, ImageLockModeRead, PixelFormat24bppRGB, &bd);
        expect(Ok, status);

        min = -1;
        max = -2;

        for (j=0; j<100; j++)
        {
            if (((BYTE*)bd.Scan0)[j*3] == 0xff)
            {
                min = j;
                break;
            }
        }

        for (j=99; j>=0; j--)
        {
            if (((BYTE*)bd.Scan0)[j*3] == 0xff)
            {
                max = j;
                break;
            }
        }

        size = max-min+1;

        ok(size == td[i].path_cx, "%u: expected %d, got %d\n", i, td[i].path_cx, size);

        min = -1;
        max = -2;

        for (j=0; j<100; j++)
        {
            if (((BYTE*)bd.Scan0)[bd.Stride*j] == 0xff)
            {
                min = j;
                break;
            }
        }

        for (j=99; j>=0; j--)
        {
            if (((BYTE*)bd.Scan0)[bd.Stride*j] == 0xff)
            {
                max = j;
                break;
            }
        }

        size = max-min+1;

        ok(size == td[i].path_cy, "%u: expected %d, got %d\n", i, td[i].path_cy, size);

        status = GdipBitmapUnlockBits(u.bitmap, &bd);
        expect(Ok, status);

        GdipDeletePen(pen);
        GdipDeleteGraphics(graphics);
        GdipDisposeImage(u.image);
    }
}