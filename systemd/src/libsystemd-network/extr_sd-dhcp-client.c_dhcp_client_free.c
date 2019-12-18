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
struct TYPE_9__ {int /*<<< orphan*/  options; int /*<<< orphan*/  user_class; int /*<<< orphan*/  vendor_class_identifier; int /*<<< orphan*/  hostname; int /*<<< orphan*/  req_opts; int /*<<< orphan*/  lease; void* timeout_expire; void* timeout_t2; void* timeout_t1; void* timeout_resend; } ;
typedef  TYPE_1__ sd_dhcp_client ;

/* Variables and functions */
 int /*<<< orphan*/  client_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_dhcp_client (TYPE_1__*,char*) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  ordered_hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_dhcp_client_detach_event (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_dhcp_lease_unref (int /*<<< orphan*/ ) ; 
 void* sd_event_source_unref (void*) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sd_dhcp_client *dhcp_client_free(sd_dhcp_client *client) {
        if (!client)
                return NULL;

        log_dhcp_client(client, "FREE");

        client->timeout_resend = sd_event_source_unref(client->timeout_resend);
        client->timeout_t1 = sd_event_source_unref(client->timeout_t1);
        client->timeout_t2 = sd_event_source_unref(client->timeout_t2);
        client->timeout_expire = sd_event_source_unref(client->timeout_expire);

        client_initialize(client);

        sd_dhcp_client_detach_event(client);

        sd_dhcp_lease_unref(client->lease);

        free(client->req_opts);
        free(client->hostname);
        free(client->vendor_class_identifier);
        client->user_class = strv_free(client->user_class);
        ordered_hashmap_free(client->options);
        return mfree(client);
}