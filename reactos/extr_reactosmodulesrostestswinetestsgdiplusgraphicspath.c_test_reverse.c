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
struct TYPE_3__ {int X; double Y; } ;
typedef  int REAL ;
typedef  int INT ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpPointF ;
typedef  int /*<<< orphan*/  GpPath ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathLine2 (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  GdipClosePathFigure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipReversePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reverse_path ; 

__attribute__((used)) static void test_reverse(void)
{
    GpStatus status;
    GpPath *path;
    GpPointF pts[7];
    INT i;

    for(i = 0; i < 7; i++){
        pts[i].X = i * 5.0 * (REAL)(i % 2);
        pts[i].Y = 50.0 - i * 5.0;
    }

    GdipCreatePath(FillModeAlternate, &path);

    /* NULL argument */
    status = GdipReversePath(NULL);
    expect(InvalidParameter, status);

    /* empty path */
    status = GdipReversePath(path);
    expect(Ok, status);

    GdipAddPathLine2(path, pts, 4);
    GdipClosePathFigure(path);
    GdipAddPathLine2(path, &(pts[4]), 3);

    status = GdipReversePath(path);
    expect(Ok, status);
    ok_path(path, reverse_path, ARRAY_SIZE(reverse_path), FALSE);

    GdipDeletePath(path);
}