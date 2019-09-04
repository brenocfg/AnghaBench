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
typedef  scalar_t__ PDH_STATUS ;
typedef  int /*<<< orphan*/ * PDH_HQUERY ;
typedef  scalar_t__ PDH_HCOUNTER ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ PDH_CSTATUS_NO_COUNTER ; 
 scalar_t__ PDH_INVALID_ARGUMENT ; 
 scalar_t__ PDH_NO_DATA ; 
 scalar_t__ PdhCloseQuery (int /*<<< orphan*/ *) ; 
 scalar_t__ PdhCollectQueryData (int /*<<< orphan*/ *) ; 
 scalar_t__ PdhOpenQueryW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ PdhRemoveCounter (scalar_t__) ; 
 int /*<<< orphan*/ * nonexistent_counter ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pPdhAddEnglishCounterW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/ * system_uptime ; 

__attribute__((used)) static void test_PdhAddEnglishCounterW( void )
{
    PDH_STATUS ret;
    PDH_HQUERY query;
    PDH_HCOUNTER counter;

    ret = PdhOpenQueryW( NULL, 0, &query );
    ok(ret == ERROR_SUCCESS, "PdhOpenQueryW failed 0x%08x\n", ret);

    ret = PdhCollectQueryData( query );
    ok(ret == PDH_NO_DATA, "PdhCollectQueryData failed 0x%08x\n", ret);

    ret = pPdhAddEnglishCounterW( NULL, system_uptime, 0, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhAddEnglishCounterW failed 0x%08x\n", ret);

    ret = pPdhAddEnglishCounterW( NULL, system_uptime, 0, &counter );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhAddEnglishCounterW failed 0x%08x\n", ret);

    ret = pPdhAddEnglishCounterW( query, NULL, 0, &counter );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhAddEnglishCounterW failed 0x%08x\n", ret);

    ret = pPdhAddEnglishCounterW( query, system_uptime, 0, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhAddEnglishCounterW failed 0x%08x\n", ret);

    ret = pPdhAddEnglishCounterW( query, nonexistent_counter, 0, &counter );
    ok(ret == PDH_CSTATUS_NO_COUNTER, "PdhAddEnglishCounterW failed 0x%08x\n", ret);
    ok(!counter, "PdhAddEnglishCounterA failed %p\n", counter);

    ret = pPdhAddEnglishCounterW( query, system_uptime, 0, &counter );
    ok(ret == ERROR_SUCCESS, "PdhAddEnglishCounterW failed 0x%08x\n", ret);

    ret = PdhCollectQueryData( query );
    ok(ret == ERROR_SUCCESS, "PdhCollectQueryData failed 0x%08x\n", ret);

    ret = PdhRemoveCounter( counter );
    ok(ret == ERROR_SUCCESS, "PdhRemoveCounter failed 0x%08x\n", ret);

    ret = PdhCloseQuery( query );
    ok(ret == ERROR_SUCCESS, "PdhCloseQuery failed 0x%08x\n", ret);
}