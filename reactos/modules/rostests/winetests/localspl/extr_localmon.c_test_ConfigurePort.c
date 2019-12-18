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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  pConfigurePort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * portname_com1W ; 
 int /*<<< orphan*/ * portname_fileW ; 
 int /*<<< orphan*/ * portname_lpt1W ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void test_ConfigurePort(void)
{
    DWORD   res;

    /* moved to localui.dll since w2k */
    if (!pConfigurePort) return;

    if (0)
    {
        /* NT4 crash on this test */
        pConfigurePort(NULL, 0, NULL);
    }

    /*  Testing-Results (localmon.dll from NT4.0):
        - Case of Portname is ignored
        - "COM1:" and "COM01:" are the same (Compared by value)
        - Portname without ":" => Dialog "Nothing to configure" comes up; Success
        - "LPT1:", "LPT0:" and "LPT:" are the same (Numbers in "LPT:" are ignored)
        - Empty Servername (LPT1:) => Dialog comes up (Servername is ignored)
        - "FILE:" => Dialog "Nothing to configure" comes up; Success
        - Empty Portname =>  => Dialog "Nothing to configure" comes up; Success
        - Port "does_not_exist" => Dialog "Nothing to configure" comes up; Success
    */
    if (winetest_interactive > 0) {

        SetLastError(0xdeadbeef);
        res = pConfigurePort(NULL, 0, portname_com1W);
        trace("returned %d with %u\n", res, GetLastError());

        SetLastError(0xdeadbeef);
        res = pConfigurePort(NULL, 0, portname_lpt1W);
        trace("returned %d with %u\n", res, GetLastError());

        SetLastError(0xdeadbeef);
        res = pConfigurePort(NULL, 0, portname_fileW);
        trace("returned %d with %u\n", res, GetLastError());
    }
}