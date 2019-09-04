#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  unsigned int uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  ip; } ;
struct TYPE_9__ {int /*<<< orphan*/  ip_port; int /*<<< orphan*/  ret_timestamp; TYPE_1__ ret_ip_port; } ;
struct TYPE_12__ {TYPE_2__ assoc6; TYPE_2__ assoc4; } ;
struct TYPE_11__ {int /*<<< orphan*/  net; TYPE_3__* friends_list; } ;
struct TYPE_10__ {TYPE_5__* client_list; } ;
typedef  int /*<<< orphan*/  IP_Port ;
typedef  TYPE_2__ IPPTsPng ;
typedef  TYPE_3__ DHT_Friend ;
typedef  TYPE_4__ DHT ;
typedef  TYPE_5__ Client_data ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_NODE_TIMEOUT ; 
 int MAX_FRIEND_CLIENTS ; 
 int friend_number (TYPE_4__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ ip_isset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rand () ; 
 int sendpacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int routeone_tofriend(DHT *dht, const uint8_t *friend_id, const uint8_t *packet, uint16_t length)
{
    int num = friend_number(dht, friend_id);

    if (num == -1)
        return 0;

    DHT_Friend *friend = &dht->friends_list[num];
    Client_data *client;

    IP_Port ip_list[MAX_FRIEND_CLIENTS * 2];
    int n = 0;
    uint32_t i;

    /* extra legwork, because having the outside allocating the space for us
     * is *usually* good(tm) (bites us in the behind in this case though) */
    uint32_t a;

    for (a = 0; a < 2; a++)
        for (i = 0; i < MAX_FRIEND_CLIENTS; ++i) {
            client = &friend->client_list[i];
            IPPTsPng *assoc = NULL;

            if (!a)
                assoc = &client->assoc4;
            else
                assoc = &client->assoc6;

            /* If ip is not zero and node is good. */
            if (ip_isset(&assoc->ret_ip_port.ip) && !is_timeout(assoc->ret_timestamp, BAD_NODE_TIMEOUT)) {
                ip_list[n] = assoc->ip_port;
                ++n;
            }
        }

    if (n < 1)
        return 0;

    int retval = sendpacket(dht->net, ip_list[rand() % n], packet, length);

    if ((unsigned int)retval == length)
        return 1;

    return 0;
}