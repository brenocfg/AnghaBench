#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_5__* manager; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_15__ {int /*<<< orphan*/  polkit_registry; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_verify_polkit_async (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_add_rrs (TYPE_1__*,int) ; 
 int /*<<< orphan*/  link_allocate_scopes (TYPE_1__*) ; 
 int /*<<< orphan*/  link_flush_settings (TYPE_1__*) ; 
 int /*<<< orphan*/  link_save_user (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_send_changed (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  manager_write_resolv_conf (TYPE_5__*) ; 
 int sd_bus_reply_method_return (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int verify_unmanaged_link (TYPE_1__*,int /*<<< orphan*/ *) ; 

int bus_link_method_revert(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Link *l = userdata;
        int r;

        assert(message);
        assert(l);

        r = verify_unmanaged_link(l, error);
        if (r < 0)
                return r;

        r = bus_verify_polkit_async(message, CAP_NET_ADMIN,
                                    "org.freedesktop.resolve1.revert",
                                    NULL, true, UID_INVALID,
                                    &l->manager->polkit_registry, error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* Polkit will call us back */

        link_flush_settings(l);
        link_allocate_scopes(l);
        link_add_rrs(l, false);

        (void) link_save_user(l);
        (void) manager_write_resolv_conf(l->manager);
        (void) manager_send_changed(l->manager, "DNS");

        return sd_bus_reply_method_return(message, NULL);
}