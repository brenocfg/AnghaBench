#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct aout_sys_common {int /*<<< orphan*/  i_dev_latency_us; } ;
struct TYPE_3__ {scalar_t__ sys; } ;
typedef  TYPE_1__ audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  lock_lock (struct aout_sys_common*) ; 
 int /*<<< orphan*/  lock_unlock (struct aout_sys_common*) ; 

void ca_SetDeviceLatency(audio_output_t *p_aout, vlc_tick_t i_dev_latency_us)
{
    struct aout_sys_common *p_sys = (struct aout_sys_common *) p_aout->sys;

    lock_lock(p_sys);
    p_sys->i_dev_latency_us = i_dev_latency_us;
    lock_unlock(p_sys);
}