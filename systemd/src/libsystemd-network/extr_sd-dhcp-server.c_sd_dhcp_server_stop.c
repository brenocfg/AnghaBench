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
struct TYPE_5__ {void* fd; void* fd_raw; int /*<<< orphan*/  receive_message; } ;
typedef  TYPE_1__ sd_dhcp_server ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_dhcp_server (TYPE_1__*,char*) ; 
 void* safe_close (void*) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

int sd_dhcp_server_stop(sd_dhcp_server *server) {
        assert_return(server, -EINVAL);

        server->receive_message =
                sd_event_source_unref(server->receive_message);

        server->fd_raw = safe_close(server->fd_raw);
        server->fd = safe_close(server->fd);

        log_dhcp_server(server, "STOPPED");

        return 0;
}