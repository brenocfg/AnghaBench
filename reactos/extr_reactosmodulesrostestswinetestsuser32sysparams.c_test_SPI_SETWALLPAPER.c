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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int SPIF_SENDCHANGE ; 
 int SPIF_UPDATEINIFILE ; 
 int /*<<< orphan*/  SPI_GETDESKWALLPAPER ; 
 int /*<<< orphan*/  SPI_SETDESKWALLPAPER ; 
 int /*<<< orphan*/  SPI_SETDESKWALLPAPER_REGKEY ; 
 int /*<<< orphan*/  SPI_SETDESKWALLPAPER_VALNAME ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SystemParametersInfoA (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  test_change_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_error_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_reg_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SPI_SETWALLPAPER( void )              /*   115 */
{
    BOOL rc;
    char oldval[260];
    char newval[260];

    trace("testing SPI_{GET,SET}DESKWALLPAPER\n");
    SetLastError(0xdeadbeef);
    rc=SystemParametersInfoA(SPI_GETDESKWALLPAPER, 260, oldval, 0);
    /* SPI_{GET,SET}DESKWALLPAPER is completely broken on Win9x and
     * unimplemented on NT4
     */
    if (!test_error_msg(rc,"SPI_{GET,SET}DESKWALLPAPER"))
        return;

    strcpy(newval, "");
    rc=SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, newval, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
    if (!test_error_msg(rc,"SPI_SETDESKWALLPAPER")) return;
    ok(rc, "SystemParametersInfoA: rc=%d err=%d\n", rc, GetLastError());
    test_change_message(SPI_SETDESKWALLPAPER, 0);

    rc=SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, oldval, SPIF_UPDATEINIFILE);
    ok(rc, "***warning*** failed to restore the original value: rc=%d err=%d\n", rc, GetLastError());

    test_reg_key(SPI_SETDESKWALLPAPER_REGKEY, SPI_SETDESKWALLPAPER_VALNAME, oldval);
}