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
struct TYPE_8__ {scalar_t__ n_dns; int /*<<< orphan*/  route_domains; int /*<<< orphan*/  search_domains; int /*<<< orphan*/  ntp; int /*<<< orphan*/  network; } ;
typedef  TYPE_1__ Network ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  link_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  network_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  ordered_set_isempty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_isempty (int /*<<< orphan*/ ) ; 

int network_apply(Network *network, Link *link) {
        assert(network);
        assert(link);

        link->network = network_ref(network);

        if (network->n_dns > 0 ||
            !strv_isempty(network->ntp) ||
            !ordered_set_isempty(network->search_domains) ||
            !ordered_set_isempty(network->route_domains))
                link_dirty(link);

        return 0;
}