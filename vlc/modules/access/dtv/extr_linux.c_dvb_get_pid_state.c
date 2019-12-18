#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {TYPE_1__* pids; scalar_t__ budget; } ;
typedef  TYPE_2__ dvb_device_t ;
struct TYPE_4__ {scalar_t__ pid; } ;

/* Variables and functions */
 size_t MAX_PIDS ; 

bool dvb_get_pid_state (const dvb_device_t *d, uint16_t pid)
{
    if (d->budget)
        return true;

    for (size_t i = 0; i < MAX_PIDS; i++)
        if (d->pids[i].pid == pid)
            return true;

    return false;
}