#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_7__ {struct TYPE_7__* command_prev; } ;
struct TYPE_6__ {TYPE_2__** exec_command; } ;
typedef  size_t ServiceExecCommand ;
typedef  TYPE_1__ Service ;
typedef  TYPE_2__ ExecCommand ;

/* Variables and functions */
 TYPE_1__* SERVICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static unsigned service_exec_command_index(Unit *u, ServiceExecCommand id, ExecCommand *current) {
        Service *s = SERVICE(u);
        unsigned idx = 0;
        ExecCommand *first, *c;

        assert(s);

        first = s->exec_command[id];

        /* Figure out where we are in the list by walking back to the beginning */
        for (c = current; c != first; c = c->command_prev)
                idx++;

        return idx;
}