#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* manager; } ;
struct TYPE_9__ {scalar_t__ std_error; scalar_t__ std_output; scalar_t__ std_input; scalar_t__ stdin_data_size; } ;
struct TYPE_10__ {TYPE_2__ exec_context; } ;
struct TYPE_8__ {scalar_t__ default_std_error; scalar_t__ default_std_output; } ;
typedef  TYPE_3__ Service ;

/* Variables and functions */
 scalar_t__ EXEC_INPUT_DATA ; 
 scalar_t__ EXEC_INPUT_NULL ; 
 scalar_t__ EXEC_OUTPUT_INHERIT ; 
 TYPE_6__* UNIT (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 

__attribute__((used)) static void service_fix_output(Service *s) {
        assert(s);

        /* If nothing has been explicitly configured, patch default output in. If input is socket/tty we avoid this
         * however, since in that case we want output to default to the same place as we read input from. */

        if (s->exec_context.std_error == EXEC_OUTPUT_INHERIT &&
            s->exec_context.std_output == EXEC_OUTPUT_INHERIT &&
            s->exec_context.std_input == EXEC_INPUT_NULL)
                s->exec_context.std_error = UNIT(s)->manager->default_std_error;

        if (s->exec_context.std_output == EXEC_OUTPUT_INHERIT &&
            s->exec_context.std_input == EXEC_INPUT_NULL)
                s->exec_context.std_output = UNIT(s)->manager->default_std_output;

        if (s->exec_context.std_input == EXEC_INPUT_NULL &&
            s->exec_context.stdin_data_size > 0)
                s->exec_context.std_input = EXEC_INPUT_DATA;
}