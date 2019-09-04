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
typedef  int /*<<< orphan*/  REAL ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpPen ;
typedef  int /*<<< orphan*/  GpMatrix ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateMatrix (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetMatrixElements (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetPenTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_pen_transform(GpPen *pen, REAL *values)
{
    GpMatrix *matrix;
    GpStatus status;

    status = GdipCreateMatrix(&matrix);
    expect(Ok, status);

    status = GdipGetPenTransform(pen, matrix);
    expect(Ok, status);
    status = GdipGetMatrixElements(matrix, values);
    expect(Ok, status);

    GdipDeleteMatrix(matrix);
}