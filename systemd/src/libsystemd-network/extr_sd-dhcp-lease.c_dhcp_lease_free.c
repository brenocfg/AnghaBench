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
struct sd_dhcp_raw_option {struct sd_dhcp_raw_option* data; } ;
struct TYPE_7__ {int /*<<< orphan*/  search_domains; struct sd_dhcp_raw_option* vendor_specific; struct sd_dhcp_raw_option* client_id; struct sd_dhcp_raw_option* static_route; struct sd_dhcp_raw_option* sip; struct sd_dhcp_raw_option* ntp; struct sd_dhcp_raw_option* dns; struct sd_dhcp_raw_option* domainname; struct sd_dhcp_raw_option* hostname; struct sd_dhcp_raw_option* timezone; struct sd_dhcp_raw_option* router; struct sd_dhcp_raw_option* root_path; struct sd_dhcp_raw_option* private_options; } ;
typedef  TYPE_1__ sd_dhcp_lease ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,struct sd_dhcp_raw_option*,struct sd_dhcp_raw_option*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (struct sd_dhcp_raw_option*) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sd_dhcp_lease *dhcp_lease_free(sd_dhcp_lease *lease) {
        assert(lease);

        while (lease->private_options) {
                struct sd_dhcp_raw_option *option = lease->private_options;

                LIST_REMOVE(options, lease->private_options, option);

                free(option->data);
                free(option);
        }

        free(lease->root_path);
        free(lease->router);
        free(lease->timezone);
        free(lease->hostname);
        free(lease->domainname);
        free(lease->dns);
        free(lease->ntp);
        free(lease->sip);
        free(lease->static_route);
        free(lease->client_id);
        free(lease->vendor_specific);
        strv_free(lease->search_domains);
        return mfree(lease);
}