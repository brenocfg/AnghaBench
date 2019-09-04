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
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MSACM_BroadcastNotification () ; 
 scalar_t__ MSACM_pendingBroadcast ; 
 scalar_t__ MSACM_suspendBroadcastCount ; 

void MSACM_EnableNotifications(void)
{
    if (MSACM_suspendBroadcastCount > 0) {
        MSACM_suspendBroadcastCount--;
        if (MSACM_suspendBroadcastCount == 0 && MSACM_pendingBroadcast) {
            MSACM_pendingBroadcast = FALSE;
            MSACM_BroadcastNotification();
        }
    }
}