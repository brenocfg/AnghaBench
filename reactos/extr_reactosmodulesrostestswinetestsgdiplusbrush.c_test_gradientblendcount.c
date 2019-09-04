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
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpPathGradient ;
typedef  int /*<<< orphan*/  GpBrush ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreatePathGradient (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetPathGradientBlendCount (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  WrapModeClamp ; 
 int /*<<< orphan*/  blendcount_ptf ; 
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_gradientblendcount(void)
{
    GpStatus status;
    GpPathGradient *brush;
    INT count;

    status = GdipCreatePathGradient(blendcount_ptf, 2, WrapModeClamp, &brush);
    expect(Ok, status);

    status = GdipGetPathGradientBlendCount(NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipGetPathGradientBlendCount(NULL, &count);
    expect(InvalidParameter, status);
    status = GdipGetPathGradientBlendCount(brush, NULL);
    expect(InvalidParameter, status);

    status = GdipGetPathGradientBlendCount(brush, &count);
    expect(Ok, status);
    expect(1, count);

    GdipDeleteBrush((GpBrush*) brush);
}