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
typedef  char WCHAR ;
typedef  scalar_t__ PDH_STATUS ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ PDH_CSTATUS_BAD_COUNTERNAME ; 
 scalar_t__ PDH_CSTATUS_NO_COUNTER ; 
 scalar_t__ PDH_INVALID_ARGUMENT ; 
 char const* nonexistent_counter ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pPdhValidatePathExW (int /*<<< orphan*/ *,char const*) ; 
 char const* system_uptime ; 
 char const* uptime ; 

__attribute__((used)) static void test_PdhValidatePathExW( void )
{
    PDH_STATUS ret;

    static const WCHAR empty[] = {0};
    static const WCHAR system[] = {'\\','S','y','s','t','e','m',0};

    ret = pPdhValidatePathExW( NULL, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhValidatePathExW failed 0x%08x\n", ret);

    ret = pPdhValidatePathExW( NULL, empty );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhValidatePathExW failed 0x%08x\n", ret);

    ret = pPdhValidatePathExW( NULL, system );
    ok(ret == PDH_CSTATUS_BAD_COUNTERNAME, "PdhValidatePathExW failed 0x%08x\n", ret);

    ret = pPdhValidatePathExW( NULL, uptime );
    ok(ret == PDH_CSTATUS_BAD_COUNTERNAME, "PdhValidatePathExW failed 0x%08x\n", ret);

    ret = pPdhValidatePathExW( NULL, nonexistent_counter );
    ok(ret == PDH_CSTATUS_NO_COUNTER, "PdhValidatePathExW failed 0x%08x\n", ret);

    ret = pPdhValidatePathExW( NULL, system_uptime );
    ok(ret == ERROR_SUCCESS, "PdhValidatePathExW failed 0x%08x\n", ret);
}