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
typedef  int INT ;
typedef  int /*<<< orphan*/  HPEN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AbortPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BeginPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreatePen (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ERROR_CAN_NOT_COMPLETE ; 
 int /*<<< orphan*/  EndPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetLastError () ; 
 int GetPath (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_SOLID ; 
 int /*<<< orphan*/  Polyline (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  RGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WidenPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_widenpath(void)
{
    HDC hdc = GetDC(0);
    HPEN greenPen, narrowPen;
    POINT pnt[6];
    INT nSize;
    BOOL ret;

    /* Create a pen to be used in WidenPath */
    greenPen = CreatePen(PS_SOLID, 10, RGB(0,0,0));
    SelectObject(hdc, greenPen);

    /* Prepare a path */
    pnt[0].x = 100;
    pnt[0].y = 0;
    pnt[1].x = 200;
    pnt[1].y = 0;
    pnt[2].x = 300;
    pnt[2].y = 100;
    pnt[3].x = 300;
    pnt[3].y = 200;
    pnt[4].x = 200;
    pnt[4].y = 300;
    pnt[5].x = 100;
    pnt[5].y = 300;

    /* Set a polyline path */
    BeginPath(hdc);
    Polyline(hdc, pnt, 6);
    EndPath(hdc);

    /* Widen the polyline path */
    ok(WidenPath(hdc), "WidenPath fails while widening a poyline path.\n");

    /* Test if WidenPath seems to have done his job */
    nSize = GetPath(hdc, NULL, NULL, 0);
    ok(nSize != -1, "GetPath fails after calling WidenPath.\n");
    ok(nSize > 6, "Path number of points is too low. Should be more than 6 but is %d\n", nSize);

    AbortPath(hdc);

    /* Test WidenPath with an open path (last error only set on Win2k and later) */
    SetLastError(0xdeadbeef);
    BeginPath(hdc);
    ret = WidenPath(hdc);
    ok(ret == FALSE && (GetLastError() == ERROR_CAN_NOT_COMPLETE || GetLastError() == 0xdeadbeef),
       "WidenPath fails while widening an open path. Return value is %d, should be %d. Error is %u\n", ret, FALSE, GetLastError());

    AbortPath(hdc);

    /* Test when the pen width is equal to 1. The path should change too */
    narrowPen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
    SelectObject(hdc, narrowPen);
    BeginPath(hdc);
    Polyline(hdc, pnt, 6);
    EndPath(hdc);
    ret = WidenPath(hdc);
    ok(ret == TRUE, "WidenPath failed: %d\n", GetLastError());
    nSize = GetPath(hdc, NULL, NULL, 0);
    ok(nSize > 6, "WidenPath should compute a widened path with a 1px wide pen. Path length is %d, should be more than 6\n", nSize);

    ReleaseDC(0, hdc);
    return;
}