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
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_INVALID_PARAMETER_1 ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pRtlDeleteTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlDeleteTimer(void)
{
    NTSTATUS ret;

    if (!pRtlDeleteTimer)
    {
        win_skip("RtlDeleteTimer is not available\n");
        return;
    }

    ret = pRtlDeleteTimer(NULL, NULL, NULL);
    ok(ret == STATUS_INVALID_PARAMETER_1 ||
       ret == STATUS_INVALID_PARAMETER, /* W2K */
       "expected STATUS_INVALID_PARAMETER_1 or STATUS_INVALID_PARAMETER, got %x\n", ret);
}