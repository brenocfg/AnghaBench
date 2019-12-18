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
struct TYPE_8__ {int n_netif; int /*<<< orphan*/  netif; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ sd_bus ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  TYPE_1__ Machine ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_cc (int) ; 
 int sd_bus_message_append_array (TYPE_1__*,char,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int property_get_netif(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        Machine *m = userdata;

        assert(bus);
        assert(reply);
        assert(m);

        assert_cc(sizeof(int) == sizeof(int32_t));

        return sd_bus_message_append_array(reply, 'i', m->netif, m->n_netif * sizeof(int));
}