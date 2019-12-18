#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  raw_option; } ;
typedef  TYPE_1__ sd_dhcp_server ;
typedef  TYPE_1__ sd_dhcp_raw_option ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dhcp_raw_options_hash_ops ; 
 int ordered_hashmap_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ordered_hashmap_put (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  sd_dhcp_raw_option_ref (TYPE_1__*) ; 

int sd_dhcp_server_add_raw_option(sd_dhcp_server *server, sd_dhcp_raw_option *v) {
        int r;

        assert_return(server, -EINVAL);
        assert_return(v, -EINVAL);

        r = ordered_hashmap_ensure_allocated(&server->raw_option, &dhcp_raw_options_hash_ops);
        if (r < 0)
                return -ENOMEM;

        r = ordered_hashmap_put(server->raw_option, v, v);
        if (r < 0)
                return r;

        sd_dhcp_raw_option_ref(v);

        return 1;
}