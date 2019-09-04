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
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  detailed_info1_child ; 
 int /*<<< orphan*/  manifest1_child_info ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pGetCurrentActCtx (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pReleaseActCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_basic_info (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_detailed_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_info_in_assembly (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_app_manifest(void)
{
    HANDLE handle;
    BOOL b;

    trace("child process manifest1\n");

    b = pGetCurrentActCtx(&handle);
    ok(handle == NULL, "handle != NULL\n");
    ok(b, "GetCurrentActCtx failed: %u\n", GetLastError());
    if(b) {
        test_basic_info(handle, __LINE__);
        test_detailed_info(handle, &detailed_info1_child, __LINE__);
        test_info_in_assembly(handle, 1, &manifest1_child_info, __LINE__);
        pReleaseActCtx(handle);
    }
}