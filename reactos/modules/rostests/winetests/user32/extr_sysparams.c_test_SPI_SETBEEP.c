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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  MB_OK ; 
 int /*<<< orphan*/  MessageBeep (int /*<<< orphan*/ ) ; 
 int SPIF_SENDCHANGE ; 
 int SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_GETBEEP ; 
 int /*<<< orphan*/  SPI_SETBEEP ; 
 int /*<<< orphan*/  SPI_SETBEEP_REGKEY ; 
 int /*<<< orphan*/  SPI_SETBEEP_VALNAME ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ SystemParametersInfoA (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 scalar_t__ SystemParametersInfoW (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  eq (scalar_t__,scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  ok (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  test_change_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_error_msg (scalar_t__,char*) ; 
 int /*<<< orphan*/  test_reg_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SPI_SETBEEP( void )                   /*      2 */
{
    BOOL rc;
    BOOL old_b;
    BOOL b;
    BOOL curr_val;

    trace("testing SPI_{GET,SET}BEEP\n");
    SetLastError(0xdeadbeef);
    rc=SystemParametersInfoA( SPI_GETBEEP, 0, &old_b, 0 );
    if (!test_error_msg(rc,"SPI_{GET,SET}BEEP"))
        return;

    curr_val = TRUE;
    rc=SystemParametersInfoA( SPI_SETBEEP, curr_val, 0, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
    if (!test_error_msg(rc,"SPI_SETBEEP")) return;
    ok(rc, "SystemParametersInfoA: rc=%d err=%d\n", rc, GetLastError());
    test_change_message( SPI_SETBEEP, 0 );
    test_reg_key( SPI_SETBEEP_REGKEY,
                  SPI_SETBEEP_VALNAME,
                  curr_val ? "Yes" : "No" );
    rc=SystemParametersInfoA( SPI_GETBEEP, 0, &b, 0 );
    ok(rc, "SystemParametersInfoA: rc=%d err=%d\n", rc, GetLastError());
    eq( b, curr_val, "SPI_{GET,SET}BEEP", "%d" );
    rc=SystemParametersInfoW( SPI_GETBEEP, 0, &b, 0 );
    if (rc || GetLastError() != ERROR_CALL_NOT_IMPLEMENTED)
    {
        ok(rc, "SystemParametersInfoW: rc=%d err=%d\n", rc, GetLastError());
        eq( b, curr_val, "SystemParametersInfoW", "%d" );
    }

    /* is a message sent for the second change? */
    rc=SystemParametersInfoA( SPI_SETBEEP, curr_val, 0, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
    ok(rc, "SystemParametersInfoA: rc=%d err=%d\n", rc, GetLastError());
    test_change_message( SPI_SETBEEP, 0 );

    curr_val = FALSE;
    rc=SystemParametersInfoW( SPI_SETBEEP, curr_val, 0, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
    if (rc == FALSE && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
        rc=SystemParametersInfoA( SPI_SETBEEP, curr_val, 0, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
    ok(rc, "SystemParametersInfo: rc=%d err=%d\n", rc, GetLastError());
    test_change_message( SPI_SETBEEP, 0 );
    test_reg_key( SPI_SETBEEP_REGKEY,
                  SPI_SETBEEP_VALNAME,
                  curr_val ? "Yes" : "No" );
    rc=SystemParametersInfoA( SPI_GETBEEP, 0, &b, 0 );
    ok(rc, "SystemParametersInfoA: rc=%d err=%d\n", rc, GetLastError());
    eq( b, curr_val, "SPI_{GET,SET}BEEP", "%d" );
    rc=SystemParametersInfoW( SPI_GETBEEP, 0, &b, 0 );
    if (rc || GetLastError() != ERROR_CALL_NOT_IMPLEMENTED)
    {
        ok(rc, "SystemParametersInfoW: rc=%d err=%d\n", rc, GetLastError());
        eq( b, curr_val, "SystemParametersInfoW", "%d" );
    }
    ok( MessageBeep( MB_OK ), "Return value of MessageBeep when sound is disabled\n" );

    rc=SystemParametersInfoA( SPI_SETBEEP, old_b, 0, SPIF_UPDATEINIFILE );
    ok(rc, "***warning*** failed to restore the original value: rc=%d err=%d\n", rc, GetLastError());
}