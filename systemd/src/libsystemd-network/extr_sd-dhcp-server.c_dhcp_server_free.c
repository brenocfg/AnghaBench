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
struct TYPE_9__ {int /*<<< orphan*/  bound_leases; int /*<<< orphan*/  raw_option; int /*<<< orphan*/  leases_by_client_id; int /*<<< orphan*/  sip; int /*<<< orphan*/  ntp; int /*<<< orphan*/  dns; int /*<<< orphan*/  timezone; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ sd_dhcp_server ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_dhcp_server (TYPE_1__*,char*) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  ordered_hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_dhcp_server_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sd_dhcp_server *dhcp_server_free(sd_dhcp_server *server) {
        assert(server);

        log_dhcp_server(server, "UNREF");

        sd_dhcp_server_stop(server);

        sd_event_unref(server->event);

        free(server->timezone);
        free(server->dns);
        free(server->ntp);
        free(server->sip);

        hashmap_free(server->leases_by_client_id);

        ordered_hashmap_free(server->raw_option);

        free(server->bound_leases);
        return mfree(server);
}