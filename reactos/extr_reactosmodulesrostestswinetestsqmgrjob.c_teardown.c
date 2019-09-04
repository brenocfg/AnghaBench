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

/* Variables and functions */
 int /*<<< orphan*/  IBackgroundCopyJob_Cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBackgroundCopyJob_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBackgroundCopyManager_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_job ; 
 int /*<<< orphan*/  test_manager ; 

__attribute__((used)) static void teardown(void)
{
    IBackgroundCopyJob_Cancel(test_job);
    IBackgroundCopyJob_Release(test_job);
    IBackgroundCopyManager_Release(test_manager);
}