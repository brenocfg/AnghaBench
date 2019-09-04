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
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpPathGradient ;
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  GpBrush ;

/* Variables and functions */
 int /*<<< orphan*/  FillModeWinding ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePathGradient (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetPathGradientPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NotImplemented ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  WrapModeClamp ; 
 int /*<<< orphan*/  blendcount_ptf ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_pathgradientpath(void)
{
    GpStatus status;
    GpPath *path=NULL;
    GpPathGradient *grad=NULL;

    status = GdipCreatePathGradient(blendcount_ptf, 2, WrapModeClamp, &grad);
    expect(Ok, status);

    status = GdipGetPathGradientPath(grad, NULL);
    expect(NotImplemented, status);

    status = GdipCreatePath(FillModeWinding, &path);
    expect(Ok, status);

    status = GdipGetPathGradientPath(NULL, path);
    expect(NotImplemented, status);

    status = GdipGetPathGradientPath(grad, path);
    expect(NotImplemented, status);

    status = GdipDeletePath(path);
    expect(Ok, status);

    status = GdipDeleteBrush((GpBrush*)grad);
    expect(Ok, status);
}