#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {scalar_t__ timestamp; } ;
struct TYPE_12__ {TYPE_2__ assoc6; TYPE_2__ assoc4; } ;
struct TYPE_11__ {unsigned int num_to_bootstrap; TYPE_4__* close_clientlist; int /*<<< orphan*/  close_bootstrap_times; int /*<<< orphan*/  self_public_key; int /*<<< orphan*/  close_lastgetnodes; TYPE_1__* to_bootstrap; } ;
struct TYPE_9__ {int /*<<< orphan*/  public_key; int /*<<< orphan*/  ip_port; } ;
typedef  TYPE_2__ IPPTsPng ;
typedef  TYPE_3__ DHT ;
typedef  TYPE_4__ Client_data ;

/* Variables and functions */
 scalar_t__ BAD_NODE_TIMEOUT ; 
 size_t LCLIENT_LIST ; 
 int /*<<< orphan*/  do_ping_and_sendnode_requests (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getnodes (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unix_time () ; 

__attribute__((used)) static void do_Close(DHT *dht)
{
    unsigned int i;

    for (i = 0; i < dht->num_to_bootstrap; ++i) {
        getnodes(dht, dht->to_bootstrap[i].ip_port, dht->to_bootstrap[i].public_key, dht->self_public_key, NULL);
    }

    dht->num_to_bootstrap = 0;

    uint8_t not_killed = do_ping_and_sendnode_requests(dht, &dht->close_lastgetnodes, dht->self_public_key,
                         dht->close_clientlist, LCLIENT_LIST, &dht->close_bootstrap_times, 0);

    if (!not_killed) {
        /* all existing nodes are at least KILL_NODE_TIMEOUT,
         * which means we are mute, as we only send packets to
         * nodes NOT in KILL_NODE_TIMEOUT
         *
         * so: reset all nodes to be BAD_NODE_TIMEOUT, but not
         * KILL_NODE_TIMEOUT, so we at least keep trying pings */
        uint64_t badonly = unix_time() - BAD_NODE_TIMEOUT;
        size_t i, a;

        for (i = 0; i < LCLIENT_LIST; i++) {
            Client_data *client = &dht->close_clientlist[i];
            IPPTsPng *assoc;

            for (a = 0, assoc = &client->assoc4; a < 2; a++, assoc = &client->assoc6)
                if (assoc->timestamp)
                    assoc->timestamp = badonly;
        }
    }
}