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
typedef  int UINT ;
typedef  int BOOL ;

/* Variables and functions */
 int const FALSE ; 
 int const GetLastError () ; 
 int SPIF_SENDCHANGE ; 
 int SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_GETLOWPOWERACTIVE ; 
 int /*<<< orphan*/  SPI_SETLOWPOWERACTIVE ; 
 int /*<<< orphan*/  SPI_SETLOWPOWERACTIVE_REGKEY ; 
 int /*<<< orphan*/  SPI_SETLOWPOWERACTIVE_VALNAME ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int SystemParametersInfoA (int /*<<< orphan*/ ,int const,int*,int) ; 
 int const TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int const,...) ; 
 int /*<<< orphan*/  test_change_message (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_error_msg (int,char*) ; 
 int /*<<< orphan*/  test_reg_key_optional (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SPI_SETLOWPOWERACTIVE( void )         /*     85 */
{
    BOOL rc;
    BOOL old_b;
    const UINT vals[]={TRUE,FALSE};
    unsigned int i;

    trace("testing SPI_{GET,SET}LOWPOWERACTIVE\n");
    SetLastError(0xdeadbeef);
    rc=SystemParametersInfoA( SPI_GETLOWPOWERACTIVE, 0, &old_b, 0 );
    if (!test_error_msg(rc,"SPI_{GET,SET}LOWPOWERACTIVE"))
        return;

    for (i=0;i<sizeof(vals)/sizeof(*vals);i++)
    {
        UINT v;

        rc=SystemParametersInfoA( SPI_SETLOWPOWERACTIVE, vals[i], 0,
                                  SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
        if (!test_error_msg(rc,"SPI_SETLOWPOWERACTIVE")) return;
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        test_change_message( SPI_SETLOWPOWERACTIVE, 1 );
        test_reg_key_optional( SPI_SETLOWPOWERACTIVE_REGKEY,
                               SPI_SETLOWPOWERACTIVE_VALNAME,
                               vals[i] ? "1" : "0" );

        /* SPI_SETLOWPOWERACTIVE is not persistent in win2k3 and above */
        v = 0xdeadbeef;
        rc=SystemParametersInfoA( SPI_GETLOWPOWERACTIVE, 0, &v, 0 );
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        ok(v == vals[i] ||
           broken(v == (0xdead0000 | vals[i])) ||  /* win98 only sets the low word */
           v == 0, /* win2k3 */
           "SPI_GETLOWPOWERACTIVE: got %d instead of 0 or %d\n", v, vals[i]);
    }

    rc=SystemParametersInfoA( SPI_SETLOWPOWERACTIVE, old_b, 0, SPIF_UPDATEINIFILE );
    ok(rc, "***warning*** failed to restore the original value: rc=%d err=%d\n", rc, GetLastError());
}