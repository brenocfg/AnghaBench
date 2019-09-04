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
typedef  double REAL ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpPathGradient ;
typedef  int /*<<< orphan*/  GpBrush ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreatePathGradient (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetPathGradientBlend (int /*<<< orphan*/ *,double*,double*,int) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  WrapModeClamp ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (double,double) ; 
 int /*<<< orphan*/  getblend_ptf ; 

__attribute__((used)) static void test_getblend(void)
{
    GpStatus status;
    GpPathGradient *brush;
    REAL blends[4];
    REAL pos[4];

    status = GdipCreatePathGradient(getblend_ptf, 2, WrapModeClamp, &brush);
    expect(Ok, status);

    /* check some invalid parameters combinations */
    status = GdipGetPathGradientBlend(NULL, NULL,  NULL, -1);
    expect(InvalidParameter, status);
    status = GdipGetPathGradientBlend(brush,NULL,  NULL, -1);
    expect(InvalidParameter, status);
    status = GdipGetPathGradientBlend(NULL, blends,NULL, -1);
    expect(InvalidParameter, status);
    status = GdipGetPathGradientBlend(NULL, NULL,  pos,  -1);
    expect(InvalidParameter, status);
    status = GdipGetPathGradientBlend(NULL, NULL,  NULL,  1);
    expect(InvalidParameter, status);

    blends[0] = (REAL)0xdeadbeef;
    pos[0]    = (REAL)0xdeadbeef;
    status = GdipGetPathGradientBlend(brush, blends, pos, 1);
    expect(Ok, status);
    expectf(1.0, blends[0]);
    expectf((REAL)0xdeadbeef, pos[0]);

    GdipDeleteBrush((GpBrush*) brush);
}