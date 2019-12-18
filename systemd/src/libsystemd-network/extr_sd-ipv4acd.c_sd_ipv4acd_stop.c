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
typedef  int /*<<< orphan*/  sd_ipv4acd ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SD_IPV4ACD_EVENT_STOP ; 
 int /*<<< orphan*/  assert_return (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4acd_client_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4acd_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_ipv4acd (int /*<<< orphan*/ *,char*) ; 

int sd_ipv4acd_stop(sd_ipv4acd *acd) {
        assert_return(acd, -EINVAL);

        ipv4acd_reset(acd);

        log_ipv4acd(acd, "STOPPED");

        ipv4acd_client_notify(acd, SD_IPV4ACD_EVENT_STOP);

        return 0;
}