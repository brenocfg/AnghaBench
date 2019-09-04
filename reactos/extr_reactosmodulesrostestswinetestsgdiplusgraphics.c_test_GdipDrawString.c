#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  logfont ;
typedef  char WCHAR ;
struct TYPE_10__ {int lfHeight; int /*<<< orphan*/  lfCharSet; int /*<<< orphan*/  lfFaceName; } ;
struct TYPE_9__ {int member_0; int member_1; } ;
struct TYPE_8__ {int Height; scalar_t__ Width; scalar_t__ Y; scalar_t__ X; } ;
typedef  TYPE_1__ RectF ;
typedef  TYPE_2__ PointF ;
typedef  TYPE_3__ LOGFONTA ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStringFormat ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpSolidFill ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpFont ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CHARSET ; 
 int DriverStringOptionsCmapLookup ; 
 scalar_t__ FileNotFound ; 
 scalar_t__ GdipCreateFontFromLogfontA (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ **) ; 
 scalar_t__ GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ GdipCreateMatrix (int /*<<< orphan*/ **) ; 
 scalar_t__ GdipCreateSolidFill (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ GdipCreateStringFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteFont (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteStringFormat (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipDrawDriverString (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__ const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ GdipDrawString (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 scalar_t__ NotTrueTypeFont ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_GdipDrawString(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    GpFont *fnt = NULL;
    RectF  rect;
    GpStringFormat *format;
    GpBrush *brush;
    LOGFONTA logfont;
    HDC hdc = GetDC( hwnd );
    static const WCHAR string[] = {'T','e','s','t',0};
    static const PointF positions[4] = {{0,0}, {1,1}, {2,2}, {3,3}};
    GpMatrix *matrix;

    memset(&logfont,0,sizeof(logfont));
    strcpy(logfont.lfFaceName,"Arial");
    logfont.lfHeight = 12;
    logfont.lfCharSet = DEFAULT_CHARSET;

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    status = GdipCreateFontFromLogfontA(hdc, &logfont, &fnt);
    if (status == NotTrueTypeFont || status == FileNotFound)
    {
        skip("Arial not installed.\n");
        return;
    }
    expect(Ok, status);

    status = GdipCreateSolidFill((ARGB)0xdeadbeef, (GpSolidFill**)&brush);
    expect(Ok, status);

    status = GdipCreateStringFormat(0,0,&format);
    expect(Ok, status);

    rect.X = 0;
    rect.Y = 0;
    rect.Width = 0;
    rect.Height = 12;

    status = GdipDrawString(graphics, string, 4, fnt, &rect, format, brush);
    expect(Ok, status);

    status = GdipCreateMatrix(&matrix);
    expect(Ok, status);

    status = GdipDrawDriverString(NULL, string, 4, fnt, brush, positions, DriverStringOptionsCmapLookup, matrix);
    expect(InvalidParameter, status);

    status = GdipDrawDriverString(graphics, NULL, 4, fnt, brush, positions, DriverStringOptionsCmapLookup, matrix);
    expect(InvalidParameter, status);

    status = GdipDrawDriverString(graphics, string, 4, NULL, brush, positions, DriverStringOptionsCmapLookup, matrix);
    expect(InvalidParameter, status);

    status = GdipDrawDriverString(graphics, string, 4, fnt, NULL, positions, DriverStringOptionsCmapLookup, matrix);
    expect(InvalidParameter, status);

    status = GdipDrawDriverString(graphics, string, 4, fnt, brush, NULL, DriverStringOptionsCmapLookup, matrix);
    expect(InvalidParameter, status);

    status = GdipDrawDriverString(graphics, string, 4, fnt, brush, positions, DriverStringOptionsCmapLookup|0x10, matrix);
    expect(Ok, status);

    status = GdipDrawDriverString(graphics, string, 4, fnt, brush, positions, DriverStringOptionsCmapLookup, NULL);
    expect(Ok, status);

    status = GdipDrawDriverString(graphics, string, 4, fnt, brush, positions, DriverStringOptionsCmapLookup, matrix);
    expect(Ok, status);

    GdipDeleteMatrix(matrix);
    GdipDeleteGraphics(graphics);
    GdipDeleteBrush(brush);
    GdipDeleteFont(fnt);
    GdipDeleteStringFormat(format);

    ReleaseDC(hwnd, hdc);
}