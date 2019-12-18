#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  todo_wine ;
struct GdiplusStartupInput {int GdiplusVersion; scalar_t__ SuppressExternalCodecs; scalar_t__ SuppressBackgroundThread; int /*<<< orphan*/ * DebugEventCallback; } ;
typedef  int /*<<< orphan*/  status ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int Status ;
typedef  int /*<<< orphan*/  GpPen ;
typedef  int /*<<< orphan*/  GdiplusNotInitialized ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int GdipCreatePen1 (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdiplusShutdown (int /*<<< orphan*/ ) ; 
 int GdiplusStartup (int /*<<< orphan*/ *,struct GdiplusStartupInput*,int /*<<< orphan*/ *) ; 
 int Ok ; 
 int /*<<< orphan*/  UnitPixel ; 
 int UnsupportedGdiplusVersion ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  trace (char*,int) ; 

__attribute__((used)) static void test_startup(void)
{
    GpPen *pen = NULL;
    Status status;
    struct GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    int gpversion;

    gdiplusStartupInput.DebugEventCallback          = NULL;
    gdiplusStartupInput.SuppressBackgroundThread    = 0;
    gdiplusStartupInput.SuppressExternalCodecs      = 0;

    for (gpversion=1; gpversion<256; gpversion++)
    {
        gdiplusStartupInput.GdiplusVersion = gpversion;
        status = GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
        ok(status == Ok || status == UnsupportedGdiplusVersion,
            "GdiplusStartup returned %x\n", status);
        GdiplusShutdown(gdiplusToken);
        if (status != Ok)
        {
            gpversion--;
            break;
        }
    }

    ok(gpversion > 0 && gpversion <= 2, "unexpected gdiplus version %i\n", gpversion);
    trace("gdiplus version is %i\n", gpversion);

    status = GdipCreatePen1((ARGB)0xffff00ff, 10.0f, UnitPixel, &pen);

    todo_wine
        expect(GdiplusNotInitialized, status);

    GdipDeletePen(pen);
}