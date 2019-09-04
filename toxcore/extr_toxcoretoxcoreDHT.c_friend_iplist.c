#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_13__ {int /*<<< orphan*/  ip; } ;
struct TYPE_12__ {int /*<<< orphan*/  timestamp; TYPE_3__ ret_ip_port; int /*<<< orphan*/  ret_timestamp; } ;
struct TYPE_11__ {int /*<<< orphan*/  timestamp; TYPE_3__ ret_ip_port; int /*<<< orphan*/  ret_timestamp; } ;
struct TYPE_16__ {TYPE_2__ assoc4; TYPE_1__ assoc6; int /*<<< orphan*/  public_key; } ;
struct TYPE_15__ {size_t num_friends; TYPE_4__* friends_list; } ;
struct TYPE_14__ {int /*<<< orphan*/  public_key; TYPE_6__* client_list; } ;
typedef  TYPE_3__ IP_Port ;
typedef  TYPE_4__ DHT_Friend ;
typedef  TYPE_5__ DHT ;
typedef  TYPE_6__ Client_data ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_NODE_TIMEOUT ; 
 int MAX_FRIEND_CLIENTS ; 
 scalar_t__ id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ip_isset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 

__attribute__((used)) static int friend_iplist(const DHT *dht, IP_Port *ip_portlist, uint16_t friend_num)
{
    if (friend_num >= dht->num_friends)
        return -1;

    DHT_Friend *friend = &dht->friends_list[friend_num];
    Client_data *client;
    IP_Port ipv4s[MAX_FRIEND_CLIENTS];
    int num_ipv4s = 0;
    IP_Port ipv6s[MAX_FRIEND_CLIENTS];
    int num_ipv6s = 0;
    int i;

    for (i = 0; i < MAX_FRIEND_CLIENTS; ++i) {
        client = &(friend->client_list[i]);

        /* If ip is not zero and node is good. */
        if (ip_isset(&client->assoc4.ret_ip_port.ip) && !is_timeout(client->assoc4.ret_timestamp, BAD_NODE_TIMEOUT)) {
            ipv4s[num_ipv4s] = client->assoc4.ret_ip_port;
            ++num_ipv4s;
        }

        if (ip_isset(&client->assoc6.ret_ip_port.ip) && !is_timeout(client->assoc6.ret_timestamp, BAD_NODE_TIMEOUT)) {
            ipv6s[num_ipv6s] = client->assoc6.ret_ip_port;
            ++num_ipv6s;
        }

        if (id_equal(client->public_key, friend->public_key))
            if (!is_timeout(client->assoc6.timestamp, BAD_NODE_TIMEOUT) || !is_timeout(client->assoc4.timestamp, BAD_NODE_TIMEOUT))
                return 0; /* direct connectivity */
    }

#ifdef FRIEND_IPLIST_PAD
    memcpy(ip_portlist, ipv6s, num_ipv6s * sizeof(IP_Port));

    if (num_ipv6s == MAX_FRIEND_CLIENTS)
        return MAX_FRIEND_CLIENTS;

    int num_ipv4s_used = MAX_FRIEND_CLIENTS - num_ipv6s;

    if (num_ipv4s_used > num_ipv4s)
        num_ipv4s_used = num_ipv4s;

    memcpy(&ip_portlist[num_ipv6s], ipv4s, num_ipv4s_used * sizeof(IP_Port));
    return num_ipv6s + num_ipv4s_used;

#else /* !FRIEND_IPLIST_PAD */

    /* there must be some secret reason why we can't pad the longer list
     * with the shorter one...
     */
    if (num_ipv6s >= num_ipv4s) {
        memcpy(ip_portlist, ipv6s, num_ipv6s * sizeof(IP_Port));
        return num_ipv6s;
    }

    memcpy(ip_portlist, ipv4s, num_ipv4s * sizeof(IP_Port));
    return num_ipv4s;

#endif /* !FRIEND_IPLIST_PAD */
}