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
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_5__ {size_t i_control; int /*<<< orphan*/  lock_control; int /*<<< orphan*/  wait_control; TYPE_2__* control; scalar_t__ is_stopped; } ;
typedef  TYPE_1__ input_thread_private_t ;
struct TYPE_6__ {int i_type; int /*<<< orphan*/  param; } ;
typedef  TYPE_2__ input_control_t ;
typedef  int /*<<< orphan*/  input_control_param_t ;

/* Variables and functions */
 size_t ControlGetReducedIndexLocked (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ControlRelease (int,int /*<<< orphan*/  const*) ; 
 size_t INPUT_CONTROL_FIFO_SIZE ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 TYPE_1__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int input_ControlPush( input_thread_t *p_input,
                       int i_type, const input_control_param_t *p_param )
{
    input_thread_private_t *sys = input_priv(p_input);

    vlc_mutex_lock( &sys->lock_control );
    input_control_t c = {
        .i_type = i_type,
    };
    if( p_param )
        c.param = *p_param;

    size_t i_next_control_idx = ControlGetReducedIndexLocked( p_input, &c );

    if( sys->is_stopped || i_next_control_idx >= INPUT_CONTROL_FIFO_SIZE )
    {
        if( sys->is_stopped )
            msg_Dbg( p_input, "input control stopped, trashing type=%d",
                     i_type );
        else
            msg_Err( p_input, "input control fifo overflow, trashing type=%d",
                     i_type );
        if( p_param )
            ControlRelease( i_type, p_param );
        vlc_mutex_unlock( &sys->lock_control );
        return VLC_EGENERIC;
    }

    sys->control[i_next_control_idx] = c;
    sys->i_control = i_next_control_idx + 1;

    vlc_cond_signal( &sys->wait_control );
    vlc_mutex_unlock( &sys->lock_control );
    return VLC_SUCCESS;
}