#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int right; int bottom; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ RECT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EqualRect (TYPE_1__*,TYPE_1__*) ; 
 int GetLastError () ; 
 int SPIF_SENDCHANGE ; 
 int SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_GETWORKAREA ; 
 int /*<<< orphan*/  SPI_SETWORKAREA ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SetRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int SystemParametersInfoA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,int,int) ; 
 int /*<<< orphan*/  test_change_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_error_msg (int,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SPI_SETWORKAREA( void )               /*     47 */
{
    BOOL rc;
    RECT old_area;
    RECT area;
    RECT curr_val;

    trace("testing SPI_{GET,SET}WORKAREA\n");
    SetLastError(0xdeadbeef);
    rc=SystemParametersInfoA(SPI_GETWORKAREA, 0, &old_area, 0);
    if (!test_error_msg(rc,"SPI_{GET,SET}WORKAREA"))
        return;

    /* Modify the work area only minimally as this causes the icons that
     * fall outside it to be moved around thus requiring the user to
     * reposition them manually one by one.
     * Changing the work area by just one pixel should make this occurrence
     * reasonably unlikely.
     */
    SetRect(&curr_val, old_area.left, old_area.top, old_area.right - 1, old_area.bottom - 1);
    rc=SystemParametersInfoA( SPI_SETWORKAREA, 0, &curr_val,
                              SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
    if (!test_error_msg(rc,"SPI_SETWORKAREA")) return;
    ok(rc, "SystemParametersInfoA: rc=%d err=%d\n", rc, GetLastError());
    rc=SystemParametersInfoA( SPI_GETWORKAREA, 0, &area, 0 );
    ok(rc, "SystemParametersInfoA: rc=%d err=%d\n", rc, GetLastError());
    if( !EqualRect( &area, &curr_val)) /* no message if rect has not changed */
        test_change_message( SPI_SETWORKAREA, 0);
    eq( area.left,   curr_val.left,   "left",   "%d" );
    eq( area.top,    curr_val.top,    "top",    "%d" );
    /* size may be rounded */
    ok( area.right >= curr_val.right - 16 && area.right < curr_val.right + 16,
        "right: got %d instead of %d\n", area.right, curr_val.right );
    ok( area.bottom >= curr_val.bottom - 16 && area.bottom < curr_val.bottom + 16,
        "bottom: got %d instead of %d\n", area.bottom, curr_val.bottom );
    curr_val = area;
    rc=SystemParametersInfoA( SPI_SETWORKAREA, 0, &old_area,
                              SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
    ok(rc, "***warning*** failed to restore the original value: rc=%d err=%d\n", rc, GetLastError());
    rc=SystemParametersInfoA( SPI_GETWORKAREA, 0, &area, 0 );
    ok(rc, "SystemParametersInfoA: rc=%d err=%d\n", rc, GetLastError());
    if( !EqualRect( &area, &curr_val)) /* no message if rect has not changed */
        test_change_message( SPI_SETWORKAREA, 0 );
    eq( area.left,   old_area.left,   "left",   "%d" );
    eq( area.top,    old_area.top,    "top",    "%d" );
    /* size may be rounded */
    ok( area.right >= old_area.right - 16 && area.right < old_area.right + 16,
        "right: got %d instead of %d\n", area.right, old_area.right );
    ok( area.bottom >= old_area.bottom - 16 && area.bottom < old_area.bottom + 16,
        "bottom: got %d instead of %d\n", area.bottom, old_area.bottom );
}