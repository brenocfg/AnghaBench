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

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ PDH_INVALID_ARGUMENT ; 
 scalar_t__ PDH_INVALID_HANDLE ; 
 scalar_t__ PdhCloseQuery (int /*<<< orphan*/ *) ; 
 scalar_t__ PdhOpenQueryA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_PdhOpenQueryA( void )
{
    PDH_STATUS ret;
    PDH_HQUERY query;

    ret = PdhOpenQueryA( NULL, 0, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhOpenQueryA failed 0x%08x\n", ret);

    ret = PdhOpenQueryA( NULL, 0, &query );
    ok(ret == ERROR_SUCCESS, "PdhOpenQueryA failed 0x%08x\n", ret);

    ret = PdhCloseQuery( NULL );
    ok(ret == PDH_INVALID_HANDLE, "PdhCloseQuery failed 0x%08x\n", ret);

    ret = PdhCloseQuery( &query );
    ok(ret == PDH_INVALID_HANDLE, "PdhCloseQuery failed 0x%08x\n", ret);

    ret = PdhCloseQuery( query );
    ok(ret == ERROR_SUCCESS, "PdhCloseQuery failed 0x%08x\n", ret);

    ret = PdhCloseQuery( query );
    ok(ret == PDH_INVALID_HANDLE, "PdhCloseQuery failed 0x%08x\n", ret);
}