#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_11__ {int i_control; TYPE_5__* control; } ;
typedef  TYPE_4__ input_thread_private_t ;
struct TYPE_9__ {scalar_t__ f_val; } ;
struct TYPE_8__ {scalar_t__ i_val; } ;
struct TYPE_10__ {TYPE_2__ pos; TYPE_1__ time; } ;
struct TYPE_12__ {int i_type; TYPE_3__ param; } ;
typedef  TYPE_5__ input_control_t ;

/* Variables and functions */
 int const INPUT_CONTROL_JUMP_POSITION ; 
 int const INPUT_CONTROL_JUMP_TIME ; 
 int const INPUT_CONTROL_SET_POSITION ; 
 int const INPUT_CONTROL_SET_PROGRAM ; 
 int const INPUT_CONTROL_SET_RATE ; 
 int const INPUT_CONTROL_SET_SEEKPOINT ; 
 int const INPUT_CONTROL_SET_STATE ; 
 int const INPUT_CONTROL_SET_TIME ; 
 int const INPUT_CONTROL_SET_TITLE ; 
 TYPE_4__* input_priv (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t ControlGetReducedIndexLocked( input_thread_t *p_input,
                                            input_control_t *c )
{
    input_thread_private_t *sys = input_priv(p_input);

    if( sys->i_control == 0 )
        return 0;

    input_control_t *prev_control = &sys->control[sys->i_control - 1];
    const int i_lt = prev_control->i_type;
    const int i_ct = c->i_type;

    if( i_lt == i_ct )
    {
        if ( i_ct == INPUT_CONTROL_SET_STATE ||
             i_ct == INPUT_CONTROL_SET_RATE ||
             i_ct == INPUT_CONTROL_SET_POSITION ||
             i_ct == INPUT_CONTROL_SET_TIME ||
             i_ct == INPUT_CONTROL_SET_PROGRAM ||
             i_ct == INPUT_CONTROL_SET_TITLE ||
             i_ct == INPUT_CONTROL_SET_SEEKPOINT )
        {
            return sys->i_control - 1;
        }
        else if ( i_ct == INPUT_CONTROL_JUMP_TIME )
        {
            c->param.time.i_val += prev_control->param.time.i_val;
            return sys->i_control - 1;
        }
        else if ( i_ct == INPUT_CONTROL_JUMP_POSITION )
        {
            c->param.pos.f_val += prev_control->param.pos.f_val;
            return sys->i_control - 1;
        }
    }

    return sys->i_control;
}