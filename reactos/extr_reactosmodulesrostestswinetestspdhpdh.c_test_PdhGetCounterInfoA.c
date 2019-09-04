#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
struct TYPE_3__ {int lScale; } ;
typedef  int PDH_STATUS ;
typedef  int /*<<< orphan*/  PDH_HQUERY ;
typedef  int /*<<< orphan*/ * PDH_HCOUNTER ;
typedef  TYPE_1__ PDH_COUNTER_INFO_A ;
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_SUCCESS ; 
 int PDH_INVALID_ARGUMENT ; 
 int PDH_INVALID_HANDLE ; 
 int PDH_MORE_DATA ; 
 int PdhAddCounterA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int PdhCloseQuery (int /*<<< orphan*/ ) ; 
 int PdhGetCounterInfoA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,TYPE_1__*) ; 
 int PdhOpenQueryA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int PdhSetCounterScaleFactor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_PdhGetCounterInfoA( void )
{
    PDH_STATUS ret;
    PDH_HQUERY query;
    PDH_HCOUNTER counter;
    PDH_COUNTER_INFO_A info;
    DWORD size;

    ret = PdhOpenQueryA( NULL, 0, &query );
    ok(ret == ERROR_SUCCESS, "PdhOpenQueryA failed 0x%08x\n", ret);

    ret = PdhAddCounterA( query, "\\System\\System Up Time", 0, &counter );
    ok(ret == ERROR_SUCCESS, "PdhAddCounterA failed 0x%08x\n", ret);

    ret = PdhGetCounterInfoA( NULL, 0, NULL, NULL );
    ok(ret == PDH_INVALID_HANDLE || ret == PDH_INVALID_ARGUMENT, "PdhGetCounterInfoA failed 0x%08x\n", ret);

    ret = PdhGetCounterInfoA( counter, 0, NULL, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhGetCounterInfoA failed 0x%08x\n", ret);

    ret = PdhGetCounterInfoA( counter, 0, NULL, &info );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhGetCounterInfoA failed 0x%08x\n", ret);

    size = sizeof(info) - 1;
    ret = PdhGetCounterInfoA( counter, 0, &size, NULL );
    ok(ret == PDH_MORE_DATA || ret == PDH_INVALID_ARGUMENT, "PdhGetCounterInfoA failed 0x%08x\n", ret);

    size = sizeof(info);
    ret = PdhGetCounterInfoA( counter, 0, &size, &info );
    ok(ret == ERROR_SUCCESS, "PdhGetCounterInfoA failed 0x%08x\n", ret);
    ok(size == sizeof(info), "PdhGetCounterInfoA failed %d\n", size);

    ret = PdhGetCounterInfoA( counter, 0, &size, &info );
    ok(ret == ERROR_SUCCESS, "PdhGetCounterInfoA failed 0x%08x\n", ret);
    ok(info.lScale == 0, "lScale %d\n", info.lScale);

    ret = PdhSetCounterScaleFactor( counter, 0 );
    ok(ret == ERROR_SUCCESS, "PdhSetCounterScaleFactor failed 0x%08x\n", ret);

    ret = PdhGetCounterInfoA( counter, 0, &size, &info );
    ok(ret == ERROR_SUCCESS, "PdhGetCounterInfoA failed 0x%08x\n", ret);
    ok(info.lScale == 0, "lScale %d\n", info.lScale);

    ret = PdhSetCounterScaleFactor( counter, -5 );
    ok(ret == ERROR_SUCCESS, "PdhSetCounterScaleFactor failed 0x%08x\n", ret);

    ret = PdhGetCounterInfoA( counter, 0, &size, &info );
    ok(ret == ERROR_SUCCESS, "PdhGetCounterInfoA failed 0x%08x\n", ret);
    ok(info.lScale == -5, "lScale %d\n", info.lScale);

    ret = PdhCloseQuery( query );
    ok(ret == ERROR_SUCCESS, "PdhCloseQuery failed 0x%08x\n", ret);
}