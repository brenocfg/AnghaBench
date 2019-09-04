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
struct TYPE_4__ {double X; double Y; } ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpPointF ;
typedef  int /*<<< orphan*/  GpLineGradient ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateLineBrush (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetLineGammaCorrection (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  WrapModeTile ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_getgamma(void)
{
    GpStatus status;
    GpLineGradient *line;
    GpPointF start, end;
    BOOL gamma;

    start.X = start.Y = 0.0;
    end.X = end.Y = 100.0;

    status = GdipCreateLineBrush(&start, &end, (ARGB)0xdeadbeef, 0xdeadbeef, WrapModeTile, &line);
    expect(Ok, status);

    /* NULL arguments */
    status = GdipGetLineGammaCorrection(NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipGetLineGammaCorrection(line, NULL);
    expect(InvalidParameter, status);
    status = GdipGetLineGammaCorrection(NULL, &gamma);
    expect(InvalidParameter, status);

    GdipDeleteBrush((GpBrush*)line);
}