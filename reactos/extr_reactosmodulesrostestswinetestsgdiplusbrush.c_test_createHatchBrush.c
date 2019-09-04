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
typedef  int HatchStyle ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpHatch ;
typedef  int /*<<< orphan*/  GpBrush ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateHatchBrush (int,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int HatchStyle05Percent ; 
 int HatchStyleMax ; 
 int HatchStyleMin ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_createHatchBrush(void)
{
    GpStatus status;
    GpHatch *brush;

    status = GdipCreateHatchBrush(HatchStyleMin, 1, 2, &brush);
    expect(Ok, status);
    ok(brush != NULL, "Expected the brush to be initialized.\n");

    GdipDeleteBrush((GpBrush *)brush);

    status = GdipCreateHatchBrush(HatchStyleMax, 1, 2, &brush);
    expect(Ok, status);
    ok(brush != NULL, "Expected the brush to be initialized.\n");

    GdipDeleteBrush((GpBrush *)brush);

    status = GdipCreateHatchBrush(HatchStyle05Percent, 1, 2, NULL);
    expect(InvalidParameter, status);

    status = GdipCreateHatchBrush((HatchStyle)(HatchStyleMin - 1), 1, 2, &brush);
    expect(InvalidParameter, status);

    status = GdipCreateHatchBrush((HatchStyle)(HatchStyleMax + 1), 1, 2, &brush);
    expect(InvalidParameter, status);
}