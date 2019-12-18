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
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int manager_load_config (int /*<<< orphan*/ *) ; 
 int manager_should_reload (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_load_config(Manager *manager) {
        int r;
/*  TODO: should_reload, is false if the config dirs do not exist, so
 *        so we can't do this test here, move it to a test for paths_check_timestamps
 *        directly
 *
 *        assert_se(network_should_reload(manager) == true);
*/

        r = manager_load_config(manager);
        if (r == -EPERM)
                return r;
        assert_se(r >= 0);

        assert_se(manager_should_reload(manager) == false);

        return 0;
}