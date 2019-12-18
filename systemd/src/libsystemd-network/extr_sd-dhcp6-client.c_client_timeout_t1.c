#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  timeout_t1; struct TYPE_7__* lease; } ;
typedef  TYPE_1__ sd_event_source ;
typedef  TYPE_1__ sd_dhcp6_client ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP6_STATE_RENEW ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  client_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_source_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_dhcp6_client (TYPE_1__*,char*) ; 

__attribute__((used)) static int client_timeout_t1(sd_event_source *s, uint64_t usec, void *userdata) {
        sd_dhcp6_client *client = userdata;

        assert(s);
        assert(client);
        assert(client->lease);

        (void) event_source_disable(client->timeout_t1);

        log_dhcp6_client(client, "Timeout T1");

        client_start(client, DHCP6_STATE_RENEW);

        return 0;
}