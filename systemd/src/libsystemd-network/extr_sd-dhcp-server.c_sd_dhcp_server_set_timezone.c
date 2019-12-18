#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  timezone; } ;
typedef  TYPE_1__ sd_dhcp_server ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int free_and_strdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ streq_ptr (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* timezone_is_valid (char const*,int /*<<< orphan*/ ) ; 

int sd_dhcp_server_set_timezone(sd_dhcp_server *server, const char *tz) {
        int r;

        assert_return(server, -EINVAL);
        assert_return(timezone_is_valid(tz, LOG_DEBUG), -EINVAL);

        if (streq_ptr(tz, server->timezone))
                return 0;

        r = free_and_strdup(&server->timezone, tz);
        if (r < 0)
                return r;

        return 1;
}