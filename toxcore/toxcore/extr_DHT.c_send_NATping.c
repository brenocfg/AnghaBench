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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  self_secret_key; int /*<<< orphan*/  self_public_key; } ;
typedef  TYPE_1__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_PACKET_NAT_PING ; 
 int MAX_CRYPTO_REQUEST_SIZE ; 
 int create_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int const*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int route_tofriend (TYPE_1__*,int const*,int*,int) ; 
 int routeone_tofriend (TYPE_1__*,int const*,int*,int) ; 

__attribute__((used)) static int send_NATping(DHT *dht, const uint8_t *public_key, uint64_t ping_id, uint8_t type)
{
    uint8_t data[sizeof(uint64_t) + 1];
    uint8_t packet[MAX_CRYPTO_REQUEST_SIZE];

    int num = 0;

    data[0] = type;
    memcpy(data + 1, &ping_id, sizeof(uint64_t));
    /* 254 is NAT ping request packet id */
    int len = create_request(dht->self_public_key, dht->self_secret_key, packet, public_key, data,
                             sizeof(uint64_t) + 1, CRYPTO_PACKET_NAT_PING);

    if (len == -1)
        return -1;

    if (type == 0) /* If packet is request use many people to route it. */
        num = route_tofriend(dht, public_key, packet, len);
    else if (type == 1) /* If packet is response use only one person to route it */
        num = routeone_tofriend(dht, public_key, packet, len);

    if (num == 0)
        return -1;

    return num;
}