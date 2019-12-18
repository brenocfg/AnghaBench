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
typedef  int /*<<< orphan*/  sd_event ;
struct TYPE_4__ {int /*<<< orphan*/ * event; } ;
typedef  TYPE_1__ sd_dhcp_server ;

/* Variables and functions */
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ *) ; 

sd_event *sd_dhcp_server_get_event(sd_dhcp_server *server) {
        assert_return(server, NULL);

        return server->event;
}