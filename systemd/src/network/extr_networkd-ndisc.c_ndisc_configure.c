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
struct TYPE_5__ {int /*<<< orphan*/  ndisc; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  mac; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ndisc_handler ; 
 int sd_ndisc_attach_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_ndisc_new (int /*<<< orphan*/ *) ; 
 int sd_ndisc_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_ndisc_set_ifindex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_ndisc_set_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ndisc_configure(Link *link) {
        int r;

        assert(link);

        r = sd_ndisc_new(&link->ndisc);
        if (r < 0)
                return r;

        r = sd_ndisc_attach_event(link->ndisc, NULL, 0);
        if (r < 0)
                return r;

        r = sd_ndisc_set_mac(link->ndisc, &link->mac);
        if (r < 0)
                return r;

        r = sd_ndisc_set_ifindex(link->ndisc, link->ifindex);
        if (r < 0)
                return r;

        r = sd_ndisc_set_callback(link->ndisc, ndisc_handler, link);
        if (r < 0)
                return r;

        return 0;
}