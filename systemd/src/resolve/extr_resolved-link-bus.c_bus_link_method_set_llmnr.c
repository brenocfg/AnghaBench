#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ llmnr_support; TYPE_1__* manager; } ;
typedef  TYPE_2__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_13__ {int /*<<< orphan*/  polkit_registry; } ;
typedef  scalar_t__ ResolveSupport ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 scalar_t__ RESOLVE_SUPPORT_YES ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int bus_verify_polkit_async (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  link_add_rrs (TYPE_2__*,int) ; 
 int /*<<< orphan*/  link_allocate_scopes (TYPE_2__*) ; 
 int /*<<< orphan*/  link_save_user (TYPE_2__*) ; 
 scalar_t__ resolve_support_from_string (char const*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int sd_bus_message_read (TYPE_2__*,char*,char const**) ; 
 int sd_bus_reply_method_return (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int verify_unmanaged_link (TYPE_2__*,int /*<<< orphan*/ *) ; 

int bus_link_method_set_llmnr(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Link *l = userdata;
        ResolveSupport mode;
        const char *llmnr;
        int r;

        assert(message);
        assert(l);

        r = verify_unmanaged_link(l, error);
        if (r < 0)
                return r;

        r = sd_bus_message_read(message, "s", &llmnr);
        if (r < 0)
                return r;

        if (isempty(llmnr))
                mode = RESOLVE_SUPPORT_YES;
        else {
                mode = resolve_support_from_string(llmnr);
                if (mode < 0)
                        return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Invalid LLMNR setting: %s", llmnr);
        }

        r = bus_verify_polkit_async(message, CAP_NET_ADMIN,
                                    "org.freedesktop.resolve1.set-llmnr",
                                    NULL, true, UID_INVALID,
                                    &l->manager->polkit_registry, error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* Polkit will call us back */

        l->llmnr_support = mode;
        link_allocate_scopes(l);
        link_add_rrs(l, false);

        (void) link_save_user(l);

        return sd_bus_reply_method_return(message, NULL);
}