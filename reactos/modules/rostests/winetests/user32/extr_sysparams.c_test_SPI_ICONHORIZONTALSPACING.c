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
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_ICONHORIZONTALSPACING ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SystemParametersInfoA (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dotest_spi_iconhorizontalspacing (int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_error_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SPI_ICONHORIZONTALSPACING( void )     /*     13 */
{
    BOOL rc;
    INT old_spacing;

    trace("testing SPI_ICONHORIZONTALSPACING\n");
    SetLastError(0xdeadbeef);
    /* default value: 75 */
    rc=SystemParametersInfoA( SPI_ICONHORIZONTALSPACING, 0, &old_spacing, 0 );
    if (!test_error_msg(rc,"SPI_ICONHORIZONTALSPACING"))
        return;
    /* do not increase the value as it would upset the user's icon layout */
    if (!dotest_spi_iconhorizontalspacing( old_spacing - 1)) return;
    dotest_spi_iconhorizontalspacing( 10); /* minimum is 32 */
    /* restore */
    rc=SystemParametersInfoA( SPI_ICONHORIZONTALSPACING, old_spacing, 0, SPIF_UPDATEINIFILE );
    ok(rc, "***warning*** failed to restore the original value: rc=%d err=%d\n", rc, GetLastError());
}