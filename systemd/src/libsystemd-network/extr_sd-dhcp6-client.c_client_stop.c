#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sd_dhcp6_client ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP6_CLIENT_DONT_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  client_notify (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  client_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void client_stop(sd_dhcp6_client *client, int error) {
        DHCP6_CLIENT_DONT_DESTROY(client);

        assert(client);

        client_notify(client, error);

        client_reset(client);
}