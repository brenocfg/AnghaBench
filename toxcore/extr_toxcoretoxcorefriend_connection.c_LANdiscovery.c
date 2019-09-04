#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ last_LANdiscovery; int /*<<< orphan*/  dht; } ;
typedef  TYPE_1__ Friend_Connections ;

/* Variables and functions */
 scalar_t__ LAN_DISCOVERY_INTERVAL ; 
 int /*<<< orphan*/  TOX_PORT_DEFAULT ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_LANdiscovery (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unix_time () ; 

__attribute__((used)) static void LANdiscovery(Friend_Connections *fr_c)
{
    if (fr_c->last_LANdiscovery + LAN_DISCOVERY_INTERVAL < unix_time()) {
        send_LANdiscovery(htons(TOX_PORT_DEFAULT), fr_c->dht);
        fr_c->last_LANdiscovery = unix_time();
    }
}