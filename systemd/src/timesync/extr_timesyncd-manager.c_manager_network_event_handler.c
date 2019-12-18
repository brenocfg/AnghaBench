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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_8__ {scalar_t__ current_server_address; int /*<<< orphan*/  network_monitor; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int manager_begin (TYPE_1__*) ; 
 int manager_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_disconnect (TYPE_1__*) ; 
 int manager_is_connected (TYPE_1__*) ; 
 int manager_network_read_link_servers (TYPE_1__*) ; 
 int network_is_online () ; 
 int /*<<< orphan*/  sd_network_monitor_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int manager_network_event_handler(sd_event_source *s, int fd, uint32_t revents, void *userdata) {
        Manager *m = userdata;
        bool changed, connected, online;
        int r;

        assert(m);

        sd_network_monitor_flush(m->network_monitor);

        /* When manager_network_read_link_servers() failed, we assume that the servers are changed. */
        changed = manager_network_read_link_servers(m);

        /* check if the machine is online */
        online = network_is_online();

        /* check if the client is currently connected */
        connected = manager_is_connected(m);

        if (connected && !online) {
                log_info("No network connectivity, watching for changes.");
                manager_disconnect(m);

        } else if ((!connected || changed) && online) {
                log_info("Network configuration changed, trying to establish connection.");

                if (m->current_server_address)
                        r = manager_begin(m);
                else
                        r = manager_connect(m);
                if (r < 0)
                        return r;
        }

        return 0;
}