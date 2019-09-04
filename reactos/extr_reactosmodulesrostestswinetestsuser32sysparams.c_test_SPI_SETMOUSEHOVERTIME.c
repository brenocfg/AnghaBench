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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int SPIF_SENDCHANGE ; 
 int SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_GETMOUSEHOVERTIME ; 
 int /*<<< orphan*/  SPI_SETMOUSEHOVERTIME ; 
 int /*<<< orphan*/  SPI_SETMOUSEHOVERTIME_REGKEY ; 
 int /*<<< orphan*/  SPI_SETMOUSEHOVERTIME_VALNAME ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SystemParametersInfoA (int /*<<< orphan*/ ,int const,int*,int) ; 
 int /*<<< orphan*/  eq (int,int const,char*,char*) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int const) ; 
 int /*<<< orphan*/  test_change_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_error_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_reg_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SPI_SETMOUSEHOVERTIME( void )      /*     103 */
{
    BOOL rc;
    UINT old_time;

    /* Windows XP accepts 10 as the minimum hover time. Any value below will be
     * defaulted to a value of 10 automatically.
     */
    const UINT vals[]={10,32767};
    unsigned int i;

    trace("testing SPI_{GET,SET}MOUSEHOVERTIME\n");
    SetLastError(0xdeadbeef);
    rc=SystemParametersInfoA( SPI_GETMOUSEHOVERTIME, 0, &old_time, 0 );
    /* SPI_{GET,SET}MOUSEHOVERWIDTH does not seem to be supported on Win9x despite
     * what MSDN states (Verified on Win98SE)
     */    
    if (!test_error_msg(rc,"SPI_{GET,SET}MOUSEHOVERTIME"))
        return;
    
    for (i=0;i<sizeof(vals)/sizeof(*vals);i++)
    {
        UINT v;
        char buf[10];

        rc=SystemParametersInfoA( SPI_SETMOUSEHOVERTIME, vals[i], 0,
                               SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
        if (!test_error_msg(rc,"SPI_SETMOUSEHOVERTIME")) return;
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        test_change_message( SPI_SETMOUSEHOVERTIME, 0 );
        sprintf( buf, "%d", vals[i] );
        test_reg_key( SPI_SETMOUSEHOVERTIME_REGKEY,
                      SPI_SETMOUSEHOVERTIME_VALNAME, buf );

        SystemParametersInfoA( SPI_GETMOUSEHOVERTIME, 0, &v, 0 );
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        eq( v, vals[i], "SPI_{GET,SET}MOUSEHOVERTIME", "%d" );
    }

    rc=SystemParametersInfoA( SPI_SETMOUSEHOVERTIME, old_time, 0,
                              SPIF_UPDATEINIFILE );
    ok(rc, "***warning*** failed to restore the original value: rc=%d err=%d\n", rc, GetLastError());
}