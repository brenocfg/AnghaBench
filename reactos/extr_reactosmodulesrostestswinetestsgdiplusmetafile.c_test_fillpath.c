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
typedef  int /*<<< orphan*/  GpSolidFill ;
typedef  TYPE_1__ GpRectF ;
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  GpMetafile ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBrush ;

/* Variables and functions */
 int /*<<< orphan*/  CopyEnhMetaFileW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteEnhMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileW (char const*) ; 
 int /*<<< orphan*/  EmfTypeEmfPlusOnly ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathLine (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  GdipCreateMetafileFromWmfFile (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateSolidFill (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipFillPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetHemfFromMetafile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipRecordMetafile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GenericError ; 
 int /*<<< orphan*/  MetafileFrameUnitPixel ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  check_emfplus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_path_records ; 
 int /*<<< orphan*/  sync_metafile (int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static void test_fillpath(void)
{
    static const WCHAR description[] = {'w','i','n','e','t','e','s','t',0};
    static const GpRectF frame = {0.0, 0.0, 100.0, 100.0};
    static const WCHAR winetestemfW[] = {'w','i','n','e','t','e','s','t','.','e','m','f',0};

    GpMetafile *metafile;
    GpGraphics *graphics;
    GpSolidFill *brush;
    HENHMETAFILE hemf;
    GpStatus stat;
    GpPath *path;
    HDC hdc;

    hdc = CreateCompatibleDC(0);
    stat = GdipRecordMetafile(hdc, EmfTypeEmfPlusOnly, &frame, MetafileFrameUnitPixel, description, &metafile);
    expect(Ok, stat);
    DeleteDC(hdc);

    stat = GdipGetImageGraphicsContext((GpImage*)metafile, &graphics);
    expect(Ok, stat);

    stat = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, stat);
    stat = GdipAddPathLine(path, 5, 5, 30, 30);
    expect(Ok, stat);
    stat = GdipAddPathLine(path, 30, 30, 5, 30);
    expect(Ok, stat);

    stat = GdipCreateSolidFill(0xffaabbcc, &brush);
    expect(Ok, stat);

    stat = GdipFillPath(graphics, (GpBrush*)brush, path);
    expect(Ok, stat);

    stat = GdipDeleteBrush((GpBrush*)brush);
    expect(Ok, stat);
    stat = GdipDeletePath(path);
    expect(Ok, stat);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);
    sync_metafile(&metafile, "fill_path.emf");

    stat = GdipGetHemfFromMetafile(metafile, &hemf);
    expect(Ok, stat);

    check_emfplus(hemf, fill_path_records, "fill path");

    /* write to disk */
    DeleteEnhMetaFile(CopyEnhMetaFileW(hemf, winetestemfW));

    DeleteEnhMetaFile(hemf);

    stat = GdipDisposeImage((GpImage*)metafile);
    expect(Ok, stat);

    /* should succeed when given path to an EMF */
    stat = GdipCreateMetafileFromWmfFile(winetestemfW, NULL, &metafile);
    expect(Ok, stat);

    stat = GdipDisposeImage((GpImage*)metafile);
    expect(Ok, stat);

    DeleteFileW(winetestemfW);

    stat = GdipCreateMetafileFromWmfFile(winetestemfW, NULL, &metafile);
    expect(GenericError, stat);
}