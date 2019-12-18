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
struct bus_container {scalar_t__ enclosing; size_t end; size_t begin; int /*<<< orphan*/ * array_size; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;

/* Variables and functions */
 size_t BUS_MESSAGE_BSWAP32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BUS_MESSAGE_IS_GVARIANT (int /*<<< orphan*/ *) ; 
 scalar_t__ SD_BUS_TYPE_ARRAY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 struct bus_container* message_get_last_container (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool message_end_of_array(sd_bus_message *m, size_t index) {
        struct bus_container *c;

        assert(m);

        c = message_get_last_container(m);
        if (c->enclosing != SD_BUS_TYPE_ARRAY)
                return false;

        if (BUS_MESSAGE_IS_GVARIANT(m))
                return index >= c->end;
        else {
                assert(c->array_size);
                return index >= c->begin + BUS_MESSAGE_BSWAP32(m, *c->array_size);
        }
}