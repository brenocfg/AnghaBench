#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  option; int /*<<< orphan*/  options; } ;
typedef  TYPE_1__ sd_dhcp_option ;
typedef  TYPE_1__ sd_dhcp_client ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  UINT_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dhcp_option_hash_ops ; 
 int ordered_hashmap_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ordered_hashmap_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sd_dhcp_option_ref (TYPE_1__*) ; 

int sd_dhcp_client_set_dhcp_option(sd_dhcp_client *client, sd_dhcp_option *v) {
        int r;

        assert_return(client, -EINVAL);
        assert_return(v, -EINVAL);

        r = ordered_hashmap_ensure_allocated(&client->options, &dhcp_option_hash_ops);
        if (r < 0)
                return r;

        r = ordered_hashmap_put(client->options, UINT_TO_PTR(v->option), v);
        if (r < 0)
                return r;

        sd_dhcp_option_ref(v);
        return 0;
}