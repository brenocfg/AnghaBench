#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  duids_requesting_uuid; int /*<<< orphan*/  links_requesting_uuid; scalar_t__ has_product_uuid; } ;
typedef  TYPE_1__ Manager ;
typedef  int /*<<< orphan*/  Link ;
typedef  int /*<<< orphan*/  DUID ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_product_uuid_handler ; 
 int /*<<< orphan*/ * link_get_duid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int log_oom () ; 
 int log_warning_errno (int,char*) ; 
 int sd_bus_call_method_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,TYPE_1__*,char*,int) ; 
 scalar_t__ sd_bus_is_ready (int /*<<< orphan*/ ) ; 
 int set_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int set_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int manager_request_product_uuid(Manager *m, Link *link) {
        int r;

        assert(m);

        if (m->has_product_uuid)
                return 0;

        log_debug("Requesting product UUID");

        if (link) {
                DUID *duid;

                assert_se(duid = link_get_duid(link));

                r = set_ensure_allocated(&m->links_requesting_uuid, NULL);
                if (r < 0)
                        return log_oom();

                r = set_ensure_allocated(&m->duids_requesting_uuid, NULL);
                if (r < 0)
                        return log_oom();

                r = set_put(m->links_requesting_uuid, link);
                if (r < 0)
                        return log_oom();

                r = set_put(m->duids_requesting_uuid, duid);
                if (r < 0)
                        return log_oom();

                link_ref(link);
        }

        if (!m->bus || sd_bus_is_ready(m->bus) <= 0) {
                log_debug("Not connected to system bus, requesting product UUID later.");
                return 0;
        }

        r = sd_bus_call_method_async(
                        m->bus,
                        NULL,
                        "org.freedesktop.hostname1",
                        "/org/freedesktop/hostname1",
                        "org.freedesktop.hostname1",
                        "GetProductUUID",
                        get_product_uuid_handler,
                        m,
                        "b",
                        false);
        if (r < 0)
                return log_warning_errno(r, "Failed to get product UUID: %m");

        return 0;
}