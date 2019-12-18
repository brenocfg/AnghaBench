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
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ BG_NOTIFY_JOB_ERROR ; 
 scalar_t__ BG_NOTIFY_JOB_TRANSFERRED ; 
 scalar_t__ IBackgroundCopyJob_GetNotifyFlags (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_job ; 

__attribute__((used)) static void test_NotifyFlags(void)
{
    ULONG flags;
    HRESULT hr;

    /* check default flags */
    flags = 0;
    hr = IBackgroundCopyJob_GetNotifyFlags(test_job, &flags);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(flags == (BG_NOTIFY_JOB_ERROR | BG_NOTIFY_JOB_TRANSFERRED), "flags 0x%08x\n", flags);
}