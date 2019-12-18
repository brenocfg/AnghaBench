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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_5__ {int i_control; int /*<<< orphan*/  lock_control; TYPE_2__* control; int /*<<< orphan*/  wait_control; scalar_t__ is_stopped; } ;
typedef  TYPE_1__ input_thread_private_t ;
typedef  int /*<<< orphan*/  input_control_param_t ;
struct TYPE_6__ {int i_type; int /*<<< orphan*/  param; } ;

/* Variables and functions */
 scalar_t__ ControlIsSeekRequest (int) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 TYPE_1__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (TYPE_2__*,TYPE_2__*,int) ; 
 scalar_t__ vlc_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ControlPop( input_thread_t *p_input,
                              int *pi_type, input_control_param_t *p_param,
                              vlc_tick_t i_deadline, bool b_postpone_seek )
{
    input_thread_private_t *p_sys = input_priv(p_input);

    vlc_mutex_lock( &p_sys->lock_control );
    while( p_sys->i_control <= 0 ||
           ( b_postpone_seek && ControlIsSeekRequest( p_sys->control[0].i_type ) ) )
    {
        if( p_sys->is_stopped )
        {
            vlc_mutex_unlock( &p_sys->lock_control );
            return VLC_EGENERIC;
        }

        if( i_deadline >= 0 )
        {
            if( vlc_cond_timedwait( &p_sys->wait_control, &p_sys->lock_control,
                                    i_deadline ) )
            {
                vlc_mutex_unlock( &p_sys->lock_control );
                return VLC_EGENERIC;
            }
        }
        else
            vlc_cond_wait( &p_sys->wait_control, &p_sys->lock_control );
    }

    /* */
    *pi_type = p_sys->control[0].i_type;
    *p_param   = p_sys->control[0].param;

    p_sys->i_control --;
    if( p_sys->i_control > 0 )
        memmove( &p_sys->control[0], &p_sys->control[1],
                 sizeof(*p_sys->control) * p_sys->i_control );
    vlc_mutex_unlock( &p_sys->lock_control );

    return VLC_SUCCESS;
}