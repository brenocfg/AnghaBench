#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct aout_sys_common {int b_paused; int b_do_flush; int b_played; int /*<<< orphan*/  flush_sem; } ;
struct TYPE_4__ {scalar_t__ sys; } ;
typedef  TYPE_1__ audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  ca_ClearOutBuffers (TYPE_1__*) ; 
 int /*<<< orphan*/  lock_lock (struct aout_sys_common*) ; 
 int /*<<< orphan*/  lock_unlock (struct aout_sys_common*) ; 
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 

void
ca_SetAliveState(audio_output_t *p_aout, bool alive)
{
    struct aout_sys_common *p_sys = (struct aout_sys_common *) p_aout->sys;

    lock_lock(p_sys);

    bool b_sem_post = false;
    p_sys->b_paused = !alive;
    if (!alive && p_sys->b_do_flush)
    {
        ca_ClearOutBuffers(p_aout);
        p_sys->b_played = false;
        p_sys->b_do_flush = false;
        b_sem_post = true;
    }

    lock_unlock(p_sys);

    if (b_sem_post)
        vlc_sem_post(&p_sys->flush_sem);
}