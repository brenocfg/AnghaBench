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
typedef  int /*<<< orphan*/  GpMatrix ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateMatrix2 (double,double,double,double,double,double,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_constructor_destructor(void)
{
    GpStatus status;
    GpMatrix *matrix = NULL;

    status = GdipCreateMatrix2(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, &matrix);
    expect(Ok, status);
    ok(matrix != NULL, "Expected matrix to be initialized\n");

    status = GdipDeleteMatrix(NULL);
    expect(InvalidParameter, status);

    status = GdipDeleteMatrix(matrix);
    expect(Ok, status);
}