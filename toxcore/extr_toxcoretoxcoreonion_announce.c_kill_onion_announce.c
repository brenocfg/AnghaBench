#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  net; } ;
typedef  TYPE_1__ Onion_Announce ;

/* Variables and functions */
 int /*<<< orphan*/  NET_PACKET_ANNOUNCE_REQUEST ; 
 int /*<<< orphan*/  NET_PACKET_ONION_DATA_REQUEST ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  networking_registerhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void kill_onion_announce(Onion_Announce *onion_a)
{
    if (onion_a == NULL)
        return;

    networking_registerhandler(onion_a->net, NET_PACKET_ANNOUNCE_REQUEST, NULL, NULL);
    networking_registerhandler(onion_a->net, NET_PACKET_ONION_DATA_REQUEST, NULL, NULL);
    free(onion_a);
}