#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  header ;
typedef  char WCHAR ;
struct TYPE_13__ {double member_0; double member_1; } ;
struct TYPE_12__ {double member_0; double member_1; double member_2; double member_3; } ;
struct TYPE_11__ {int Type; int Version; } ;
typedef  TYPE_1__ MetafileHeader ;
typedef  int /*<<< orphan*/  HENHMETAFILE ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int GpStatus ;
typedef  TYPE_2__ GpRectF ;
typedef  TYPE_3__ GpPointF ;
typedef  int /*<<< orphan*/  GpMetafile ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateSolidBrush (int) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmfTypeEmfOnly ; 
 int /*<<< orphan*/  GdiComment (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int GdipBitmapGetPixel (int /*<<< orphan*/ *,int,int,int*) ; 
 int GdipCreateBitmapFromScan0 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int GdipGetDC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipGetHemfFromMetafile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipGetMetafileHeaderFromMetafile (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int GdipRecordMetafile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 
 int GdipReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int InvalidParameter ; 
 int /*<<< orphan*/  MetafileFrameUnitPixel ; 
 int MetafileTypeEmf ; 
 int Ok ; 
 int /*<<< orphan*/  PixelFormat32bppARGB ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  check_metafile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_3__ const*,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  gditransform_records ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  play_metafile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_3__ const*,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_metafile (int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static void test_gditransform(void)
{
    GpStatus stat;
    GpMetafile *metafile;
    GpGraphics *graphics;
    HDC hdc, metafile_dc;
    HENHMETAFILE hemf;
    MetafileHeader header;
    static const GpRectF frame = {0.0, 0.0, 100.0, 100.0};
    static const GpPointF dst_points[3] = {{0.0,0.0},{40.0,0.0},{0.0,40.0}};
    static const WCHAR description[] = {'w','i','n','e','t','e','s','t',0};
    HBRUSH hbrush, holdbrush;
    GpBitmap *bitmap;
    ARGB color;

    hdc = CreateCompatibleDC(0);

    stat = GdipRecordMetafile(hdc, EmfTypeEmfOnly, &frame, MetafileFrameUnitPixel, description, &metafile);
    expect(Ok, stat);

    DeleteDC(hdc);

    if (stat != Ok)
            return;

    stat = GdipGetHemfFromMetafile(metafile, &hemf);
    expect(InvalidParameter, stat);

    memset(&header, 0xaa, sizeof(header));
    stat = GdipGetMetafileHeaderFromMetafile(metafile, &header);
    expect(Ok, stat);
    expect(MetafileTypeEmf, header.Type);
    ok(header.Version == 0xdbc01001 || header.Version == 0xdbc01002, "Unexpected version %x\n", header.Version);

    stat = GdipGetImageGraphicsContext((GpImage*)metafile, &graphics);
    expect(Ok, stat);

    stat = GdipGetDC(graphics, &metafile_dc);
    expect(Ok, stat);

    if (stat != Ok)
    {
        GdipDeleteGraphics(graphics);
        GdipDisposeImage((GpImage*)metafile);
        return;
    }

    hbrush = CreateSolidBrush(0xff);

    holdbrush = SelectObject(metafile_dc, hbrush);

    GdiComment(metafile_dc, 8, (const BYTE*)"winetest");

    SelectObject(metafile_dc, holdbrush);

    DeleteObject(hbrush);

    stat = GdipReleaseDC(graphics, metafile_dc);
    expect(Ok, stat);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    check_metafile(metafile, gditransform_records, "gditransform metafile", dst_points, &frame, UnitPixel);

    sync_metafile(&metafile, "gditransform.emf");

    stat = GdipCreateBitmapFromScan0(100, 100, 0, PixelFormat32bppARGB, NULL, &bitmap);
    expect(Ok, stat);

    stat = GdipGetImageGraphicsContext((GpImage*)bitmap, &graphics);
    expect(Ok, stat);

    play_metafile(metafile, graphics, gditransform_records, "gditransform playback", dst_points, &frame, UnitPixel);

    stat = GdipBitmapGetPixel(bitmap, 10, 10, &color);
    expect(Ok, stat);
    expect(0xffff0000, color);

    stat = GdipBitmapGetPixel(bitmap, 30, 30, &color);
    expect(Ok, stat);
    expect(0x00000000, color);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    stat = GdipDisposeImage((GpImage*)bitmap);
    expect(Ok, stat);

    stat = GdipDisposeImage((GpImage*)metafile);
    expect(Ok, stat);
}