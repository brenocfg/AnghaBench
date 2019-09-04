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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {int /*<<< orphan*/  ip; } ;
struct TYPE_8__ {TYPE_5__ ip_port; } ;
struct TYPE_7__ {TYPE_5__ ip_port; } ;
struct TYPE_10__ {TYPE_2__ assoc4; TYPE_1__ assoc6; int /*<<< orphan*/  public_key; } ;
struct TYPE_9__ {int /*<<< orphan*/  net; TYPE_4__* close_clientlist; } ;
typedef  TYPE_3__ DHT ;
typedef  TYPE_4__ Client_data ;

/* Variables and functions */
 size_t LCLIENT_LIST ; 
 scalar_t__ id_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ip_isset (int /*<<< orphan*/ *) ; 
 int sendpacket (int /*<<< orphan*/ ,TYPE_5__,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int route_packet(const DHT *dht, const uint8_t *public_key, const uint8_t *packet, uint16_t length)
{
    uint32_t i;

    for (i = 0; i < LCLIENT_LIST; ++i) {
        if (id_equal(public_key, dht->close_clientlist[i].public_key)) {
            const Client_data *client = &dht->close_clientlist[i];

            if (ip_isset(&client->assoc6.ip_port.ip))
                return sendpacket(dht->net, client->assoc6.ip_port, packet, length);
            else if (ip_isset(&client->assoc4.ip_port.ip))
                return sendpacket(dht->net, client->assoc4.ip_port, packet, length);
            else
                break;
        }
    }

    return -1;
}