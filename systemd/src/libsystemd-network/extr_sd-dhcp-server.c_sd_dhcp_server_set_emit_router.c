#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int emit_router; } ;
typedef  TYPE_1__ sd_dhcp_server ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 

int sd_dhcp_server_set_emit_router(sd_dhcp_server *server, int enabled) {
        assert_return(server, -EINVAL);

        if (enabled == server->emit_router)
                return 0;

        server->emit_router = enabled;

        return 1;
}