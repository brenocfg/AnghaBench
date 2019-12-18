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
 scalar_t__ PdhValidatePathW (char const*) ; 
 char const* nonexistent_counter ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 char const* system_uptime ; 
 char const* uptime ; 

__attribute__((used)) static void test_PdhValidatePathW( void )
{
    PDH_STATUS ret;

    static const WCHAR empty[] = {0};
    static const WCHAR system[] = {'\\','S','y','s','t','e','m',0};

    ret = PdhValidatePathW( NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhValidatePathW failed 0x%08x\n", ret);

    ret = PdhValidatePathW( empty );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhValidatePathW failed 0x%08x\n", ret);

    ret = PdhValidatePathW( system );
    ok(ret == PDH_CSTATUS_BAD_COUNTERNAME, "PdhValidatePathW failed 0x%08x\n", ret);

    ret = PdhValidatePathW( uptime );
    ok(ret == PDH_CSTATUS_BAD_COUNTERNAME, "PdhValidatePathW failed 0x%08x\n", ret);

    ret = PdhValidatePathW( nonexistent_counter );
    ok(ret == PDH_CSTATUS_NO_COUNTER, "PdhValidatePathW failed 0x%08x\n", ret);

    ret = PdhValidatePathW( system_uptime );
    ok(ret == ERROR_SUCCESS, "PdhValidatePathW failed 0x%08x\n", ret);
}