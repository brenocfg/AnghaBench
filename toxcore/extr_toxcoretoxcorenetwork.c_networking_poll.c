#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {scalar_t__ family; TYPE_1__* packethandlers; int /*<<< orphan*/  sock; } ;
struct TYPE_4__ {int /*<<< orphan*/  object; int /*<<< orphan*/  (* function ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int) ;} ;
typedef  TYPE_2__ Networking_Core ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_WARNING (char*,size_t) ; 
 int MAX_UDP_PACKET_SIZE ; 
 int receivepacket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int) ; 
 int /*<<< orphan*/  unix_time_update () ; 

void networking_poll(Networking_Core *net)
{
    if (net->family == 0) /* Socket not initialized */
        return;

    unix_time_update();

    IP_Port ip_port;
    uint8_t data[MAX_UDP_PACKET_SIZE];
    uint32_t length;

    while (receivepacket(net->sock, &ip_port, data, &length) != -1) {
        if (length < 1) continue;

        if (!(net->packethandlers[data[0]].function)) {
            LOGGER_WARNING("[%02u] -- Packet has no handler", data[0]);
            continue;
        }

        net->packethandlers[data[0]].function(net->packethandlers[data[0]].object, ip_port, data, length);
    }
}