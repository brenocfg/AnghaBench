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
typedef  int NET_API_STATUS ;
typedef  int NETSETUP_JOIN_STATUS ;
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int NERR_Success ; 
 int NetSetupUnknownStatus ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  pNetApiBufferFree (int /*<<< orphan*/ *) ; 
 int pNetGetJoinInformation (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void run_wkstajoininfo_tests(void)
{
    NET_API_STATUS ret;
    LPWSTR buffer = NULL;
    NETSETUP_JOIN_STATUS buffertype = 0xdada;
    /* NT4 doesn't have this function */
    if (!pNetGetJoinInformation) {
        win_skip("NetGetJoinInformation not available\n");
        return;
    }

    ret = pNetGetJoinInformation(NULL, NULL, NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "NetJoinGetInformation returned unexpected 0x%08x\n", ret);
    ok(buffertype == 0xdada, "buffertype set to unexpected value %d\n", buffertype);

    ret = pNetGetJoinInformation(NULL, &buffer, &buffertype);
    ok(ret == NERR_Success, "NetJoinGetInformation returned unexpected 0x%08x\n", ret);
    ok(buffertype != 0xdada && buffertype != NetSetupUnknownStatus, "buffertype set to unexpected value %d\n", buffertype);
    trace("workstation joined to %s with status %d\n", wine_dbgstr_w(buffer), buffertype);
    pNetApiBufferFree(buffer);
}