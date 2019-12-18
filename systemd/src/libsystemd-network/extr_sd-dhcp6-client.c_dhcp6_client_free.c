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
struct TYPE_9__ {int /*<<< orphan*/  fqdn; int /*<<< orphan*/  req_opts; int /*<<< orphan*/  fd; void* timeout_t2; void* timeout_t1; void* timeout_resend_expire; void* timeout_resend; } ;
typedef  TYPE_1__ sd_dhcp6_client ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  client_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_dhcp6_client_detach_event (TYPE_1__*) ; 
 void* sd_event_source_unref (void*) ; 

__attribute__((used)) static sd_dhcp6_client *dhcp6_client_free(sd_dhcp6_client *client) {
        assert(client);

        client->timeout_resend = sd_event_source_unref(client->timeout_resend);
        client->timeout_resend_expire = sd_event_source_unref(client->timeout_resend_expire);
        client->timeout_t1 = sd_event_source_unref(client->timeout_t1);
        client->timeout_t2 = sd_event_source_unref(client->timeout_t2);

        client_reset(client);

        client->fd = safe_close(client->fd);

        sd_dhcp6_client_detach_event(client);

        free(client->req_opts);
        free(client->fqdn);
        return mfree(client);
}