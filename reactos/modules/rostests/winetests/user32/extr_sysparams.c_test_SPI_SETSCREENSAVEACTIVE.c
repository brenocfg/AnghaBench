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
typedef  int /*<<< orphan*/  vals ;
typedef  int const UINT ;
typedef  int BOOL ;

/* Variables and functions */
 int const FALSE ; 
 int const GetLastError () ; 
 int SPIF_SENDCHANGE ; 
 int SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_GETSCREENSAVEACTIVE ; 
 int /*<<< orphan*/  SPI_SETSCREENSAVEACTIVE ; 
 int /*<<< orphan*/  SPI_SETSCREENSAVEACTIVE_REGKEY ; 
 int /*<<< orphan*/  SPI_SETSCREENSAVEACTIVE_VALNAME ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int SystemParametersInfoA (int /*<<< orphan*/ ,int const,int const*,int) ; 
 int const TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int const,int const,...) ; 
 int /*<<< orphan*/  test_change_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_error_msg (int,char*) ; 
 int /*<<< orphan*/  test_reg_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SPI_SETSCREENSAVEACTIVE( void )       /*     17 */
{
    BOOL rc;
    BOOL old_b;
    const UINT vals[]={TRUE,FALSE};
    unsigned int i;

    trace("testing SPI_{GET,SET}SCREENSAVEACTIVE\n");
    SetLastError(0xdeadbeef);
    rc=SystemParametersInfoA( SPI_GETSCREENSAVEACTIVE, 0, &old_b, 0 );
    if (!test_error_msg(rc,"SPI_{GET,SET}SCREENSAVEACTIVE"))
        return;

    for (i=0;i<sizeof(vals)/sizeof(*vals);i++)
    {
        UINT v;

        rc=SystemParametersInfoA( SPI_SETSCREENSAVEACTIVE, vals[i], 0,
                                  SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
        if (!test_error_msg(rc,"SPI_SETSCREENSAVEACTIVE")) return;
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        test_change_message( SPI_SETSCREENSAVEACTIVE, 0 );
        test_reg_key( SPI_SETSCREENSAVEACTIVE_REGKEY,
                      SPI_SETSCREENSAVEACTIVE_VALNAME,
                      vals[i] ? "1" : "0" );

        rc=SystemParametersInfoA( SPI_GETSCREENSAVEACTIVE, 0, &v, 0 );
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        ok(v == vals[i] || broken(! v) /* Win 7 */,
           "SPI_{GET,SET}SCREENSAVEACTIVE: got %d instead of %d\n", v, vals[i]);
    }

    rc=SystemParametersInfoA( SPI_SETSCREENSAVEACTIVE, old_b, 0, SPIF_UPDATEINIFILE );
    ok(rc, "***warning*** failed to restore the original value: rc=%d err=%d\n", rc, GetLastError());
}