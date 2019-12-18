#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  numa_policy; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ sd_bus ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  numa_policy_get_type (int /*<<< orphan*/ *) ; 
 int sd_bus_message_append_basic (TYPE_1__*,char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int property_get_numa_policy(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {
        ExecContext *c = userdata;
        int32_t policy;

        assert(bus);
        assert(reply);
        assert(c);

        policy = numa_policy_get_type(&c->numa_policy);

        return sd_bus_message_append_basic(reply, 'i', &policy);
}