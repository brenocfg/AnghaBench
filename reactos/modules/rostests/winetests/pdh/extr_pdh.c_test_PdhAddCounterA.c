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
 scalar_t__ PdhAddCounterA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ PdhCloseQuery (int /*<<< orphan*/ *) ; 
 scalar_t__ PdhCollectQueryData (int /*<<< orphan*/ *) ; 
 scalar_t__ PdhOpenQueryA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ PdhRemoveCounter (int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_PdhAddCounterA( void )
{
    PDH_STATUS ret;
    PDH_HQUERY query;
    PDH_HCOUNTER counter;

    ret = PdhOpenQueryA( NULL, 0, &query );
    ok(ret == ERROR_SUCCESS, "PdhOpenQueryA failed 0x%08x\n", ret);

    ret = PdhAddCounterA( NULL, "\\System\\System Up Time", 0, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhAddCounterA failed 0x%08x\n", ret);

    ret = PdhAddCounterA( NULL, "\\System\\System Up Time", 0, &counter );
    ok(ret == PDH_INVALID_HANDLE, "PdhAddCounterA failed 0x%08x\n", ret);

    ret = PdhAddCounterA( query, NULL, 0, &counter );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhAddCounterA failed 0x%08x\n", ret);

    ret = PdhAddCounterA( query, "\\System\\System Up Time", 0, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhAddCounterA failed 0x%08x\n", ret);

    ret = PdhAddCounterA( query, "\\System\\Nonexistent Counter", 0, &counter );
    ok(ret == PDH_CSTATUS_NO_COUNTER ||
       broken(ret == PDH_INVALID_PATH), /* Win2K */
       "PdhAddCounterA failed 0x%08x\n", ret);
    ok(!counter, "PdhAddCounterA failed %p\n", counter);

    ret = PdhAddCounterA( query, "\\System\\System Up Time", 0, &counter );
    ok(ret == ERROR_SUCCESS, "PdhAddCounterA failed 0x%08x\n", ret);

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