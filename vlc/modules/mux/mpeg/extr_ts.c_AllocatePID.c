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
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_6__ {int i_pid_video; int i_pid_audio; int i_pid_spu; } ;
typedef  TYPE_2__ sout_mux_sys_t ;

/* Variables and functions */
#define  AUDIO_ES 130 
 int GetNextFreePID (TYPE_1__*,int) ; 
#define  SPU_ES 129 
#define  VIDEO_ES 128 

__attribute__((used)) static int  AllocatePID( sout_mux_t *p_mux, int i_cat )
{
    sout_mux_sys_t *p_sys = p_mux->p_sys;
    int i_pid;
    int *pi_candidate_pid = NULL;

    switch( i_cat )
    {
    case VIDEO_ES:
        pi_candidate_pid = &p_sys->i_pid_video;
        break;

    case AUDIO_ES:
        pi_candidate_pid = &p_sys->i_pid_audio;
        break;

    case SPU_ES:
    default:
        pi_candidate_pid = &p_sys->i_pid_spu;
        break;
    }

    *pi_candidate_pid = GetNextFreePID( p_mux, *pi_candidate_pid );
    i_pid = (*pi_candidate_pid)++;

    return i_pid;
}