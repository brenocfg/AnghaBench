#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  net; } ;
struct TYPE_8__ {TYPE_2__* dht; int /*<<< orphan*/  ping_array; } ;
typedef  TYPE_1__ PING ;
typedef  TYPE_2__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  NET_PACKET_PING_REQUEST ; 
 int /*<<< orphan*/  NET_PACKET_PING_RESPONSE ; 
 int /*<<< orphan*/  PING_NUM_MAX ; 
 int /*<<< orphan*/  PING_TIMEOUT ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  handle_ping_request ; 
 int /*<<< orphan*/  handle_ping_response ; 
 int /*<<< orphan*/  networking_registerhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ ping_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PING *new_ping(DHT *dht)
{
    PING *ping = calloc(1, sizeof(PING));

    if (ping == NULL)
        return NULL;

    if (ping_array_init(&ping->ping_array, PING_NUM_MAX, PING_TIMEOUT) != 0) {
        free(ping);
        return NULL;
    }

    ping->dht = dht;
    networking_registerhandler(ping->dht->net, NET_PACKET_PING_REQUEST, &handle_ping_request, dht);
    networking_registerhandler(ping->dht->net, NET_PACKET_PING_RESPONSE, &handle_ping_response, dht);

    return ping;
}