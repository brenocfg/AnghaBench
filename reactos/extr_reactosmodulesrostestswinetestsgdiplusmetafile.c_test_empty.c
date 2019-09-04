#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  header ;
typedef  char WCHAR ;
struct TYPE_26__ {double member_0; double member_1; } ;
struct TYPE_25__ {double member_0; double member_1; double member_2; double member_3; double X; double Y; double Width; double Height; } ;
struct TYPE_24__ {int Type; int Size; int Version; int EmfPlusFlags; double DpiX; double DpiY; int X; int Y; int Width; int Height; int EmfPlusHeaderSize; int LogicalDpiX; } ;
struct TYPE_22__ {int left; int top; double right; double bottom; } ;
struct TYPE_21__ {int left; int top; int right; int bottom; } ;
struct TYPE_20__ {scalar_t__ cy; scalar_t__ cx; } ;
struct TYPE_19__ {double cx; double cy; } ;
struct TYPE_23__ {int nBytes; int iType; TYPE_4__ rclFrame; TYPE_3__ rclBounds; TYPE_2__ szlMillimeters; TYPE_1__ szlDevice; } ;
struct TYPE_18__ {TYPE_5__ EmfHeader; } ;
typedef  double REAL ;
typedef  TYPE_6__ MetafileHeader ;
typedef  int /*<<< orphan*/  HENHMETAFILE ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int GpUnit ;
typedef  int GpStatus ;
typedef  TYPE_7__ GpRectF ;
typedef  TYPE_8__ GpPointF ;
typedef  int /*<<< orphan*/  GpMetafile ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int EMR_HEADER ; 
 scalar_t__ EmfTypeEmfPlusOnly ; 
 int GdipCreateMetafileFromEmf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int GdipGetHemfFromMetafile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipGetImageBounds (int /*<<< orphan*/ *,TYPE_7__*,int*) ; 
 int GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipGetImageHorizontalResolution (int /*<<< orphan*/ *,double*) ; 
 int GdipGetImageVerticalResolution (int /*<<< orphan*/ *,double*) ; 
 int GdipGetMetafileHeaderFromEmf (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int GdipGetMetafileHeaderFromMetafile (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int GdipRecordMetafile (int /*<<< orphan*/ *,scalar_t__,TYPE_7__ const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 
 int InvalidParameter ; 
 int /*<<< orphan*/  MetafileFrameUnitPixel ; 
 scalar_t__ MetafileTypeEmfPlusDual ; 
 int MetafileTypeEmfPlusOnly ; 
 scalar_t__ MetafileTypeInvalid ; 
 scalar_t__ MetafileTypeWmf ; 
 scalar_t__ MetafileTypeWmfPlaceable ; 
 int Ok ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_12__ U (TYPE_6__) ; 
 int UnitPixel ; 
 int /*<<< orphan*/  check_emfplus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_metafile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_8__ const*,TYPE_7__ const*,int) ; 
 int /*<<< orphan*/  empty_records ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expectf (double,double) ; 
 int /*<<< orphan*/  expectf_ (double,double,double) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  sync_metafile (int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static void test_empty(void)
{
    GpStatus stat;
    GpMetafile *metafile;
    GpGraphics *graphics;
    HDC hdc;
    GpRectF bounds;
    GpUnit unit;
    REAL xres, yres;
    HENHMETAFILE hemf, dummy;
    MetafileHeader header;
    static const GpRectF frame = {0.0, 0.0, 100.0, 100.0};
    static const GpPointF dst_points[3] = {{0.0,0.0},{100.0,0.0},{0.0,100.0}};
    static const WCHAR description[] = {'w','i','n','e','t','e','s','t',0};

    hdc = CreateCompatibleDC(0);

    stat = GdipRecordMetafile(NULL, EmfTypeEmfPlusOnly, &frame, MetafileFrameUnitPixel, description, &metafile);
    expect(InvalidParameter, stat);

    stat = GdipRecordMetafile(hdc, MetafileTypeInvalid, &frame, MetafileFrameUnitPixel, description, &metafile);
    expect(InvalidParameter, stat);

    stat = GdipRecordMetafile(hdc, MetafileTypeWmf, &frame, MetafileFrameUnitPixel, description, &metafile);
    expect(InvalidParameter, stat);

    stat = GdipRecordMetafile(hdc, MetafileTypeWmfPlaceable, &frame, MetafileFrameUnitPixel, description, &metafile);
    expect(InvalidParameter, stat);

    stat = GdipRecordMetafile(hdc, MetafileTypeEmfPlusDual+1, &frame, MetafileFrameUnitPixel, description, &metafile);
    expect(InvalidParameter, stat);

    stat = GdipRecordMetafile(hdc, EmfTypeEmfPlusOnly, &frame, MetafileFrameUnitPixel, description, NULL);
    expect(InvalidParameter, stat);

    stat = GdipRecordMetafile(hdc, EmfTypeEmfPlusOnly, &frame, MetafileFrameUnitPixel, description, &metafile);
    expect(Ok, stat);

    DeleteDC(hdc);

    if (stat != Ok)
        return;

    stat = GdipGetHemfFromMetafile(metafile, &hemf);
    expect(InvalidParameter, stat);

    stat = GdipGetImageGraphicsContext((GpImage*)metafile, &graphics);
    expect(Ok, stat);

    stat = GdipGetHemfFromMetafile(metafile, &hemf);
    expect(InvalidParameter, stat);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    check_metafile(metafile, empty_records, "empty metafile", dst_points, &frame, UnitPixel);

    sync_metafile(&metafile, "empty.emf");

    stat = GdipGetImageBounds((GpImage*)metafile, &bounds, &unit);
    expect(Ok, stat);
    expectf(0.0, bounds.X);
    expectf(0.0, bounds.Y);
    expectf_(100.0, bounds.Width, 0.05);
    expectf_(100.0, bounds.Height, 0.05);
    expect(UnitPixel, unit);

    stat = GdipGetImageHorizontalResolution((GpImage*)metafile, &xres);
    expect(Ok, stat);

    stat = GdipGetImageVerticalResolution((GpImage*)metafile, &yres);
    expect(Ok, stat);

    memset(&header, 0xaa, sizeof(header));
    stat = GdipGetMetafileHeaderFromMetafile(metafile, &header);
    expect(Ok, stat);
    expect(MetafileTypeEmfPlusOnly, header.Type);
    expect(U(header).EmfHeader.nBytes, header.Size);
    ok(header.Version == 0xdbc01001 || header.Version == 0xdbc01002, "Unexpected version %x\n", header.Version);
    expect(1, header.EmfPlusFlags); /* reference device was display, not printer */
    expectf(xres, header.DpiX);
    expectf(xres, U(header).EmfHeader.szlDevice.cx / (REAL)U(header).EmfHeader.szlMillimeters.cx * 25.4);
    expectf(yres, header.DpiY);
    expectf(yres, U(header).EmfHeader.szlDevice.cy / (REAL)U(header).EmfHeader.szlMillimeters.cy * 25.4);
    expect(0, header.X);
    expect(0, header.Y);
    expect(100, header.Width);
    expect(100, header.Height);
    expect(28, header.EmfPlusHeaderSize);
    expect(96, header.LogicalDpiX);
    expect(96, header.LogicalDpiX);
    expect(EMR_HEADER, U(header).EmfHeader.iType);
    expect(0, U(header).EmfHeader.rclBounds.left);
    expect(0, U(header).EmfHeader.rclBounds.top);
    expect(-1, U(header).EmfHeader.rclBounds.right);
    expect(-1, U(header).EmfHeader.rclBounds.bottom);
    expect(0, U(header).EmfHeader.rclFrame.left);
    expect(0, U(header).EmfHeader.rclFrame.top);
    expectf_(100.0, U(header).EmfHeader.rclFrame.right * xres / 2540.0, 2.0);
    expectf_(100.0, U(header).EmfHeader.rclFrame.bottom * yres / 2540.0, 2.0);

    stat = GdipGetHemfFromMetafile(metafile, &hemf);
    expect(Ok, stat);

    stat = GdipGetHemfFromMetafile(metafile, &dummy);
    expect(InvalidParameter, stat);

    stat = GdipDisposeImage((GpImage*)metafile);
    expect(Ok, stat);

    check_emfplus(hemf, empty_records, "empty emf");

    memset(&header, 0xaa, sizeof(header));
    stat = GdipGetMetafileHeaderFromEmf(hemf, &header);
    expect(Ok, stat);
    expect(MetafileTypeEmfPlusOnly, header.Type);
    expect(U(header).EmfHeader.nBytes, header.Size);
    ok(header.Version == 0xdbc01001 || header.Version == 0xdbc01002, "Unexpected version %x\n", header.Version);
    expect(1, header.EmfPlusFlags); /* reference device was display, not printer */
    expectf(xres, header.DpiX);
    expectf(xres, U(header).EmfHeader.szlDevice.cx / (REAL)U(header).EmfHeader.szlMillimeters.cx * 25.4);
    expectf(yres, header.DpiY);
    expectf(yres, U(header).EmfHeader.szlDevice.cy / (REAL)U(header).EmfHeader.szlMillimeters.cy * 25.4);
    expect(0, header.X);
    expect(0, header.Y);
    expect(100, header.Width);
    expect(100, header.Height);
    expect(28, header.EmfPlusHeaderSize);
    expect(96, header.LogicalDpiX);
    expect(96, header.LogicalDpiX);
    expect(EMR_HEADER, U(header).EmfHeader.iType);
    expect(0, U(header).EmfHeader.rclBounds.left);
    expect(0, U(header).EmfHeader.rclBounds.top);
    expect(-1, U(header).EmfHeader.rclBounds.right);
    expect(-1, U(header).EmfHeader.rclBounds.bottom);
    expect(0, U(header).EmfHeader.rclFrame.left);
    expect(0, U(header).EmfHeader.rclFrame.top);
    expectf_(100.0, U(header).EmfHeader.rclFrame.right * xres / 2540.0, 2.0);
    expectf_(100.0, U(header).EmfHeader.rclFrame.bottom * yres / 2540.0, 2.0);

    stat = GdipCreateMetafileFromEmf(hemf, TRUE, &metafile);
    expect(Ok, stat);

    stat = GdipGetImageBounds((GpImage*)metafile, &bounds, &unit);
    expect(Ok, stat);
    expectf(0.0, bounds.X);
    expectf(0.0, bounds.Y);
    expectf_(100.0, bounds.Width, 0.05);
    expectf_(100.0, bounds.Height, 0.05);
    expect(UnitPixel, unit);

    stat = GdipGetImageHorizontalResolution((GpImage*)metafile, &xres);
    expect(Ok, stat);
    expectf(header.DpiX, xres);

    stat = GdipGetImageVerticalResolution((GpImage*)metafile, &yres);
    expect(Ok, stat);
    expectf(header.DpiY, yres);

    memset(&header, 0xaa, sizeof(header));
    stat = GdipGetMetafileHeaderFromMetafile(metafile, &header);
    expect(Ok, stat);
    expect(MetafileTypeEmfPlusOnly, header.Type);
    expect(U(header).EmfHeader.nBytes, header.Size);
    ok(header.Version == 0xdbc01001 || header.Version == 0xdbc01002, "Unexpected version %x\n", header.Version);
    expect(1, header.EmfPlusFlags); /* reference device was display, not printer */
    expectf(xres, header.DpiX);
    expectf(xres, U(header).EmfHeader.szlDevice.cx / (REAL)U(header).EmfHeader.szlMillimeters.cx * 25.4);
    expectf(yres, header.DpiY);
    expectf(yres, U(header).EmfHeader.szlDevice.cy / (REAL)U(header).EmfHeader.szlMillimeters.cy * 25.4);
    expect(0, header.X);
    expect(0, header.Y);
    expect(100, header.Width);
    expect(100, header.Height);
    expect(28, header.EmfPlusHeaderSize);
    expect(96, header.LogicalDpiX);
    expect(96, header.LogicalDpiX);
    expect(EMR_HEADER, U(header).EmfHeader.iType);
    expect(0, U(header).EmfHeader.rclBounds.left);
    expect(0, U(header).EmfHeader.rclBounds.top);
    expect(-1, U(header).EmfHeader.rclBounds.right);
    expect(-1, U(header).EmfHeader.rclBounds.bottom);
    expect(0, U(header).EmfHeader.rclFrame.left);
    expect(0, U(header).EmfHeader.rclFrame.top);
    expectf_(100.0, U(header).EmfHeader.rclFrame.right * xres / 2540.0, 2.0);
    expectf_(100.0, U(header).EmfHeader.rclFrame.bottom * yres / 2540.0, 2.0);

    stat = GdipDisposeImage((GpImage*)metafile);
    expect(Ok, stat);
}