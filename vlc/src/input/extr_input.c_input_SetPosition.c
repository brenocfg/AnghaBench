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
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_4__ {float f_val; int b_fast_seek; } ;
struct TYPE_5__ {TYPE_1__ pos; } ;
typedef  TYPE_2__ input_control_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_CONTROL_SET_POSITION ; 
 int /*<<< orphan*/  input_ControlPush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

void input_SetPosition( input_thread_t *p_input, float f_position, bool b_fast )
{
    input_control_param_t param;

    param.pos.f_val = f_position;
    param.pos.b_fast_seek = b_fast;
    input_ControlPush( p_input, INPUT_CONTROL_SET_POSITION, &param );
}