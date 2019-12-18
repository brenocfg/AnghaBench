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
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ BG_JOB_TYPE ;

/* Variables and functions */
 scalar_t__ IBackgroundCopyJob_GetType (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_job ; 
 scalar_t__ test_type ; 

__attribute__((used)) static void test_GetType(void)
{
    HRESULT hres;
    BG_JOB_TYPE type;

    hres = IBackgroundCopyJob_GetType(test_job, &type);
    ok(hres == S_OK, "GetType failed: %08x\n", hres);
    ok(type == test_type, "Got incorrect type\n");
}