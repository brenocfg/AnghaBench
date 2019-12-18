#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* ntp_fqdn; int /*<<< orphan*/  ntp; void* domains; int /*<<< orphan*/  dns; int /*<<< orphan*/  pd; int /*<<< orphan*/  ia; int /*<<< orphan*/  serverid; } ;
typedef  TYPE_1__ sd_dhcp6_lease ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dhcp6_lease_free_ia (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 void* strv_free (void*) ; 

__attribute__((used)) static sd_dhcp6_lease *dhcp6_lease_free(sd_dhcp6_lease *lease) {
        assert(lease);

        free(lease->serverid);
        dhcp6_lease_free_ia(&lease->ia);
        dhcp6_lease_free_ia(&lease->pd);

        free(lease->dns);

        lease->domains = strv_free(lease->domains);

        free(lease->ntp);

        lease->ntp_fqdn = strv_free(lease->ntp_fqdn);
        return mfree(lease);
}