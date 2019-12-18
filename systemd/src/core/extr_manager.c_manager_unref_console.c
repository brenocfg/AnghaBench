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
struct TYPE_3__ {scalar_t__ n_on_console; int no_console_output; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void manager_unref_console(Manager *m) {

        assert(m->n_on_console > 0);
        m->n_on_console--;

        if (m->n_on_console == 0)
                m->no_console_output = false; /* unset no_console_output flag, since the console is definitely free now */
}