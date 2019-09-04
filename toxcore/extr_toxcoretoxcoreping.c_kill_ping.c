#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ping_array; TYPE_1__* dht; } ;
struct TYPE_5__ {int /*<<< orphan*/  net; } ;
typedef  TYPE_2__ PING ;

/* Variables and functions */
 int /*<<< orphan*/  NET_PACKET_PING_REQUEST ; 
 int /*<<< orphan*/  NET_PACKET_PING_RESPONSE ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  networking_registerhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ping_array_free_all (int /*<<< orphan*/ *) ; 

void kill_ping(PING *ping)
{
    networking_registerhandler(ping->dht->net, NET_PACKET_PING_REQUEST, NULL, NULL);
    networking_registerhandler(ping->dht->net, NET_PACKET_PING_RESPONSE, NULL, NULL);
    ping_array_free_all(&ping->ping_array);

    free(ping);
}