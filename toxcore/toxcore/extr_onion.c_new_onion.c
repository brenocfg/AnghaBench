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
struct TYPE_7__ {int /*<<< orphan*/  net; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  secret_symmetric_key; TYPE_2__* dht; } ;
typedef  TYPE_1__ Onion ;
typedef  TYPE_2__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  NET_PACKET_ONION_RECV_1 ; 
 int /*<<< orphan*/  NET_PACKET_ONION_RECV_2 ; 
 int /*<<< orphan*/  NET_PACKET_ONION_RECV_3 ; 
 int /*<<< orphan*/  NET_PACKET_ONION_SEND_1 ; 
 int /*<<< orphan*/  NET_PACKET_ONION_SEND_2 ; 
 int /*<<< orphan*/  NET_PACKET_ONION_SEND_INITIAL ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  handle_recv_1 ; 
 int /*<<< orphan*/  handle_recv_2 ; 
 int /*<<< orphan*/  handle_recv_3 ; 
 int /*<<< orphan*/  handle_send_1 ; 
 int /*<<< orphan*/  handle_send_2 ; 
 int /*<<< orphan*/  handle_send_initial ; 
 int /*<<< orphan*/  networking_registerhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  new_symmetric_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unix_time () ; 

Onion *new_onion(DHT *dht)
{
    if (dht == NULL)
        return NULL;

    Onion *onion = calloc(1, sizeof(Onion));

    if (onion == NULL)
        return NULL;

    onion->dht = dht;
    onion->net = dht->net;
    new_symmetric_key(onion->secret_symmetric_key);
    onion->timestamp = unix_time();

    networking_registerhandler(onion->net, NET_PACKET_ONION_SEND_INITIAL, &handle_send_initial, onion);
    networking_registerhandler(onion->net, NET_PACKET_ONION_SEND_1, &handle_send_1, onion);
    networking_registerhandler(onion->net, NET_PACKET_ONION_SEND_2, &handle_send_2, onion);

    networking_registerhandler(onion->net, NET_PACKET_ONION_RECV_3, &handle_recv_3, onion);
    networking_registerhandler(onion->net, NET_PACKET_ONION_RECV_2, &handle_recv_2, onion);
    networking_registerhandler(onion->net, NET_PACKET_ONION_RECV_1, &handle_recv_1, onion);

    return onion;
}