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
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int const GetLastError () ; 
 int SPIF_SENDCHANGE ; 
 int SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_GETFONTSMOOTHING ; 
 int /*<<< orphan*/  SPI_GETFONTSMOOTHINGCONTRAST ; 
 int /*<<< orphan*/  SPI_GETFONTSMOOTHINGORIENTATION ; 
 int /*<<< orphan*/  SPI_GETFONTSMOOTHINGTYPE ; 
 int /*<<< orphan*/  SPI_SETFONTSMOOTHING ; 
 int /*<<< orphan*/  SPI_SETFONTSMOOTHINGCONTRAST ; 
 int /*<<< orphan*/  SPI_SETFONTSMOOTHINGCONTRAST_VALNAME ; 
 int /*<<< orphan*/  SPI_SETFONTSMOOTHINGORIENTATION ; 
 int /*<<< orphan*/  SPI_SETFONTSMOOTHINGORIENTATION_VALNAME ; 
 int /*<<< orphan*/  SPI_SETFONTSMOOTHINGTYPE ; 
 int /*<<< orphan*/  SPI_SETFONTSMOOTHINGTYPE_VALNAME ; 
 int /*<<< orphan*/  SPI_SETFONTSMOOTHING_REGKEY ; 
 int /*<<< orphan*/  SPI_SETFONTSMOOTHING_VALNAME ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int SystemParametersInfoA (int /*<<< orphan*/ ,int const,int*,int) ; 
 int* UlongToPtr (int const) ; 
 int /*<<< orphan*/  eq (int,int,char*,char*) ; 
 scalar_t__ iswin9x ; 
 int /*<<< orphan*/  ok (int,char*,int,int const,...) ; 
 int /*<<< orphan*/  test_change_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_error_msg (int,char*) ; 
 int /*<<< orphan*/  test_reg_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_reg_key_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SPI_SETFONTSMOOTHING( void )         /*     75 */
{
    BOOL rc;
    BOOL old_b;
    DWORD old_type, old_contrast, old_orient;
    const UINT vals[]={0xffffffff,0,1,2};
    unsigned int i;

    trace("testing SPI_{GET,SET}FONTSMOOTHING\n");
    if( iswin9x) return; /* 95/98/ME don't seem to implement this fully */ 
    SetLastError(0xdeadbeef);
    rc=SystemParametersInfoA( SPI_GETFONTSMOOTHING, 0, &old_b, 0 );
    if (!test_error_msg(rc,"SPI_{GET,SET}FONTSMOOTHING"))
        return;
    SystemParametersInfoA( SPI_GETFONTSMOOTHINGTYPE, 0, &old_type, 0 );
    SystemParametersInfoA( SPI_GETFONTSMOOTHINGCONTRAST, 0, &old_contrast, 0 );
    SystemParametersInfoA( SPI_GETFONTSMOOTHINGORIENTATION, 0, &old_orient, 0 );

    for (i=0;i<sizeof(vals)/sizeof(*vals);i++)
    {
        UINT v;

        rc=SystemParametersInfoA( SPI_SETFONTSMOOTHING, vals[i], 0,
                                  SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
        if (!test_error_msg(rc,"SPI_SETFONTSMOOTHING")) return;
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        test_change_message( SPI_SETFONTSMOOTHING, 0 );
        test_reg_key( SPI_SETFONTSMOOTHING_REGKEY,
                      SPI_SETFONTSMOOTHING_VALNAME,
                      vals[i] ? "2" : "0" );

        rc=SystemParametersInfoA( SPI_SETFONTSMOOTHINGTYPE, 0, UlongToPtr(vals[i]),
                                  SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
        if (!test_error_msg(rc,"SPI_SETFONTSMOOTHINGTYPE")) return;
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        test_change_message( SPI_SETFONTSMOOTHINGTYPE, 0 );
        test_reg_key_dword( SPI_SETFONTSMOOTHING_REGKEY,
                            SPI_SETFONTSMOOTHINGTYPE_VALNAME, &vals[i] );

        rc=SystemParametersInfoA( SPI_SETFONTSMOOTHINGCONTRAST, 0, UlongToPtr(vals[i]),
                                  SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
        if (!test_error_msg(rc,"SPI_SETFONTSMOOTHINGCONTRAST")) return;
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        test_change_message( SPI_SETFONTSMOOTHINGCONTRAST, 0 );
        test_reg_key_dword( SPI_SETFONTSMOOTHING_REGKEY,
                            SPI_SETFONTSMOOTHINGCONTRAST_VALNAME, &vals[i] );

        rc=SystemParametersInfoA( SPI_SETFONTSMOOTHINGORIENTATION, 0, UlongToPtr(vals[i]),
                                  SPIF_UPDATEINIFILE | SPIF_SENDCHANGE );
        if (!test_error_msg(rc,"SPI_SETFONTSMOOTHINGORIENTATION")) return;
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        test_change_message( SPI_SETFONTSMOOTHINGORIENTATION, 0 );
        test_reg_key_dword( SPI_SETFONTSMOOTHING_REGKEY,
                            SPI_SETFONTSMOOTHINGORIENTATION_VALNAME, &vals[i] );

        rc=SystemParametersInfoA( SPI_GETFONTSMOOTHING, 0, &v, 0 );
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        eq( v, vals[i] ? 1 : 0, "SPI_GETFONTSMOOTHING", "%d" );

        rc=SystemParametersInfoA( SPI_GETFONTSMOOTHINGTYPE, 0, &v, 0 );
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        ok( v == vals[i], "wrong value %x/%x\n", v, vals[i] );

        rc=SystemParametersInfoA( SPI_GETFONTSMOOTHINGCONTRAST, 0, &v, 0 );
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        ok( v == vals[i], "wrong value %x/%x\n", v, vals[i] );

        rc=SystemParametersInfoA( SPI_GETFONTSMOOTHINGORIENTATION, 0, &v, 0 );
        ok(rc, "%d: rc=%d err=%d\n", i, rc, GetLastError());
        ok( v == vals[i], "wrong value %x/%x\n", v, vals[i] );
    }

    rc=SystemParametersInfoA( SPI_SETFONTSMOOTHING, old_b, 0, SPIF_UPDATEINIFILE );
    ok(rc, "***warning*** failed to restore the original value: rc=%d err=%d\n", rc, GetLastError());
    rc=SystemParametersInfoA( SPI_SETFONTSMOOTHINGTYPE, old_type, 0, SPIF_UPDATEINIFILE );
    ok(rc, "***warning*** failed to restore the original value: rc=%d err=%d\n", rc, GetLastError());
    rc=SystemParametersInfoA( SPI_SETFONTSMOOTHINGCONTRAST, old_contrast, 0, SPIF_UPDATEINIFILE );
    ok(rc, "***warning*** failed to restore the original value: rc=%d err=%d\n", rc, GetLastError());
    rc=SystemParametersInfoA( SPI_SETFONTSMOOTHINGORIENTATION, old_orient, 0, SPIF_UPDATEINIFILE );
    ok(rc, "***warning*** failed to restore the original value: rc=%d err=%d\n", rc, GetLastError());
}