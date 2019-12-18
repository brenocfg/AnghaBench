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
typedef  int /*<<< orphan*/  sd_ipv4ll ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (int,int /*<<< orphan*/ ) ; 
 int ipv4ll_start_internal (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sd_ipv4ll_is_running (int /*<<< orphan*/ *) ; 

int sd_ipv4ll_start(sd_ipv4ll *ll) {
        assert_return(ll, -EINVAL);
        assert_return(sd_ipv4ll_is_running(ll) == 0, -EBUSY);

        return ipv4ll_start_internal(ll, true);
}