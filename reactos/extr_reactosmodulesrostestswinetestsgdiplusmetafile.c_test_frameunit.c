#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_4__ {double member_0; double member_1; double member_2; double member_3; double Width; double Height; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  double REAL ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ GpUnit ;
typedef  scalar_t__ GpStatus ;
typedef  TYPE_1__ GpRectF ;
typedef  int /*<<< orphan*/  GpMetafile ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmfTypeEmfPlusOnly ; 
 scalar_t__ GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipDisposeImage (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipGetImageBounds (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__*) ; 
 scalar_t__ GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ GdipGetImageHorizontalResolution (int /*<<< orphan*/ *,double*) ; 
 scalar_t__ GdipGetImageVerticalResolution (int /*<<< orphan*/ *,double*) ; 
 scalar_t__ GdipRecordMetafile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MetafileFrameUnitInch ; 
 scalar_t__ Ok ; 
 scalar_t__ UnitPixel ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  expect (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  expectf (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf_ (double,double,double) ; 
 int /*<<< orphan*/  ok (int,char*,double) ; 

__attribute__((used)) static void test_frameunit(void)
{
    GpStatus stat;
    GpMetafile *metafile;
    GpGraphics *graphics;
    HDC hdc;
    static const GpRectF frame = {0.0, 0.0, 5.0, 5.0};
    static const WCHAR description[] = {'w','i','n','e','t','e','s','t',0};
    GpUnit unit;
    REAL dpix, dpiy;
    GpRectF bounds;

    hdc = CreateCompatibleDC(0);

    stat = GdipRecordMetafile(hdc, EmfTypeEmfPlusOnly, &frame, MetafileFrameUnitInch, description, &metafile);
    expect(Ok, stat);

    DeleteDC(hdc);

    if (stat != Ok)
        return;

    stat = GdipGetImageBounds((GpImage*)metafile, &bounds, &unit);
    expect(Ok, stat);
    expect(UnitPixel, unit);
    expectf(0.0, bounds.X);
    expectf(0.0, bounds.Y);
    ok(bounds.Width == 1.0 || broken(bounds.Width == 0.0) /* xp sp1 */,
        "expected 1.0, got %f\n", bounds.Width);
    ok(bounds.Height == 1.0 || broken(bounds.Height == 0.0) /* xp sp1 */,
        "expected 1.0, got %f\n", bounds.Height);

    stat = GdipGetImageGraphicsContext((GpImage*)metafile, &graphics);
    expect(Ok, stat);

    stat = GdipGetImageBounds((GpImage*)metafile, &bounds, &unit);
    expect(Ok, stat);
    expect(UnitPixel, unit);
    expectf(0.0, bounds.X);
    expectf(0.0, bounds.Y);
    ok(bounds.Width == 1.0 || broken(bounds.Width == 0.0) /* xp sp1 */,
        "expected 1.0, got %f\n", bounds.Width);
    ok(bounds.Height == 1.0 || broken(bounds.Height == 0.0) /* xp sp1 */,
        "expected 1.0, got %f\n", bounds.Height);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    stat = GdipGetImageHorizontalResolution((GpImage*)metafile, &dpix);
    expect(Ok, stat);

    stat = GdipGetImageVerticalResolution((GpImage*)metafile, &dpiy);
    expect(Ok, stat);

    stat = GdipGetImageBounds((GpImage*)metafile, &bounds, &unit);
    expect(Ok, stat);
    expect(UnitPixel, unit);
    expectf(0.0, bounds.X);
    expectf(0.0, bounds.Y);
    expectf_(5.0 * dpix, bounds.Width, 1.0);
    expectf_(5.0 * dpiy, bounds.Height, 1.0);

    stat = GdipDisposeImage((GpImage*)metafile);
    expect(Ok, stat);
}