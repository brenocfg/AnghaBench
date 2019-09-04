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
typedef  int INT ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpPathGradient ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  int ARGB ;

/* Variables and functions */
 int GdipCreatePathGradient (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int GdipGetPathGradientSurroundColorCount (int /*<<< orphan*/ *,int*) ; 
 int GdipGetPathGradientSurroundColorsWithCount (int /*<<< orphan*/ *,int*,int*) ; 
 int GdipSetPathGradientSurroundColorsWithCount (int /*<<< orphan*/ *,int*,int*) ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  WrapModeClamp ; 
 int /*<<< orphan*/  blendcount_ptf ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  getbounds_ptf ; 

__attribute__((used)) static void test_gradientsurroundcolorcount(void)
{
    GpStatus status;
    GpPathGradient *grad;
    ARGB color[3];
    INT count;

    status = GdipCreatePathGradient(blendcount_ptf, 2, WrapModeClamp, &grad);
    expect(Ok, status);

    count = 0;
    status = GdipGetPathGradientSurroundColorCount(grad, &count);
    expect(Ok, status);
    expect(2, count);

    color[0] = color[1] = color[2] = 0xdeadbeef;
    count = 3;
    status = GdipGetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(Ok, status);
    expect(1, count);
    expect(0xffffffff, color[0]);
    expect(0xffffffff, color[1]);
    expect(0xdeadbeef, color[2]);

    color[0] = color[1] = color[2] = 0xdeadbeef;
    count = 2;
    status = GdipGetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(Ok, status);
    expect(1, count);
    expect(0xffffffff, color[0]);
    expect(0xffffffff, color[1]);
    expect(0xdeadbeef, color[2]);

    color[0] = color[1] = color[2] = 0xdeadbeef;
    count = 1;
    status = GdipGetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(InvalidParameter, status);
    expect(1, count);
    expect(0xdeadbeef, color[0]);
    expect(0xdeadbeef, color[1]);
    expect(0xdeadbeef, color[2]);

    color[0] = color[1] = color[2] = 0xdeadbeef;
    count = 0;
    status = GdipGetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(InvalidParameter, status);
    expect(0, count);
    expect(0xdeadbeef, color[0]);
    expect(0xdeadbeef, color[1]);
    expect(0xdeadbeef, color[2]);

    count = 3;
    status = GdipSetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(InvalidParameter, status);

    count = 2;

    color[0] = 0x00ff0000;
    color[1] = 0x0000ff00;

    status = GdipSetPathGradientSurroundColorsWithCount(NULL, color, &count);
    expect(InvalidParameter, status);

    status = GdipSetPathGradientSurroundColorsWithCount(grad, NULL, &count);
    expect(InvalidParameter, status);

    /* WinXP crashes on this test */
    if(0)
    {
        status = GdipSetPathGradientSurroundColorsWithCount(grad, color, NULL);
        expect(InvalidParameter, status);
    }

    status = GdipSetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(Ok, status);
    expect(2, count);

    status = GdipGetPathGradientSurroundColorCount(NULL, &count);
    expect(InvalidParameter, status);

    status = GdipGetPathGradientSurroundColorCount(grad, NULL);
    expect(InvalidParameter, status);

    count = 0;
    status = GdipGetPathGradientSurroundColorCount(grad, &count);
    expect(Ok, status);
    expect(2, count);

    color[0] = color[1] = color[2] = 0xdeadbeef;
    count = 2;
    status = GdipGetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(Ok, status);
    expect(2, count);
    expect(0x00ff0000, color[0]);
    expect(0x0000ff00, color[1]);
    expect(0xdeadbeef, color[2]);

    count = 1;
    status = GdipSetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(Ok, status);
    expect(1, count);

    count = 0;
    status = GdipGetPathGradientSurroundColorCount(grad, &count);
    expect(Ok, status);
    expect(2, count);

    /* If all colors are the same, count is set to 1. */
    color[0] = color[1] = 0;
    count = 2;
    status = GdipSetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(Ok, status);
    expect(2, count);

    color[0] = color[1] = color[2] = 0xdeadbeef;
    count = 2;
    status = GdipGetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(Ok, status);
    expect(1, count);
    expect(0x00000000, color[0]);
    expect(0x00000000, color[1]);
    expect(0xdeadbeef, color[2]);

    color[0] = color[1] = 0xff00ff00;
    count = 2;
    status = GdipSetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(Ok, status);
    expect(2, count);

    color[0] = color[1] = color[2] = 0xdeadbeef;
    count = 2;
    status = GdipGetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(Ok, status);
    expect(1, count);
    expect(0xff00ff00, color[0]);
    expect(0xff00ff00, color[1]);
    expect(0xdeadbeef, color[2]);

    count = 0;
    status = GdipSetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(InvalidParameter, status);
    expect(0, count);

    GdipDeleteBrush((GpBrush*)grad);

    status = GdipCreatePathGradient(getbounds_ptf, 3, WrapModeClamp, &grad);
    expect(Ok, status);

    color[0] = color[1] = color[2] = 0xdeadbeef;
    count = 3;
    status = GdipGetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(Ok, status);
    expect(1, count);
    expect(0xffffffff, color[0]);
    expect(0xffffffff, color[1]);
    expect(0xffffffff, color[2]);

    color[0] = color[1] = color[2] = 0xdeadbeef;
    count = 2;
    status = GdipGetPathGradientSurroundColorsWithCount(grad, color, &count);
    expect(InvalidParameter, status);
    expect(2, count);
    expect(0xdeadbeef, color[0]);
    expect(0xdeadbeef, color[1]);
    expect(0xdeadbeef, color[2]);

    count = 0;
    status = GdipGetPathGradientSurroundColorCount(grad, &count);
    expect(Ok, status);
    expect(3, count);

    GdipDeleteBrush((GpBrush*)grad);
}