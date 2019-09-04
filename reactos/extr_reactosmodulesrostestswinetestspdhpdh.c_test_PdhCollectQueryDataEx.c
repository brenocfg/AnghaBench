#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_2__ {int /*<<< orphan*/  largeValue; } ;
typedef  scalar_t__ PDH_STATUS ;
typedef  int /*<<< orphan*/ * PDH_HQUERY ;
typedef  int /*<<< orphan*/  PDH_HCOUNTER ;
typedef  int /*<<< orphan*/  PDH_FMT_COUNTERVALUE ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateEventA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  PDH_FMT_LARGE ; 
 scalar_t__ PDH_INVALID_HANDLE ; 
 scalar_t__ PdhAddCounterA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PdhCloseQuery (int /*<<< orphan*/ *) ; 
 scalar_t__ PdhCollectQueryData (int /*<<< orphan*/ *) ; 
 scalar_t__ PdhCollectQueryDataEx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ PdhGetFormattedCounterValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PdhOpenQueryA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_1__ U (int /*<<< orphan*/ ) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_PdhCollectQueryDataEx(void)
{
    PDH_STATUS status;
    PDH_HQUERY query;
    PDH_HCOUNTER counter;
    HANDLE event;
    BOOL ret;
    UINT i;

    status = PdhOpenQueryA( NULL, 0, &query );
    ok(status == ERROR_SUCCESS, "PdhOpenQuery failed 0x%08x\n", status);

    event = CreateEventA( NULL, FALSE, FALSE, "winetest" );
    ok(event != NULL, "CreateEvent failed\n");

    status = PdhAddCounterA( query, "\\System\\System Up Time", 0, &counter );
    ok(status == ERROR_SUCCESS, "PdhAddCounterA failed 0x%08x\n", status);

    status = PdhCollectQueryDataEx( NULL, 1, event );
    ok(status == PDH_INVALID_HANDLE, "PdhCollectQueryDataEx failed 0x%08x\n", status);

    status = PdhCollectQueryDataEx( query, 1, NULL );
    ok(status == ERROR_SUCCESS, "PdhCollectQueryDataEx failed 0x%08x\n", status);

    status = PdhCollectQueryDataEx( query, 1, event );
    ok(status == ERROR_SUCCESS, "PdhCollectQueryDataEx failed 0x%08x\n", status);

    status = PdhCollectQueryData( query );
    ok(status == ERROR_SUCCESS, "PdhCollectQueryData failed 0x%08x\n", status);

    for (i = 0; i < 3; i++)
    {
        if (WaitForSingleObject( event, INFINITE ) == WAIT_OBJECT_0)
        {
            PDH_FMT_COUNTERVALUE value;

            status = PdhGetFormattedCounterValue( counter, PDH_FMT_LARGE, NULL, &value );
            ok(status == ERROR_SUCCESS, "PdhGetFormattedCounterValue failed 0x%08x\n", status);

            trace( "uptime %s\n", wine_dbgstr_longlong(U(value).largeValue) );
        }
    }

    ret = CloseHandle( event );
    ok(ret, "CloseHandle failed\n");

    status = PdhCloseQuery( query );
    ok(status == ERROR_SUCCESS, "PdhCloseQuery failed 0x%08x\n", status);
}