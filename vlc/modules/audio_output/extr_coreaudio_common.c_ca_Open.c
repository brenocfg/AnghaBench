#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct aout_sys_common {int /*<<< orphan*/ * p_out_chain; int /*<<< orphan*/  flush_sem; } ;
struct TYPE_5__ {int /*<<< orphan*/  time_get; int /*<<< orphan*/  flush; int /*<<< orphan*/  pause; int /*<<< orphan*/  play; scalar_t__ sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_6__ {scalar_t__ denom; scalar_t__ numer; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  ca_Flush ; 
 int /*<<< orphan*/  ca_Pause ; 
 int /*<<< orphan*/  ca_Play ; 
 int /*<<< orphan*/  ca_TimeGet ; 
 int /*<<< orphan*/  lock_init (struct aout_sys_common*) ; 
 scalar_t__ mach_timebase_info (TYPE_2__*) ; 
 TYPE_2__ tinfo ; 
 int /*<<< orphan*/  vlc_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ca_Open(audio_output_t *p_aout)
{
    struct aout_sys_common *p_sys = (struct aout_sys_common *) p_aout->sys;

    if (mach_timebase_info(&tinfo) != KERN_SUCCESS)
    {
        tinfo.numer = tinfo.denom = 0;
        return VLC_EGENERIC;
    }

    vlc_sem_init(&p_sys->flush_sem, 0);
    lock_init(p_sys);
    p_sys->p_out_chain = NULL;

    p_aout->play = ca_Play;
    p_aout->pause = ca_Pause;
    p_aout->flush = ca_Flush;
    p_aout->time_get = ca_TimeGet;

    return VLC_SUCCESS;
}