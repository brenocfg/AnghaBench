#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  Clsid; } ;
typedef  double REAL ;
typedef  TYPE_1__ ImageCodecInfo ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char const*) ; 
 TYPE_1__* GdipAlloc (scalar_t__) ; 
 scalar_t__ GdipCreateBitmapFromScan0 (double const,double const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipFree (TYPE_1__*) ; 
 scalar_t__ GdipGetImageDimension (int /*<<< orphan*/ *,double*,double*) ; 
 scalar_t__ GdipGetImageEncoders (scalar_t__,scalar_t__,TYPE_1__*) ; 
 scalar_t__ GdipGetImageEncodersSize (scalar_t__*,scalar_t__*) ; 
 scalar_t__ GdipLoadImageFromFile (char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ GdipSaveImageToFile (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidParameter ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  PixelFormat24bppRGB ; 
 int /*<<< orphan*/  expect (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  expectf (double const,double) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_SavingImages(void)
{
    GpStatus stat;
    GpBitmap *bm;
    UINT n;
    UINT s;
    const REAL WIDTH = 10.0, HEIGHT = 20.0;
    REAL w, h;
    ImageCodecInfo *codecs;
    static const CHAR filenameA[] = "a.bmp";
    static const WCHAR filename[] = { 'a','.','b','m','p',0 };

    codecs = NULL;

    stat = GdipSaveImageToFile(0, 0, 0, 0);
    expect(InvalidParameter, stat);

    bm = NULL;
    stat = GdipCreateBitmapFromScan0(WIDTH, HEIGHT, 0, PixelFormat24bppRGB, NULL, &bm);
    expect(Ok, stat);
    if (!bm)
        return;

    /* invalid params */
    stat = GdipSaveImageToFile((GpImage*)bm, 0, 0, 0);
    expect(InvalidParameter, stat);

    stat = GdipSaveImageToFile((GpImage*)bm, filename, 0, 0);
    expect(InvalidParameter, stat);

    /* encoder tests should succeed -- already tested */
    stat = GdipGetImageEncodersSize(&n, &s);
    if (stat != Ok || n == 0) goto cleanup;

    codecs = GdipAlloc(s);
    if (!codecs) goto cleanup;

    stat = GdipGetImageEncoders(n, s, codecs);
    if (stat != Ok) goto cleanup;

    stat = GdipSaveImageToFile((GpImage*)bm, filename, &codecs[0].Clsid, 0);
    expect(Ok, stat);

    GdipDisposeImage((GpImage*)bm);
    bm = 0;

    /* re-load and check image stats */
    stat = GdipLoadImageFromFile(filename, (GpImage**)&bm);
    expect(Ok, stat);
    if (stat != Ok) goto cleanup;

    stat = GdipGetImageDimension((GpImage*)bm, &w, &h);
    if (stat != Ok) goto cleanup;

    expectf(WIDTH, w);
    expectf(HEIGHT, h);

 cleanup:
    GdipFree(codecs);
    if (bm)
        GdipDisposeImage((GpImage*)bm);
    ok(DeleteFileA(filenameA), "Delete failed.\n");
}