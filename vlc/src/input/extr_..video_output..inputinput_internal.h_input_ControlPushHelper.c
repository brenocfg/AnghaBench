#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_value_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_3__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ input_control_param_t ;

/* Variables and functions */
 int input_ControlPush (int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static inline int input_ControlPushHelper( input_thread_t *p_input, int i_type, vlc_value_t *val )
{
    if( val != NULL )
    {
        input_control_param_t param = { .val = *val };
        return input_ControlPush( p_input, i_type, &param );
    }
    else
    {
        return input_ControlPush( p_input, i_type, NULL );
    }
}