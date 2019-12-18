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
struct in_addr {int dummy; } ;
struct ether_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sd_ipv4acd ;
typedef  int /*<<< orphan*/  sd_event ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  acd_handler ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 scalar_t__ sd_event_loop (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_ipv4acd_attach_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_ipv4acd_new (int /*<<< orphan*/ **) ; 
 scalar_t__ sd_ipv4acd_set_address (int /*<<< orphan*/ *,struct in_addr const*) ; 
 scalar_t__ sd_ipv4acd_set_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sd_ipv4acd_set_ifindex (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sd_ipv4acd_set_mac (int /*<<< orphan*/ *,struct ether_addr const*) ; 
 scalar_t__ sd_ipv4acd_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_ipv4acd_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int client_run(int ifindex, const struct in_addr *pa, const struct ether_addr *ha, sd_event *e) {
        sd_ipv4acd *acd;

        assert_se(sd_ipv4acd_new(&acd) >= 0);
        assert_se(sd_ipv4acd_attach_event(acd, e, 0) >= 0);

        assert_se(sd_ipv4acd_set_ifindex(acd, ifindex) >= 0);
        assert_se(sd_ipv4acd_set_mac(acd, ha) >= 0);
        assert_se(sd_ipv4acd_set_address(acd, pa) >= 0);
        assert_se(sd_ipv4acd_set_callback(acd, acd_handler, NULL) >= 0);

        log_info("starting IPv4ACD client");

        assert_se(sd_ipv4acd_start(acd) >= 0);

        assert_se(sd_event_loop(e) >= 0);

        assert_se(!sd_ipv4acd_unref(acd));

        return EXIT_SUCCESS;
}