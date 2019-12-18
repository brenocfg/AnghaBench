#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * current_server_address; TYPE_1__* current_server_name; } ;
struct TYPE_7__ {int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ ServerName ;
typedef  TYPE_2__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_disconnect (TYPE_2__*) ; 

void manager_set_server_name(Manager *m, ServerName *n) {
        assert(m);

        if (m->current_server_name == n)
                return;

        m->current_server_name = n;
        m->current_server_address = NULL;

        manager_disconnect(m);

        if (n)
                log_debug("Selected server %s.", n->string);
}