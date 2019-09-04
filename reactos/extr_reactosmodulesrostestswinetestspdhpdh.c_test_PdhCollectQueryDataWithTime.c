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
typedef  int /*<<< orphan*/  PDH_HCOUNTER ;
typedef  int /*<<< orphan*/  LONGLONG ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ PDH_INVALID_ARGUMENT ; 
 scalar_t__ PDH_INVALID_HANDLE ; 
 scalar_t__ PDH_NO_DATA ; 
 scalar_t__ PdhAddCounterA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PdhCloseQuery (int /*<<< orphan*/ *) ; 
 scalar_t__ PdhCollectQueryData (int /*<<< orphan*/ *) ; 
 scalar_t__ PdhOpenQueryA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pPdhCollectQueryDataWithTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_PdhCollectQueryDataWithTime( void )
{
    PDH_STATUS ret;
    PDH_HQUERY query;
    PDH_HCOUNTER counter;
    LONGLONG time;

    ret = PdhOpenQueryA( NULL, 0, &query );
    ok(ret == ERROR_SUCCESS, "PdhOpenQueryA failed 0x%08x\n", ret);

    ret = PdhCollectQueryData( query );
    ok(ret == PDH_NO_DATA, "PdhCollectQueryData failed 0x%08x\n", ret);

    ret = PdhAddCounterA( query, "\\System\\System Up Time", 0, &counter );
    ok(ret == ERROR_SUCCESS, "PdhAddCounterA failed 0x%08x\n", ret);

    ret = pPdhCollectQueryDataWithTime( NULL, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhCollectQueryDataWithTime failed 0x%08x\n", ret);

    ret = pPdhCollectQueryDataWithTime( query, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhCollectQueryDataWithTime failed 0x%08x\n", ret);

    ret = pPdhCollectQueryDataWithTime( NULL, &time );
    ok(ret == PDH_INVALID_HANDLE, "PdhCollectQueryDataWithTime failed 0x%08x\n", ret);

    ret = pPdhCollectQueryDataWithTime( query, &time );
    ok(ret == ERROR_SUCCESS, "PdhCollectQueryDataWithTime failed 0x%08x\n", ret);

    ret = PdhCloseQuery( query );
    ok(ret == ERROR_SUCCESS, "PdhCloseQuery failed 0x%08x\n", ret);
}