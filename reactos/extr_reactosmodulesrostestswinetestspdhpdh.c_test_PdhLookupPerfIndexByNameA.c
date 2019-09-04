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
typedef  int PDH_STATUS ;
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_SUCCESS ; 
 int PDH_INVALID_ARGUMENT ; 
 int PDH_STRING_NOT_FOUND ; 
 int PdhLookupPerfIndexByNameA (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_PdhLookupPerfIndexByNameA( void )
{
    PDH_STATUS ret;
    DWORD index;

    ret = PdhLookupPerfIndexByNameA( NULL, NULL, NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhLookupPerfIndexByNameA failed 0x%08x\n", ret);

    ret = PdhLookupPerfIndexByNameA( NULL, NULL, &index );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhLookupPerfIndexByNameA failed 0x%08x\n", ret);

    ret = PdhLookupPerfIndexByNameA( NULL, "No Counter", &index );
    ok(ret == PDH_STRING_NOT_FOUND, "PdhLookupPerfIndexByNameA failed 0x%08x\n", ret);

    ret = PdhLookupPerfIndexByNameA( NULL, "% Processor Time", NULL );
    ok(ret == PDH_INVALID_ARGUMENT, "PdhLookupPerfIndexByNameA failed 0x%08x\n", ret);

    ret = PdhLookupPerfIndexByNameA( NULL, "% Processor Time", &index );
    ok(ret == ERROR_SUCCESS, "PdhLookupPerfIndexByNameA failed 0x%08x\n", ret);
    ok(index == 6, "PdhLookupPerfIndexByNameA failed %d\n", index);

    ret = PdhLookupPerfIndexByNameA( NULL, "System Up Time", &index );
    ok(ret == ERROR_SUCCESS, "PdhLookupPerfIndexByNameA failed 0x%08x\n", ret);
    ok(index == 674, "PdhLookupPerfIndexByNameA failed %d\n", index);
}