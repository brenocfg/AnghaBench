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
typedef  int UINT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int GetDoubleClickTime () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int SPIF_SENDCHANGE ; 
 int SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_SETDOUBLECLICKTIME ; 
 int /*<<< orphan*/  SPI_SETDOUBLECLICKTIME_REGKEY ; 
 int /*<<< orphan*/  SPI_SETDOUBLECLICKTIME_VALNAME ; 
 int /*<<< orphan*/  SetDoubleClickTime (int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SystemParametersInfoA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eq (int,int,char*,char*) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  test_change_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_error_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_reg_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SPI_SETDOUBLECLICKTIME( void )        /*     32 */
{
    BOOL rc;
    UINT curr_val;
    UINT saved_val;
    UINT old_time;
    char buf[10];

    trace("testing SPI_{GET,SET}DOUBLECLICKTIME\n");
    old_time = GetDoubleClickTime();

    curr_val = 0;
    SetLastError(0xdeadbeef);
    rc=SystemParametersInfoA( SPI_SETDOUBLECLICKTIME, curr_val, 0,
                              SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
    if (!test_error_msg(rc,"SPI_{GET,SET}DOUBLECLICKTIME"))
        return;

    test_change_message( SPI_SETDOUBLECLICKTIME, 0 );
    sprintf( buf, "%d", curr_val );
    test_reg_key( SPI_SETDOUBLECLICKTIME_REGKEY,
                  SPI_SETDOUBLECLICKTIME_VALNAME, buf );
    curr_val = 500; /* used value for 0 */
    eq( GetDoubleClickTime(), curr_val, "GetDoubleClickTime", "%d" );

    curr_val = 1000;
    rc=SystemParametersInfoA( SPI_SETDOUBLECLICKTIME, curr_val, 0,
                             SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
    ok(rc, "SystemParametersInfoA: rc=%d err=%d\n", rc, GetLastError());
    test_change_message( SPI_SETDOUBLECLICKTIME, 0 );
    sprintf( buf, "%d", curr_val );
    test_reg_key( SPI_SETDOUBLECLICKTIME_REGKEY,
                  SPI_SETDOUBLECLICKTIME_VALNAME, buf );
    eq( GetDoubleClickTime(), curr_val, "GetDoubleClickTime", "%d" );

    saved_val = curr_val;

    curr_val = 0;
    SetDoubleClickTime( curr_val );
    sprintf( buf, "%d", saved_val );
    test_reg_key( SPI_SETDOUBLECLICKTIME_REGKEY,
                  SPI_SETDOUBLECLICKTIME_VALNAME, buf );
    curr_val = 500; /* used value for 0 */
    eq( GetDoubleClickTime(), curr_val, "GetDoubleClickTime", "%d" );

    curr_val = 1000;
    SetDoubleClickTime( curr_val );
    sprintf( buf, "%d", saved_val );
    test_reg_key( SPI_SETDOUBLECLICKTIME_REGKEY,
                  SPI_SETDOUBLECLICKTIME_VALNAME, buf );
    eq( GetDoubleClickTime(), curr_val, "GetDoubleClickTime", "%d" );

    rc=SystemParametersInfoA(SPI_SETDOUBLECLICKTIME, old_time, 0, SPIF_UPDATEINIFILE);
    ok(rc, "***warning*** failed to restore the original value: rc=%d err=%d\n", rc, GetLastError());
}