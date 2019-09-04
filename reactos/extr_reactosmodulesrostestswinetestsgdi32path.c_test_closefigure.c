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
struct TYPE_3__ {int x; int y; } ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  AbortPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BeginPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseFigure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EndPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentPositionEx (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetPath (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_closefigure(void) {
    int nSize, nSizeWitness;
    POINT pos;
    HDC hdc = GetDC(0);

    MoveToEx( hdc, 100, 100, NULL );
    GetCurrentPositionEx( hdc, &pos );
    ok( pos.x == 100 && pos.y == 100, "wrong pos %d,%d\n", pos.x, pos.y );

    BeginPath(hdc);
    GetCurrentPositionEx( hdc, &pos );
    ok( pos.x == 100 && pos.y == 100, "wrong pos %d,%d\n", pos.x, pos.y );
    MoveToEx(hdc, 95, 95, NULL);
    GetCurrentPositionEx( hdc, &pos );
    ok( pos.x == 95 && pos.y == 95, "wrong pos %d,%d\n", pos.x, pos.y );
    LineTo(hdc, 95,  0);
    GetCurrentPositionEx( hdc, &pos );
    ok( pos.x == 95 && pos.y == 0, "wrong pos %d,%d\n", pos.x, pos.y );
    LineTo(hdc,  0, 95);
    GetCurrentPositionEx( hdc, &pos );
    ok( pos.x == 0 && pos.y == 95, "wrong pos %d,%d\n", pos.x, pos.y );

    CloseFigure(hdc);
    GetCurrentPositionEx( hdc, &pos );
    ok( pos.x == 0 && pos.y == 95, "wrong pos %d,%d\n", pos.x, pos.y );
    EndPath(hdc);
    GetCurrentPositionEx( hdc, &pos );
    ok( pos.x == 0 && pos.y == 95, "wrong pos %d,%d\n", pos.x, pos.y );
    nSize = GetPath(hdc, NULL, NULL, 0);

    AbortPath(hdc);

    BeginPath(hdc);
    MoveToEx(hdc, 95, 95, NULL);
    LineTo(hdc, 95,  0);
    LineTo(hdc,  0, 95);

    EndPath(hdc);
    nSizeWitness = GetPath(hdc, NULL, NULL, 0);

    /* This test shows CloseFigure does not have to add a point at the end of the path */
    ok(nSize == nSizeWitness, "Wrong number of points, no point should be added by CloseFigure\n");

    ReleaseDC(0, hdc);
}