#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  duids_requesting_uuid; int /*<<< orphan*/  links_requesting_uuid; int /*<<< orphan*/  product_uuid; scalar_t__ has_product_uuid; struct TYPE_15__* manager; struct TYPE_15__* network; } ;
typedef  TYPE_1__ Manager ;
typedef  TYPE_1__ Link ;
typedef  TYPE_1__ DUID ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  duid_set_uuid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* link_get_duid (TYPE_1__*) ; 
 int /*<<< orphan*/  link_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  link_requires_uuid (TYPE_1__*) ; 
 int /*<<< orphan*/  log_link_warning_errno (TYPE_1__*,int,char*) ; 
 int log_oom () ; 
 int manager_request_product_uuid (TYPE_1__*,TYPE_1__*) ; 
 int set_put (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int link_configure_duid(Link *link) {
        Manager *m;
        DUID *duid;
        int r;

        assert(link);
        assert(link->manager);
        assert(link->network);

        m = link->manager;
        duid = link_get_duid(link);

        if (!link_requires_uuid(link))
                return 1;

        if (m->has_product_uuid) {
                (void) duid_set_uuid(duid, m->product_uuid);
                return 1;
        }

        if (!m->links_requesting_uuid) {
                r = manager_request_product_uuid(m, link);
                if (r < 0) {
                        if (r == -ENOMEM)
                                return r;

                        log_link_warning_errno(link, r,
                                               "Failed to get product UUID. Falling back to use machine-app-specific ID as DUID-UUID: %m");
                        return 1;
                }
        } else {
                r = set_put(m->links_requesting_uuid, link);
                if (r < 0)
                        return log_oom();

                r = set_put(m->duids_requesting_uuid, duid);
                if (r < 0)
                        return log_oom();

                link_ref(link);
        }

        return 0;
}