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
 scalar_t__ PdhOpenQueryA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ PdhRemoveCounter (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pPdhAddEnglishCounterA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void test_PdhAddEnglishCounterA( void )
{
    PDH_STATUS ret;
    PDH_HQUERY query;
    PDH_HCOUNTER counter;

    ret = PdhOpenQueryA( NULL, 0, &query );
    ok(ret == ERROR_SUCCESS, "PdhOpenQueryA failed 0x%08x\n", ret);

    ret = PdhCollectQueryData( query );
    ok(ret == PDH_NO_DATA, "PdhCollectQueryData failed 0x%08x\n", ret);

    ret = pPdhAddEnglishCounterA( NULL, "\\System\\System Up Time", 0, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhAddEnglishCounterA failed 0x%08x\n", ret);

    ret = pPdhAddEnglishCounterA( NULL, "\\System\\System Up Time", 0, &counter );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhAddEnglishCounterA failed 0x%08x\n", ret);

    ret = pPdhAddEnglishCounterA( query, NULL, 0, &counter );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhAddEnglishCounterA failed 0x%08x\n", ret);

    ret = pPdhAddEnglishCounterA( query, "\\System\\System Up Time", 0, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhAddEnglishCounterA failed 0x%08x\n", ret);

    ret = pPdhAddEnglishCounterA( query, "\\System\\System Down Time", 0, &counter );
    ok(ret == PDH_CSTATUS_NO_COUNTER, "PdhAddEnglishCounterA failed 0x%08x\n", ret);
    ok(!counter, "PdhAddEnglishCounterA failed %p\n", counter);

    ret = pPdhAddEnglishCounterA( query, "\\System\\System Up Time", 0, &counter );
    ok(ret == ERROR_SUCCESS, "PdhAddEnglishCounterA failed 0x%08x\n", ret);

    ret = PdhCollectQueryData( query );
    ok(ret == ERROR_SUCCESS, "PdhCollectQueryData failed 0x%08x\n", ret);

    ret = PdhRemoveCounter( counter );
    ok(ret == ERROR_SUCCESS, "PdhRemoveCounter failed 0x%08x\n", ret);

    ret = PdhCloseQuery( query );
    ok(ret == ERROR_SUCCESS, "PdhCloseQuery failed 0x%08x\n", ret);
}