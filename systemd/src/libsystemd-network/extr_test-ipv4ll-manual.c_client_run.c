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
struct ether_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sd_ipv4ll ;
typedef  int /*<<< orphan*/  sd_event ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  ll_handler ; 
 int /*<<< orphan*/  log_info (char*) ; 
 scalar_t__ safe_atou (char const*,unsigned int*) ; 
 scalar_t__ sd_event_loop (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_ipv4ll_attach_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_ipv4ll_new (int /*<<< orphan*/ **) ; 
 scalar_t__ sd_ipv4ll_set_address_seed (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ sd_ipv4ll_set_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sd_ipv4ll_set_ifindex (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sd_ipv4ll_set_mac (int /*<<< orphan*/ *,struct ether_addr const*) ; 
 scalar_t__ sd_ipv4ll_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_ipv4ll_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int client_run(int ifindex, const char *seed_str, const struct ether_addr *ha, sd_event *e) {
        sd_ipv4ll *ll;

        assert_se(sd_ipv4ll_new(&ll) >= 0);
        assert_se(sd_ipv4ll_attach_event(ll, e, 0) >= 0);

        assert_se(sd_ipv4ll_set_ifindex(ll, ifindex) >= 0);
        assert_se(sd_ipv4ll_set_mac(ll, ha) >= 0);
        assert_se(sd_ipv4ll_set_callback(ll, ll_handler, NULL) >= 0);

        if (seed_str) {
                unsigned seed;

                assert_se(safe_atou(seed_str, &seed) >= 0);

                assert_se(sd_ipv4ll_set_address_seed(ll, seed) >= 0);
        }

        log_info("starting IPv4LL client");

        assert_se(sd_ipv4ll_start(ll) >= 0);

        assert_se(sd_event_loop(e) >= 0);

        assert_se(!sd_ipv4ll_unref(ll));

        return EXIT_SUCCESS;
}