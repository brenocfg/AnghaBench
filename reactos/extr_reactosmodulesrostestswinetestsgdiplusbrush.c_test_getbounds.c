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
struct TYPE_3__ {int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpRectF ;
typedef  int /*<<< orphan*/  GpPathGradient ;
typedef  int /*<<< orphan*/  GpBrush ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreatePathGradient (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetPathGradientRect (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  WrapModeClamp ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getbounds_ptf ; 

__attribute__((used)) static void test_getbounds(void)
{
    GpStatus status;
    GpPathGradient *brush;
    GpRectF bounds;

    status = GdipCreatePathGradient(getbounds_ptf, 4, WrapModeClamp, &brush);
    expect(Ok, status);

    status = GdipGetPathGradientRect(NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipGetPathGradientRect(brush, NULL);
    expect(InvalidParameter, status);
    status = GdipGetPathGradientRect(NULL, &bounds);
    expect(InvalidParameter, status);

    status = GdipGetPathGradientRect(brush, &bounds);
    expect(Ok, status);
    expectf(0.0, bounds.X);
    expectf(20.0, bounds.Y);
    expectf(50.0, bounds.Width);
    expectf(30.0, bounds.Height);

    GdipDeleteBrush((GpBrush*) brush);
}