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
typedef  int /*<<< orphan*/  LONGLONG ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ PDH_INVALID_ARGUMENT ; 
 scalar_t__ PDH_INVALID_HANDLE ; 
 scalar_t__ PdhAddCounterA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ PdhCloseQuery (int /*<<< orphan*/ ) ; 
 scalar_t__ PdhGetCounterTimeBase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PdhOpenQueryA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_PdhGetCounterTimeBase( void )
{
    PDH_STATUS ret;
    PDH_HQUERY query;
    PDH_HCOUNTER counter;
    LONGLONG base;

    ret = PdhOpenQueryA( NULL, 0, &query );
    ok(ret == ERROR_SUCCESS, "PdhOpenQueryA failed 0x%08x\n", ret);

    ret = PdhAddCounterA( query, "\\System\\System Up Time", 0, &counter );
    ok(ret == ERROR_SUCCESS, "PdhAddCounterA failed 0x%08x\n", ret);

    ret = PdhGetCounterTimeBase( NULL, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhGetCounterTimeBase failed 0x%08x\n", ret);

    ret = PdhGetCounterTimeBase( NULL, &base );
    ok(ret == PDH_INVALID_HANDLE, "PdhGetCounterTimeBase failed 0x%08x\n", ret);

    ret = PdhGetCounterTimeBase( counter, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhGetCounterTimeBase failed 0x%08x\n", ret);

    ret = PdhGetCounterTimeBase( counter, &base );
    ok(ret == ERROR_SUCCESS, "PdhGetCounterTimeBase failed 0x%08x\n", ret);

    ret = PdhCloseQuery( query );
    ok(ret == ERROR_SUCCESS, "PdhCloseQuery failed 0x%08x\n", ret);
}