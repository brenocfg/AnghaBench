#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_id128_t ;
struct TYPE_11__ {int has_product_uuid; void* links_requesting_uuid; void* duids_requesting_uuid; int /*<<< orphan*/  product_uuid; } ;
typedef  TYPE_1__ sd_bus_message ;
struct TYPE_12__ {int /*<<< orphan*/  message; } ;
typedef  TYPE_2__ sd_bus_error ;
typedef  TYPE_1__ Manager ;
typedef  int /*<<< orphan*/  Link ;
typedef  int /*<<< orphan*/  DUID ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  duid_set_uuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int link_configure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_enter_failed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/  log_error_errno (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  sd_bus_error_get_errno (TYPE_2__ const*) ; 
 TYPE_2__* sd_bus_message_get_error (TYPE_1__*) ; 
 int sd_bus_message_read_array (TYPE_1__*,char,void const**,size_t*) ; 
 void* set_free (void*) ; 
 void* set_steal_first (void*) ; 

int get_product_uuid_handler(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
        Manager *manager = userdata;
        const sd_bus_error *e;
        const void *a;
        size_t sz;
        DUID *duid;
        Link *link;
        int r;

        assert(m);
        assert(manager);

        e = sd_bus_message_get_error(m);
        if (e) {
                log_error_errno(sd_bus_error_get_errno(e),
                                "Could not get product UUID. Falling back to use machine-app-specific ID as DUID-UUID: %s",
                                e->message);
                goto configure;
        }

        r = sd_bus_message_read_array(m, 'y', &a, &sz);
        if (r < 0)
                goto configure;

        if (sz != sizeof(sd_id128_t)) {
                log_error("Invalid product UUID. Falling back to use machine-app-specific ID as DUID-UUID.");
                goto configure;
        }

        memcpy(&manager->product_uuid, a, sz);
        while ((duid = set_steal_first(manager->duids_requesting_uuid)))
                (void) duid_set_uuid(duid, manager->product_uuid);

        manager->duids_requesting_uuid = set_free(manager->duids_requesting_uuid);

configure:
        while ((link = set_steal_first(manager->links_requesting_uuid))) {
                link_unref(link);

                r = link_configure(link);
                if (r < 0)
                        link_enter_failed(link);
        }

        manager->links_requesting_uuid = set_free(manager->links_requesting_uuid);

        /* To avoid calling GetProductUUID() bus method so frequently, set the flag below
         * even if the method fails. */
        manager->has_product_uuid = true;

        return 1;
}