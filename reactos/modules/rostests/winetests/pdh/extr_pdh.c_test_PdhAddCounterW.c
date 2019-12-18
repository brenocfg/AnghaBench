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
typedef  int /*<<< orphan*/ * PDH_HCOUNTER ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ PDH_CSTATUS_NO_COUNTER ; 
 scalar_t__ PDH_INVALID_ARGUMENT ; 
 scalar_t__ PDH_INVALID_HANDLE ; 
 scalar_t__ PDH_INVALID_PATH ; 
 scalar_t__ PdhAddCounterW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ PdhCloseQuery (int /*<<< orphan*/ *) ; 
 scalar_t__ PdhCollectQueryData (int /*<<< orphan*/ *) ; 
 scalar_t__ PdhOpenQueryW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ PdhRemoveCounter (int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/ * nonexistent_counter ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * percentage_processor_time ; 

__attribute__((used)) static void test_PdhAddCounterW( void )
{
    PDH_STATUS ret;
    PDH_HQUERY query;
    PDH_HCOUNTER counter;

    ret = PdhOpenQueryW( NULL, 0, &query );
    ok(ret == ERROR_SUCCESS, "PdhOpenQueryW failed 0x%08x\n", ret);

    ret = PdhAddCounterW( NULL, percentage_processor_time, 0, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhAddCounterW failed 0x%08x\n", ret);

    ret = PdhAddCounterW( NULL, percentage_processor_time, 0, &counter );
    ok(ret == PDH_INVALID_HANDLE, "PdhAddCounterW failed 0x%08x\n", ret);

    ret = PdhAddCounterW( query, NULL, 0, &counter );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhAddCounterW failed 0x%08x\n", ret);

    ret = PdhAddCounterW( query, percentage_processor_time, 0, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhAddCounterW failed 0x%08x\n", ret);

    ret = PdhAddCounterW( query, nonexistent_counter, 0, &counter );
    ok(ret == PDH_CSTATUS_NO_COUNTER ||
       broken(ret == PDH_INVALID_PATH), /* Win2K */
       "PdhAddCounterW failed 0x%08x\n", ret);
    ok(!counter, "PdhAddCounterW failed %p\n", counter);

    ret = PdhAddCounterW( query, percentage_processor_time, 0, &counter );
    ok(ret == ERROR_SUCCESS, "PdhAddCounterW failed 0x%08x\n", ret);

    ret = PdhCollectQueryData( NULL );
    ok(ret == PDH_INVALID_HANDLE, "PdhCollectQueryData failed 0x%08x\n", ret);

    ret = PdhCollectQueryData( counter );
    ok(ret == PDH_INVALID_HANDLE, "PdhCollectQueryData failed 0x%08x\n", ret);

    ret = PdhCollectQueryData( query );
    ok(ret == ERROR_SUCCESS, "PdhCollectQueryData failed 0x%08x\n", ret);

    ret = PdhRemoveCounter( NULL );
    ok(ret == PDH_INVALID_HANDLE, "PdhRemoveCounter failed 0x%08x\n", ret);

    ret = PdhRemoveCounter( counter );
    ok(ret == ERROR_SUCCESS, "PdhRemoveCounter failed 0x%08x\n", ret);

    ret = PdhCloseQuery( query );
    ok(ret == ERROR_SUCCESS, "PdhCloseQuery failed 0x%08x\n", ret);
}