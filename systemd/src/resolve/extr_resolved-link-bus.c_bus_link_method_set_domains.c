#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  search_domains; TYPE_10__* manager; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_22__ {int route_only; } ;
struct TYPE_20__ {int /*<<< orphan*/  polkit_registry; } ;
typedef  TYPE_1__ Link ;
typedef  TYPE_3__ DnsSearchDomain ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  DNS_SEARCH_DOMAIN_LINK ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_verify_polkit_async (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dns_name_is_root (char const*) ; 
 int dns_name_is_valid (char const*) ; 
 int dns_search_domain_find (int /*<<< orphan*/ ,char const*,TYPE_3__**) ; 
 int /*<<< orphan*/  dns_search_domain_mark_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_search_domain_move_back_and_unmark (TYPE_3__*) ; 
 int dns_search_domain_new (TYPE_10__*,TYPE_3__**,int /*<<< orphan*/ ,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  dns_search_domain_unlink_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_search_domain_unlink_marked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_save_user (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_write_resolv_conf (TYPE_10__*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int sd_bus_message_enter_container (TYPE_1__*,char,char*) ; 
 int sd_bus_message_exit_container (TYPE_1__*) ; 
 int sd_bus_message_read (TYPE_1__*,char*,char const**,int*) ; 
 int sd_bus_message_rewind (TYPE_1__*,int) ; 
 int sd_bus_reply_method_return (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int verify_unmanaged_link (TYPE_1__*,int /*<<< orphan*/ *) ; 

int bus_link_method_set_domains(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Link *l = userdata;
        int r;

        assert(message);
        assert(l);

        r = verify_unmanaged_link(l, error);
        if (r < 0)
                return r;

        r = sd_bus_message_enter_container(message, 'a', "(sb)");
        if (r < 0)
                return r;

        for (;;) {
                const char *name;
                int route_only;

                r = sd_bus_message_read(message, "(sb)", &name, &route_only);
                if (r < 0)
                        return r;
                if (r == 0)
                        break;

                r = dns_name_is_valid(name);
                if (r < 0)
                        return r;
                if (r == 0)
                        return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Invalid search domain %s", name);
                if (!route_only && dns_name_is_root(name))
                        return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Root domain is not suitable as search domain");
        }

        r = sd_bus_message_rewind(message, false);
        if (r < 0)
                return r;

        r = bus_verify_polkit_async(message, CAP_NET_ADMIN,
                                    "org.freedesktop.resolve1.set-domains",
                                    NULL, true, UID_INVALID,
                                    &l->manager->polkit_registry, error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* Polkit will call us back */

        dns_search_domain_mark_all(l->search_domains);

        for (;;) {
                DnsSearchDomain *d;
                const char *name;
                int route_only;

                r = sd_bus_message_read(message, "(sb)", &name, &route_only);
                if (r < 0)
                        goto clear;
                if (r == 0)
                        break;

                r = dns_search_domain_find(l->search_domains, name, &d);
                if (r < 0)
                        goto clear;

                if (r > 0)
                        dns_search_domain_move_back_and_unmark(d);
                else {
                        r = dns_search_domain_new(l->manager, &d, DNS_SEARCH_DOMAIN_LINK, l, name);
                        if (r < 0)
                                goto clear;
                }

                d->route_only = route_only;
        }

        r = sd_bus_message_exit_container(message);
        if (r < 0)
                goto clear;

        dns_search_domain_unlink_marked(l->search_domains);

        (void) link_save_user(l);
        (void) manager_write_resolv_conf(l->manager);

        return sd_bus_reply_method_return(message, NULL);

clear:
        dns_search_domain_unlink_all(l->search_domains);
        return r;
}