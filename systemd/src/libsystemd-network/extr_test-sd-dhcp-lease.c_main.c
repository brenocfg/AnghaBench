#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  test_dhcp_lease_parse_search_domains_basic () ; 
 int /*<<< orphan*/  test_dhcp_lease_parse_search_domains_labels_and_ptr () ; 
 int /*<<< orphan*/  test_dhcp_lease_parse_search_domains_loops () ; 
 int /*<<< orphan*/  test_dhcp_lease_parse_search_domains_no_data () ; 
 int /*<<< orphan*/  test_dhcp_lease_parse_search_domains_ptr () ; 
 int /*<<< orphan*/  test_dhcp_lease_parse_search_domains_wrong_len () ; 

int main(int argc, char *argv[]) {
        test_dhcp_lease_parse_search_domains_basic();
        test_dhcp_lease_parse_search_domains_ptr();
        test_dhcp_lease_parse_search_domains_labels_and_ptr();
        test_dhcp_lease_parse_search_domains_no_data();
        test_dhcp_lease_parse_search_domains_loops();
        test_dhcp_lease_parse_search_domains_wrong_len();
}