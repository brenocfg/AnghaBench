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
typedef  int /*<<< orphan*/  sd_netlink_message ;
typedef  int /*<<< orphan*/  sd_netlink ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_info_errno (int,char*,int) ; 
 int sd_netlink_message_get_errno (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pipe_handler(sd_netlink *rtnl, sd_netlink_message *m, void *userdata) {
        int *counter = userdata;
        int r;

        (*counter)--;

        r = sd_netlink_message_get_errno(m);

        log_info_errno(r, "%d left in pipe. got reply: %m", *counter);

        assert_se(r >= 0);

        return 1;
}