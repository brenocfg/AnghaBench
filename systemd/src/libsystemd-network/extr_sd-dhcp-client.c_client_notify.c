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
struct TYPE_5__ {int (* callback ) (TYPE_1__*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  userdata; } ;
typedef  TYPE_1__ sd_dhcp_client ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int stub1 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int client_notify(sd_dhcp_client *client, int event) {
        assert(client);

        if (client->callback)
                return client->callback(client, event, client->userdata);

        return 0;
}