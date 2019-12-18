#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  net; } ;
struct TYPE_7__ {int /*<<< orphan*/  net; int /*<<< orphan*/  secret_bytes; TYPE_2__* dht; } ;
typedef  TYPE_1__ Onion_Announce ;
typedef  TYPE_2__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  NET_PACKET_ANNOUNCE_REQUEST ; 
 int /*<<< orphan*/  NET_PACKET_ONION_DATA_REQUEST ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  handle_announce_request ; 
 int /*<<< orphan*/  handle_data_request ; 
 int /*<<< orphan*/  networking_registerhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  new_symmetric_key (int /*<<< orphan*/ ) ; 

Onion_Announce *new_onion_announce(DHT *dht)
{
    if (dht == NULL)
        return NULL;

    Onion_Announce *onion_a = calloc(1, sizeof(Onion_Announce));

    if (onion_a == NULL)
        return NULL;

    onion_a->dht = dht;
    onion_a->net = dht->net;
    new_symmetric_key(onion_a->secret_bytes);

    networking_registerhandler(onion_a->net, NET_PACKET_ANNOUNCE_REQUEST, &handle_announce_request, onion_a);
    networking_registerhandler(onion_a->net, NET_PACKET_ONION_DATA_REQUEST, &handle_data_request, onion_a);

    return onion_a;
}