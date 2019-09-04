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
struct TYPE_3__ {int cbSize; int iWidth; int iHorzGap; int iVertGap; int iArrange; } ;
typedef  TYPE_1__ MINIMIZEDMETRICS ;
typedef  int INT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GetLastError () ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_ARRANGE ; 
 int /*<<< orphan*/  SM_CXMINIMIZED ; 
 int /*<<< orphan*/  SM_CXMINSPACING ; 
 int /*<<< orphan*/  SM_CYMINIMIZED ; 
 int /*<<< orphan*/  SM_CYMINSPACING ; 
 int /*<<< orphan*/  SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_GETMINIMIZEDMETRICS ; 
 int /*<<< orphan*/  SPI_MINARRANGE_VALNAME ; 
 int /*<<< orphan*/  SPI_MINHORZGAP_VALNAME ; 
 int /*<<< orphan*/  SPI_MINIMIZEDMETRICS_REGKEY ; 
 int /*<<< orphan*/  SPI_MINVERTGAP_VALNAME ; 
 int /*<<< orphan*/  SPI_MINWIDTH_VALNAME ; 
 int /*<<< orphan*/  SPI_SETMINIMIZEDMETRICS ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int SystemParametersInfoA (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpi ; 
 int /*<<< orphan*/  eq (int,int,char*,char*) ; 
 int metricfromreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int,int) ; 
 int /*<<< orphan*/  test_error_msg (int,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SPI_SETMINIMIZEDMETRICS( void )               /*     44 */
{
    BOOL rc;
    INT regval;
    MINIMIZEDMETRICS lpMm_orig;
    MINIMIZEDMETRICS lpMm_new;
    MINIMIZEDMETRICS lpMm_cur;

    lpMm_orig.cbSize = sizeof(MINIMIZEDMETRICS);
    lpMm_new.cbSize = sizeof(MINIMIZEDMETRICS);
    lpMm_cur.cbSize = sizeof(MINIMIZEDMETRICS);

    trace("testing SPI_{GET,SET}MINIMIZEDMETRICS\n");
    SetLastError(0xdeadbeef);
    rc=SystemParametersInfoA( SPI_GETMINIMIZEDMETRICS, sizeof(MINIMIZEDMETRICS), &lpMm_orig, FALSE );
    if (!test_error_msg(rc,"SPI_{GET,SET}MINIMIZEDMETRICS"))
        return;
    /* Test registry. Note that it is perfectly valid for some fields to
     * not be set.
     */
    regval = metricfromreg( SPI_MINIMIZEDMETRICS_REGKEY, SPI_MINWIDTH_VALNAME, dpi);
    ok( regval == -1 || regval == lpMm_orig.iWidth, "wrong value in registry %d, expected %d\n",
        regval, lpMm_orig.iWidth);
    regval = metricfromreg( SPI_MINIMIZEDMETRICS_REGKEY, SPI_MINHORZGAP_VALNAME, dpi);
    ok( regval == -1 || regval == lpMm_orig.iHorzGap, "wrong value in registry %d, expected %d\n",
        regval, lpMm_orig.iHorzGap);
    regval = metricfromreg( SPI_MINIMIZEDMETRICS_REGKEY, SPI_MINVERTGAP_VALNAME, dpi);
    ok( regval == -1 || regval == lpMm_orig.iVertGap, "wrong value in registry %d, expected %d\n",
        regval, lpMm_orig.iVertGap);
    regval = metricfromreg( SPI_MINIMIZEDMETRICS_REGKEY, SPI_MINARRANGE_VALNAME, dpi);
    ok( regval == -1 || regval == lpMm_orig.iArrange, "wrong value in registry %d, expected %d\n",
        regval, lpMm_orig.iArrange);
    /* set some new values */
    lpMm_cur.iWidth = 180;
    lpMm_cur.iHorzGap = 1;
    lpMm_cur.iVertGap = 1;
    lpMm_cur.iArrange = 5;
    rc=SystemParametersInfoA( SPI_SETMINIMIZEDMETRICS, sizeof(MINIMIZEDMETRICS),
        &lpMm_cur, SPIF_UPDATEINIFILE );
    if (!test_error_msg(rc,"SPI_SETMINIMIZEDMETRICS")) return;
    ok(rc, "SystemParametersInfoA: rc=%d err=%d\n", rc, GetLastError());
    /* read them back */
    rc=SystemParametersInfoA( SPI_GETMINIMIZEDMETRICS, sizeof(MINIMIZEDMETRICS), &lpMm_new, FALSE );
    ok(rc, "SystemParametersInfoA: rc=%d err=%d\n", rc, GetLastError());
    /* and compare */
    eq( lpMm_new.iWidth,   lpMm_cur.iWidth,   "iWidth",   "%d" );
    eq( lpMm_new.iHorzGap, lpMm_cur.iHorzGap, "iHorzGap", "%d" );
    eq( lpMm_new.iVertGap, lpMm_cur.iVertGap, "iVertGap", "%d" );
    eq( lpMm_new.iArrange, lpMm_cur.iArrange, "iArrange", "%d" );
    /* test registry */
    regval = metricfromreg( SPI_MINIMIZEDMETRICS_REGKEY, SPI_MINWIDTH_VALNAME, dpi);
    ok( regval == lpMm_new.iWidth, "wrong value in registry %d, expected %d\n",
        regval, lpMm_new.iWidth);
    regval = metricfromreg( SPI_MINIMIZEDMETRICS_REGKEY, SPI_MINHORZGAP_VALNAME, dpi);
    ok( regval == lpMm_new.iHorzGap, "wrong value in registry %d, expected %d\n",
        regval, lpMm_new.iHorzGap);
    regval = metricfromreg( SPI_MINIMIZEDMETRICS_REGKEY, SPI_MINVERTGAP_VALNAME, dpi);
    ok( regval == lpMm_new.iVertGap, "wrong value in registry %d, expected %d\n",
        regval, lpMm_new.iVertGap);
    regval = metricfromreg( SPI_MINIMIZEDMETRICS_REGKEY, SPI_MINARRANGE_VALNAME, dpi);
    ok( regval == lpMm_new.iArrange, "wrong value in registry %d, expected %d\n",
        regval, lpMm_new.iArrange);
    /* test some system metrics */
    eq( GetSystemMetrics( SM_CXMINIMIZED ) - 6,
        lpMm_new.iWidth,   "iWidth",   "%d" );
    eq( GetSystemMetrics( SM_CXMINSPACING ) - GetSystemMetrics( SM_CXMINIMIZED ),
        lpMm_new.iHorzGap, "iHorzGap", "%d" );
    eq( GetSystemMetrics( SM_CYMINSPACING ) - GetSystemMetrics( SM_CYMINIMIZED ),
        lpMm_new.iVertGap, "iVertGap", "%d" );
    eq( GetSystemMetrics( SM_ARRANGE ),
        lpMm_new.iArrange, "iArrange", "%d" );
    /* now some really invalid settings */
    lpMm_cur.iWidth = -1;
    lpMm_cur.iHorzGap = -1;
    lpMm_cur.iVertGap = -1;
    lpMm_cur.iArrange = - 1;
    rc=SystemParametersInfoA( SPI_SETMINIMIZEDMETRICS, sizeof(MINIMIZEDMETRICS),
        &lpMm_cur, SPIF_UPDATEINIFILE );
    ok(rc, "SystemParametersInfoA: rc=%d err=%d\n", rc, GetLastError());
    /* read back */
    rc=SystemParametersInfoA( SPI_GETMINIMIZEDMETRICS, sizeof(MINIMIZEDMETRICS), &lpMm_new, FALSE );
    ok(rc, "SystemParametersInfoA: rc=%d err=%d\n", rc, GetLastError());
    /* the width and H/V gaps have minimum 0, arrange is and'd with 0xf */
    eq( lpMm_new.iWidth,   0,   "iWidth",   "%d" );
    eq( lpMm_new.iHorzGap, 0, "iHorzGap", "%d" );
    eq( lpMm_new.iVertGap, 0, "iVertGap", "%d" );
    eq( lpMm_new.iArrange, 0xf & lpMm_cur.iArrange, "iArrange", "%d" );
    /* test registry */
    if (0)
    {
    /* FIXME: cannot understand the results of this (11, 11, 11, 0) */
    regval = metricfromreg( SPI_MINIMIZEDMETRICS_REGKEY, SPI_MINWIDTH_VALNAME, dpi);
    ok( regval == lpMm_new.iWidth, "wrong value in registry %d, expected %d\n",
        regval, lpMm_new.iWidth);
    regval = metricfromreg( SPI_MINIMIZEDMETRICS_REGKEY, SPI_MINHORZGAP_VALNAME, dpi);
    ok( regval == lpMm_new.iHorzGap, "wrong value in registry %d, expected %d\n",
        regval, lpMm_new.iHorzGap);
    regval = metricfromreg( SPI_MINIMIZEDMETRICS_REGKEY, SPI_MINVERTGAP_VALNAME, dpi);
    ok( regval == lpMm_new.iVertGap, "wrong value in registry %d, expected %d\n",
        regval, lpMm_new.iVertGap);
    regval = metricfromreg( SPI_MINIMIZEDMETRICS_REGKEY, SPI_MINARRANGE_VALNAME, dpi);
    ok( regval == lpMm_new.iArrange, "wrong value in registry %d, expected %d\n",
        regval, lpMm_new.iArrange);
    }
    /* test some system metrics */
    eq( GetSystemMetrics( SM_CXMINIMIZED ) - 6,
        lpMm_new.iWidth,   "iWidth",   "%d" );
    eq( GetSystemMetrics( SM_CXMINSPACING ) - GetSystemMetrics( SM_CXMINIMIZED ),
        lpMm_new.iHorzGap, "iHorzGap", "%d" );
    eq( GetSystemMetrics( SM_CYMINSPACING ) - GetSystemMetrics( SM_CYMINIMIZED ),
        lpMm_new.iVertGap, "iVertGap", "%d" );
    eq( GetSystemMetrics( SM_ARRANGE ),
        lpMm_new.iArrange, "iArrange", "%d" );
    /* restore */
    rc=SystemParametersInfoA( SPI_SETMINIMIZEDMETRICS, sizeof(MINIMIZEDMETRICS),
        &lpMm_orig, SPIF_UPDATEINIFILE );
    ok(rc, "***warning*** failed to restore the original value: rc=%d err=%d\n", rc, GetLastError());
    /* check that */
    rc=SystemParametersInfoA( SPI_GETMINIMIZEDMETRICS, sizeof(MINIMIZEDMETRICS), &lpMm_new, FALSE );
    ok(rc, "SystemParametersInfoA: rc=%d err=%d\n", rc, GetLastError());
    eq( lpMm_new.iWidth,   lpMm_orig.iWidth,   "iWidth",   "%d" );
    eq( lpMm_new.iHorzGap, lpMm_orig.iHorzGap, "iHorzGap", "%d" );
    eq( lpMm_new.iVertGap, lpMm_orig.iVertGap, "iVertGap", "%d" );
    eq( lpMm_new.iArrange, lpMm_orig.iArrange, "iArrange", "%d" );
}