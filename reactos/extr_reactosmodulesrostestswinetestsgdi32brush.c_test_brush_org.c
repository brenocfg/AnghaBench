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
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBrushOrgEx (int /*<<< orphan*/ ,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ok (int,char*,int,int) ; 

__attribute__((used)) static void test_brush_org( void )
{
    HDC hdc = GetDC( 0 );
    POINT old, pt;

    SetBrushOrgEx( hdc, 0, 0, &old );

    SetBrushOrgEx( hdc, 1, 1, &pt );
    ok( pt.x == 0 && pt.y == 0, "got %d,%d\n", pt.x, pt.y );
    SetBrushOrgEx( hdc, 0x10000, -1, &pt );
    ok( pt.x == 1 && pt.y == 1, "got %d,%d\n", pt.x, pt.y );
    SetBrushOrgEx( hdc, old.x, old.y, &pt );
    ok( pt.x == 0x10000 && pt.y == -1, "got %d,%d\n", pt.x, pt.y );

    ReleaseDC( 0, hdc );
}