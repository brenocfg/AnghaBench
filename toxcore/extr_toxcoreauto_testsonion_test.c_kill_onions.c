#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* dht; } ;
struct TYPE_10__ {int /*<<< orphan*/ * c; } ;
struct TYPE_9__ {int /*<<< orphan*/ * net; } ;
struct TYPE_8__ {TYPE_5__* onion; int /*<<< orphan*/  onion_a; TYPE_4__* onion_c; } ;
typedef  TYPE_1__ Onions ;
typedef  int /*<<< orphan*/  Networking_Core ;
typedef  int /*<<< orphan*/  Net_Crypto ;
typedef  TYPE_2__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  kill_DHT (TYPE_2__*) ; 
 int /*<<< orphan*/  kill_net_crypto (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_networking (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_onion (TYPE_5__*) ; 
 int /*<<< orphan*/  kill_onion_announce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_onion_client (TYPE_4__*) ; 

void kill_onions(Onions *on)
{
    Networking_Core *net = on->onion->dht->net;
    DHT *dht = on->onion->dht;
    Net_Crypto *c = on->onion_c->c;
    kill_onion_client(on->onion_c);
    kill_onion_announce(on->onion_a);
    kill_onion(on->onion);
    kill_net_crypto(c);
    kill_DHT(dht);
    kill_networking(net);
    free(on);
}