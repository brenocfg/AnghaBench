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
 scalar_t__ is_ie_hardened () ; 
 int /*<<< orphan*/  pCreateUri ; 
 int /*<<< orphan*/  register_zone_domains () ; 
 int /*<<< orphan*/  run_child_process () ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_zone_domain_cache () ; 
 int /*<<< orphan*/  trace (char*) ; 
 int /*<<< orphan*/  unregister_zone_domains () ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_zone_domains(void)
{
    if(is_ie_hardened()) {
        skip("IE running in Enhanced Security Configuration\n");
        return;
    } else if(!pCreateUri) {
        win_skip("Skipping zone domain tests, IE too old\n");
        return;
    }

    trace("testing zone domains...\n");

    test_zone_domain_cache();

    if (!register_zone_domains()) return;
    run_child_process();
    unregister_zone_domains();
}