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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  ip; } ;
typedef  TYPE_1__ IP_Port ;
typedef  int /*<<< orphan*/  DHT ;

/* Variables and functions */
 int /*<<< orphan*/  DHT_bootstrap (int /*<<< orphan*/ *,TYPE_1__,int /*<<< orphan*/  const*) ; 
 int LAN_ip (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_box_PUBLICKEYBYTES ; 

__attribute__((used)) static int handle_LANdiscovery(void *object, IP_Port source, const uint8_t *packet, uint16_t length)
{
    DHT *dht = object;

    if (LAN_ip(source.ip) == -1)
        return 1;

    if (length != crypto_box_PUBLICKEYBYTES + 1)
        return 1;

    DHT_bootstrap(dht, source, packet + 1);
    return 0;
}