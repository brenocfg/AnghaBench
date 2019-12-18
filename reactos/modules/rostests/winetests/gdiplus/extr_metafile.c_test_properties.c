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
typedef  char WCHAR ;
struct TYPE_3__ {double member_0; double member_1; double member_2; double member_3; } ;
typedef  int /*<<< orphan*/  HENHMETAFILE ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpRectF ;
typedef  int /*<<< orphan*/  GpMetafile ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  CompositingModeSourceCopy ; 
 int /*<<< orphan*/  CompositingModeSourceOver ; 
 int /*<<< orphan*/  CompositingQualityHighQuality ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteEnhMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmfTypeEmfPlusOnly ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetHemfFromMetafile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipRecordMetafile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipSetCompositingMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetCompositingQuality (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetInterpolationMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetPixelOffsetMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetSmoothingMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetTextRenderingHint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InterpolationModeDefault ; 
 int /*<<< orphan*/  InterpolationModeHighQuality ; 
 int /*<<< orphan*/  MetafileFrameUnitPixel ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PixelOffsetModeHighQuality ; 
 int /*<<< orphan*/  SmoothingModeAntiAlias ; 
 int /*<<< orphan*/  TextRenderingHintAntiAlias ; 
 int /*<<< orphan*/  TextRenderingHintSystemDefault ; 
 int /*<<< orphan*/  check_emfplus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  properties_records ; 
 int /*<<< orphan*/  sync_metafile (int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static void test_properties(void)
{
    static const WCHAR description[] = {'w','i','n','e','t','e','s','t',0};
    static const GpRectF frame = {0.0, 0.0, 100.0, 100.0};

    GpMetafile *metafile;
    GpGraphics *graphics;
    HENHMETAFILE hemf;
    GpStatus stat;
    HDC hdc;

    hdc = CreateCompatibleDC(0);
    stat = GdipRecordMetafile(hdc, EmfTypeEmfPlusOnly, &frame, MetafileFrameUnitPixel, description, &metafile);
    expect(Ok, stat);
    DeleteDC(hdc);

    stat = GdipGetImageGraphicsContext((GpImage*)metafile, &graphics);
    expect(Ok, stat);

    stat = GdipSetTextRenderingHint(graphics, TextRenderingHintSystemDefault);
    expect(Ok, stat);
    stat = GdipSetTextRenderingHint(graphics, TextRenderingHintAntiAlias);
    expect(Ok, stat);

    stat = GdipSetPixelOffsetMode(graphics, PixelOffsetModeHighQuality);
    expect(Ok, stat);
    stat = GdipSetPixelOffsetMode(graphics, PixelOffsetModeHighQuality);
    expect(Ok, stat);

    stat = GdipSetSmoothingMode(graphics, SmoothingModeAntiAlias);
    expect(Ok, stat);
    stat = GdipSetSmoothingMode(graphics, SmoothingModeAntiAlias);
    expect(Ok, stat);

    stat = GdipSetCompositingMode(graphics, CompositingModeSourceOver);
    expect(Ok, stat);
    stat = GdipSetCompositingMode(graphics, CompositingModeSourceCopy);
    expect(Ok, stat);

    stat = GdipSetCompositingQuality(graphics, CompositingQualityHighQuality);
    expect(Ok, stat);
    stat = GdipSetCompositingQuality(graphics, CompositingQualityHighQuality);
    expect(Ok, stat);

    stat = GdipSetInterpolationMode(graphics, InterpolationModeDefault);
    expect(Ok, stat);
    stat = GdipSetInterpolationMode(graphics, InterpolationModeHighQuality);
    expect(Ok, stat);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);
    sync_metafile(&metafile, "properties.emf");

    stat = GdipGetHemfFromMetafile(metafile, &hemf);
    expect(Ok, stat);

    check_emfplus(hemf, properties_records, "properties");
    DeleteEnhMetaFile(hemf);

    stat = GdipDisposeImage((GpImage*)metafile);
    expect(Ok, stat);
}