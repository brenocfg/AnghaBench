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
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ numfriends; struct TYPE_5__* friendlist; int /*<<< orphan*/  net; int /*<<< orphan*/  dht; int /*<<< orphan*/  net_crypto; int /*<<< orphan*/  onion_c; int /*<<< orphan*/  onion_a; int /*<<< orphan*/  onion; int /*<<< orphan*/  fr_c; scalar_t__ tcp_server; } ;
typedef  TYPE_1__ Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  clear_receipts (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  kill_DHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_TCP_server (scalar_t__) ; 
 int /*<<< orphan*/  kill_friend_connections (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_net_crypto (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_networking (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_onion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_onion_announce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_onion_client (int /*<<< orphan*/ ) ; 

void kill_messenger(Messenger *m)
{
    if (!m)
        return;

    uint32_t i;

    if (m->tcp_server) {
        kill_TCP_server(m->tcp_server);
    }

    kill_friend_connections(m->fr_c);
    kill_onion(m->onion);
    kill_onion_announce(m->onion_a);
    kill_onion_client(m->onion_c);
    kill_net_crypto(m->net_crypto);
    kill_DHT(m->dht);
    kill_networking(m->net);

    for (i = 0; i < m->numfriends; ++i) {
        clear_receipts(m, i);
    }

    free(m->friendlist);
    free(m);
}