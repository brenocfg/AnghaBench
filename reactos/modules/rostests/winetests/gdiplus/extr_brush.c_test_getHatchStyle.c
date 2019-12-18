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
typedef  int /*<<< orphan*/  GpHatchStyle ;
typedef  int /*<<< orphan*/  GpHatch ;
typedef  int /*<<< orphan*/  GpBrush ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateHatchBrush (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetHatchStyle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HatchStyleHorizontal ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_getHatchStyle(void)
{
    GpStatus status;
    GpHatch *brush;
    GpHatchStyle hatchStyle;

    GdipCreateHatchBrush(HatchStyleHorizontal, 11, 12, &brush);

    status = GdipGetHatchStyle(NULL, &hatchStyle);
    expect(InvalidParameter, status);

    status = GdipGetHatchStyle(brush, NULL);
    expect(InvalidParameter, status);

    status = GdipGetHatchStyle(brush, &hatchStyle);
    expect(Ok, status);
    expect(HatchStyleHorizontal, hatchStyle);

    GdipDeleteBrush((GpBrush *)brush);
}