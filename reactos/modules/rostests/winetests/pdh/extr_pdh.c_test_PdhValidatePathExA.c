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

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ PDH_CSTATUS_BAD_COUNTERNAME ; 
 scalar_t__ PDH_CSTATUS_NO_COUNTER ; 
 scalar_t__ PDH_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pPdhValidatePathExA (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_PdhValidatePathExA( void )
{
    PDH_STATUS ret;

    ret = pPdhValidatePathExA( NULL, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhValidatePathExA failed 0x%08x\n", ret);

    ret = pPdhValidatePathExA( NULL, "" );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhValidatePathExA failed 0x%08x\n", ret);

    ret = pPdhValidatePathExA( NULL, "\\System" );
    ok(ret == PDH_CSTATUS_BAD_COUNTERNAME, "PdhValidatePathExA failed 0x%08x\n", ret);

    ret = pPdhValidatePathExA( NULL, "System Up Time" );
    ok(ret == PDH_CSTATUS_BAD_COUNTERNAME, "PdhValidatePathExA failed 0x%08x\n", ret);

    ret = pPdhValidatePathExA( NULL, "\\System\\System Down Time" );
    ok(ret == PDH_CSTATUS_NO_COUNTER, "PdhValidatePathExA failed 0x%08x\n", ret);

    ret = pPdhValidatePathExA( NULL, "\\System\\System Up Time" );
    ok(ret == ERROR_SUCCESS, "PdhValidatePathExA failed 0x%08x\n", ret);
}