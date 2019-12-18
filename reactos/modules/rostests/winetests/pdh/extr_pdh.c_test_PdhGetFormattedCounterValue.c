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
typedef  int /*<<< orphan*/  PDH_HQUERY ;
typedef  int /*<<< orphan*/ * PDH_HCOUNTER ;
typedef  int /*<<< orphan*/  PDH_FMT_COUNTERVALUE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int PDH_FMT_1000 ; 
 int PDH_FMT_LARGE ; 
 int PDH_FMT_NOCAP100 ; 
 int PDH_FMT_NOSCALE ; 
 scalar_t__ PDH_INVALID_ARGUMENT ; 
 scalar_t__ PDH_INVALID_HANDLE ; 
 scalar_t__ PdhAddCounterA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ PdhCloseQuery (int /*<<< orphan*/ ) ; 
 scalar_t__ PdhCollectQueryData (int /*<<< orphan*/ ) ; 
 scalar_t__ PdhGetFormattedCounterValue (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PdhOpenQueryA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PdhSetCounterScaleFactor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_PdhGetFormattedCounterValue( void )
{
    PDH_STATUS ret;
    PDH_HQUERY query;
    PDH_HCOUNTER counter;
    PDH_FMT_COUNTERVALUE value;

    ret = PdhOpenQueryA( NULL, 0, &query );
    ok(ret == ERROR_SUCCESS, "PdhOpenQueryA failed 0x%08x\n", ret);

    ret = PdhAddCounterA( query, "\\System\\System Up Time", 0, &counter );
    ok(ret == ERROR_SUCCESS, "PdhAddCounterA failed 0x%08x\n", ret);

    ret = PdhGetFormattedCounterValue( NULL, PDH_FMT_LARGE, NULL, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhGetFormattedCounterValue failed 0x%08x\n", ret);

    ret = PdhGetFormattedCounterValue( NULL, PDH_FMT_LARGE, NULL, &value );
    ok(ret == PDH_INVALID_HANDLE, "PdhGetFormattedCounterValue failed 0x%08x\n", ret);

    ret = PdhGetFormattedCounterValue( counter, PDH_FMT_LARGE, NULL, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhGetFormattedCounterValue failed 0x%08x\n", ret);

    ret = PdhGetFormattedCounterValue( counter, PDH_FMT_LARGE, NULL, &value );
    ok(ret == ERROR_SUCCESS, "PdhGetFormattedCounterValue failed 0x%08x\n", ret);

    ret = PdhCollectQueryData( query );
    ok(ret == ERROR_SUCCESS, "PdhCollectQueryData failed 0x%08x\n", ret);

    ret = PdhGetFormattedCounterValue( counter, PDH_FMT_LARGE, NULL, &value );
    ok(ret == ERROR_SUCCESS, "PdhGetFormattedCounterValue failed 0x%08x\n", ret);

    ret = PdhGetFormattedCounterValue( counter, PDH_FMT_LARGE | PDH_FMT_NOSCALE, NULL, &value );
    ok(ret == ERROR_SUCCESS, "PdhGetFormattedCounterValue failed 0x%08x\n", ret);

    ret = PdhGetFormattedCounterValue( counter, PDH_FMT_LARGE | PDH_FMT_NOCAP100, NULL, &value );
    ok(ret == ERROR_SUCCESS, "PdhGetFormattedCounterValue failed 0x%08x\n", ret);

    ret = PdhGetFormattedCounterValue( counter, PDH_FMT_LARGE | PDH_FMT_1000, NULL, &value );
    ok(ret == ERROR_SUCCESS, "PdhGetFormattedCounterValue failed 0x%08x\n", ret);

    ret = PdhSetCounterScaleFactor( counter, 2 );
    ok(ret == ERROR_SUCCESS, "PdhSetCounterScaleFactor failed 0x%08x\n", ret);

    ret = PdhGetFormattedCounterValue( counter, PDH_FMT_LARGE, NULL, &value );
    ok(ret == ERROR_SUCCESS, "PdhGetFormattedCounterValue failed 0x%08x\n", ret);

    ret = PdhCloseQuery( query );
    ok(ret == ERROR_SUCCESS, "PdhCloseQuery failed 0x%08x\n", ret);
}