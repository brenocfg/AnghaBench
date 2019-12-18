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
struct aout_sys_common {int b_do_flush; int b_played; scalar_t__ i_render_frames; scalar_t__ i_first_render_host_time; scalar_t__ i_render_host_time; int /*<<< orphan*/  flush_sem; scalar_t__ b_paused; } ;
struct TYPE_4__ {scalar_t__ sys; } ;
typedef  TYPE_1__ audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ca_ClearOutBuffers (TYPE_1__*) ; 
 int /*<<< orphan*/  lock_lock (struct aout_sys_common*) ; 
 int /*<<< orphan*/  lock_unlock (struct aout_sys_common*) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 

void
ca_Flush(audio_output_t *p_aout)
{
    struct aout_sys_common *p_sys = (struct aout_sys_common *) p_aout->sys;

    lock_lock(p_sys);

    assert(!p_sys->b_do_flush);
    if (p_sys->b_paused)
        ca_ClearOutBuffers(p_aout);
    else
    {
        p_sys->b_do_flush = true;
        lock_unlock(p_sys);
        vlc_sem_wait(&p_sys->flush_sem);
        lock_lock(p_sys);
    }

    p_sys->i_render_host_time = p_sys->i_first_render_host_time = 0;
    p_sys->i_render_frames = 0;
    lock_unlock(p_sys);

    p_sys->b_played = false;
}