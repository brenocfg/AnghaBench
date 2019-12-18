#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int num_friends; TYPE_2__* friends_list; } ;
struct TYPE_8__ {unsigned int num_to_bootstrap; int /*<<< orphan*/  bootstrap_times; int /*<<< orphan*/  client_list; int /*<<< orphan*/  public_key; int /*<<< orphan*/  lastgetnode; TYPE_1__* to_bootstrap; } ;
struct TYPE_7__ {int /*<<< orphan*/  public_key; int /*<<< orphan*/  ip_port; } ;
typedef  TYPE_2__ DHT_Friend ;
typedef  TYPE_3__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_FRIEND_CLIENTS ; 
 int /*<<< orphan*/  do_ping_and_sendnode_requests (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  getnodes (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_DHT_friends(DHT *dht)
{
    unsigned int i, j;

    for (i = 0; i < dht->num_friends; ++i) {
        DHT_Friend *friend = &dht->friends_list[i];

        for (j = 0; j < friend->num_to_bootstrap; ++j) {
            getnodes(dht, friend->to_bootstrap[j].ip_port, friend->to_bootstrap[j].public_key, friend->public_key, NULL);
        }

        friend->num_to_bootstrap = 0;

        do_ping_and_sendnode_requests(dht, &friend->lastgetnode, friend->public_key, friend->client_list, MAX_FRIEND_CLIENTS,
                                      &friend->bootstrap_times, 1);
    }
}