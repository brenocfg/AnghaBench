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
typedef  int /*<<< orphan*/  sd_bus_message ;
struct TYPE_4__ {int /*<<< orphan*/  family; int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ DnsServer ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  FAMILY_ADDRESS_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_server_ifindex (TYPE_1__*) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int sd_bus_message_append_array (int /*<<< orphan*/ *,char,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_bus_message_close_container (int /*<<< orphan*/ *) ; 
 int sd_bus_message_open_container (int /*<<< orphan*/ *,char,char*) ; 

int bus_dns_server_append(sd_bus_message *reply, DnsServer *s, bool with_ifindex) {
        int r;

        assert(reply);

        if (!s) {
                if (with_ifindex)
                        return sd_bus_message_append(reply, "(iiay)", 0, AF_UNSPEC, 0);
                else
                        return sd_bus_message_append(reply, "(iay)", AF_UNSPEC, 0);
        }

        r = sd_bus_message_open_container(reply, 'r', with_ifindex ? "iiay" : "iay");
        if (r < 0)
                return r;

        if (with_ifindex) {
                r = sd_bus_message_append(reply, "i", dns_server_ifindex(s));
                if (r < 0)
                        return r;
        }

        r = sd_bus_message_append(reply, "i", s->family);
        if (r < 0)
                return r;

        r = sd_bus_message_append_array(reply, 'y', &s->address, FAMILY_ADDRESS_SIZE(s->family));
        if (r < 0)
                return r;

        return sd_bus_message_close_container(reply);
}