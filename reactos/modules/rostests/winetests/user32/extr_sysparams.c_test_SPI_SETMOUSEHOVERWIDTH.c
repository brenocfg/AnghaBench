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
 int /*<<< orphan*/  SPI_GETMOUSEHOVERWIDTH ; 
 int /*<<< orphan*/  SPI_SETMOUSEHOVERWIDTH ; 
 int /*<<< orphan*/  SPI_SETMOUSEHOVERWIDTH_REGKEY ; 
 int /*<<< orphan*/  SPI_SETMOUSEHOVERWIDTH_VALNAME ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SystemParametersInfoA (int /*<<< orphan*/ ,int const,int*,int) ; 
 int /*<<< orphan*/  eq (int,int const,char*,char*) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int const) ; 
 int /*<<< orphan*/  test_change_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_error_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_reg_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SPI_SETMOUSEHOVERWIDTH( void )      /*     99 */
{
    BOOL rc;
    UINT old_width;
    const UINT vals[]={0,32767};
    unsigned int i;

    trace("testing SPI_{GET,SET}MOUSEHOVERWIDTH\n");
    SetLastError(0xdeadbeef);
    rc=SystemParametersInfoA( SPI_GETMOUSEHOVERWIDTH, 0, &old_width, 0 );
    /* SPI_{GET,SET}MOUSEHOVERWIDTH does not seem to be supported on Win9x despite
    * what MSDN states (Verified on Win98SE)
    */
    if (!test_error_msg(rc,"SPI_{GET,SET}MOUSEHOVERWIDTH"))
        return;
    
    for (i=0;i<sizeof(vals)/sizeof(*vals);i++)
    {
        UINT v;
        char buf[10];

        rc=SystemParametersInfoA( SPI_SETMOUSEHOVERWIDTH, vals[i], 0,
                               SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
        if (!test_error_msg(rc,"SPI_SETMOUSEHOVERWIDTH")) return;
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        test_change_message( SPI_SETMOUSEHOVERWIDTH, 0 );
        sprintf( buf, "%d", vals[i] );
        test_reg_key( SPI_SETMOUSEHOVERWIDTH_REGKEY,
                      SPI_SETMOUSEHOVERWIDTH_VALNAME, buf );

        SystemParametersInfoA( SPI_GETMOUSEHOVERWIDTH, 0, &v, 0 );
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        eq( v, vals[i], "SPI_{GET,SET}MOUSEHOVERWIDTH", "%d" );
    }

    rc=SystemParametersInfoA( SPI_SETMOUSEHOVERWIDTH, old_width, 0,
                              SPIF_UPDATEINIFILE );
    ok(rc, "***warning*** failed to restore the original value: rc=%d err=%d\n", rc, GetLastError());
}