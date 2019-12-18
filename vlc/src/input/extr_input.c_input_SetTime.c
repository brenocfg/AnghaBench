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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_4__ {int b_fast_seek; int /*<<< orphan*/  i_val; } ;
struct TYPE_5__ {TYPE_1__ time; } ;
typedef  TYPE_2__ input_control_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_CONTROL_SET_TIME ; 
 int /*<<< orphan*/  input_ControlPush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

void input_SetTime( input_thread_t *p_input, vlc_tick_t i_time, bool b_fast )
{
    input_control_param_t param;

    param.time.i_val = i_time;
    param.time.b_fast_seek = b_fast;
    input_ControlPush( p_input, INPUT_CONTROL_SET_TIME, &param );
}