#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bus_container {int /*<<< orphan*/  offsets; int /*<<< orphan*/  peeked_signature; int /*<<< orphan*/  signature; } ;
struct TYPE_4__ {scalar_t__ n_containers; } ;
typedef  TYPE_1__ sd_bus_message ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 struct bus_container* message_get_last_container (TYPE_1__*) ; 

__attribute__((used)) static void message_free_last_container(sd_bus_message *m) {
        struct bus_container *c;

        c = message_get_last_container(m);

        free(c->signature);
        free(c->peeked_signature);
        free(c->offsets);

        /* Move to previous container, but not if we are on root container */
        if (m->n_containers > 0)
                m->n_containers--;
}