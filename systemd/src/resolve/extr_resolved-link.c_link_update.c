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
struct TYPE_8__ {scalar_t__ llmnr_support; scalar_t__ mdns_support; int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 scalar_t__ RESOLVE_SUPPORT_NO ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  link_add_rrs (TYPE_1__*,int) ; 
 int /*<<< orphan*/  link_allocate_scopes (TYPE_1__*) ; 
 int /*<<< orphan*/  link_load_user (TYPE_1__*) ; 
 int /*<<< orphan*/  link_read_settings (TYPE_1__*) ; 
 int manager_llmnr_start (int /*<<< orphan*/ ) ; 
 int manager_mdns_start (int /*<<< orphan*/ ) ; 

int link_update(Link *l) {
        int r;

        assert(l);

        link_read_settings(l);
        link_load_user(l);

        if (l->llmnr_support != RESOLVE_SUPPORT_NO) {
                r = manager_llmnr_start(l->manager);
                if (r < 0)
                        return r;
        }

        if (l->mdns_support != RESOLVE_SUPPORT_NO) {
                r = manager_mdns_start(l->manager);
                if (r < 0)
                        return r;
        }

        link_allocate_scopes(l);
        link_add_rrs(l, false);

        return 0;
}