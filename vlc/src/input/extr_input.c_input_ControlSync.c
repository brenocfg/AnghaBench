#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  input_thread_t ;
typedef  int /*<<< orphan*/  input_control_param_t ;
struct TYPE_2__ {int /*<<< orphan*/  is_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  Control (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* input_priv (int /*<<< orphan*/ *) ; 

void input_ControlSync(input_thread_t *p_input, int i_type,
                       const input_control_param_t* param )
{
    assert( !input_priv(p_input)->is_running );
    Control( p_input, i_type, *param );
}