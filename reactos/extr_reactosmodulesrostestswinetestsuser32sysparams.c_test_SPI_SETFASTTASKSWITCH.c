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
 int /*<<< orphan*/  SPI_GETFASTTASKSWITCH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SystemParametersInfoA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_error_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SPI_SETFASTTASKSWITCH( void )         /*     36 */
{
    BOOL rc;
    BOOL v;

    trace("testing SPI_GETFASTTASKSWITCH\n");
    SetLastError(0xdeadbeef);
    rc=SystemParametersInfoA( SPI_GETFASTTASKSWITCH, 0, &v, 0 );
    if (!test_error_msg(rc,"SPI_{GET,SET}FASTTASKSWITCH"))
        return;

    /* there is not a single Windows platform on which SPI_GETFASTTASKSWITCH
     * works. That sure simplifies testing!
     */
}