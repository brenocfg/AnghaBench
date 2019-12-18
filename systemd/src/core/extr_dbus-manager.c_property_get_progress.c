#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ n_installed_jobs; int /*<<< orphan*/  jobs; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ sd_bus ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 scalar_t__ MANAGER_IS_FINISHED (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ hashmap_size (int /*<<< orphan*/ ) ; 
 int sd_bus_message_append (TYPE_1__*,char*,double) ; 

__attribute__((used)) static int property_get_progress(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        Manager *m = userdata;
        double d;

        assert(bus);
        assert(reply);
        assert(m);

        if (MANAGER_IS_FINISHED(m))
                d = 1.0;
        else
                d = 1.0 - ((double) hashmap_size(m->jobs) / (double) m->n_installed_jobs);

        return sd_bus_message_append(reply, "d", d);
}