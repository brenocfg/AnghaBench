#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bus_container {scalar_t__* signature; size_t index; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 struct bus_container* message_get_last_container (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool message_end_of_signature(sd_bus_message *m) {
        struct bus_container *c;

        assert(m);

        c = message_get_last_container(m);
        return !c->signature || c->signature[c->index] == 0;
}