#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_24__ {size_t num_friends; scalar_t__ assoc; TYPE_6__* friends_list; int /*<<< orphan*/  close_clientlist; } ;
struct TYPE_23__ {size_t lock_count; TYPE_3__* callbacks; int /*<<< orphan*/  public_key; int /*<<< orphan*/  client_list; } ;
struct TYPE_17__ {int /*<<< orphan*/ * uint32; } ;
struct TYPE_18__ {int /*<<< orphan*/  uint32; } ;
struct TYPE_19__ {scalar_t__ family; TYPE_15__ ip6; TYPE_1__ ip4; } ;
struct TYPE_21__ {TYPE_2__ ip; } ;
struct TYPE_22__ {int /*<<< orphan*/  timestamp; TYPE_4__ ip_port; } ;
struct TYPE_20__ {int /*<<< orphan*/  number; int /*<<< orphan*/  data; int /*<<< orphan*/  (* ip_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__) ;} ;
typedef  TYPE_4__ IP_Port ;
typedef  TYPE_5__ IPPTs ;
typedef  TYPE_6__ DHT_Friend ;
typedef  TYPE_7__ DHT ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  Assoc_add_entry (scalar_t__,int /*<<< orphan*/  const*,TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ IPV6_IPV4_IN_V6 (TYPE_15__) ; 
 int /*<<< orphan*/  LCLIENT_LIST ; 
 int /*<<< orphan*/  MAX_FRIEND_CLIENTS ; 
 scalar_t__ add_to_close (TYPE_7__*,int /*<<< orphan*/  const*,TYPE_4__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_or_ip_port_in_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_4__) ; 
 scalar_t__ public_key_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ replace_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_4__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__) ; 
 int /*<<< orphan*/  unix_time () ; 

int addto_lists(DHT *dht, IP_Port ip_port, const uint8_t *public_key)
{
    uint32_t i, used = 0;

    /* convert IPv4-in-IPv6 to IPv4 */
    if ((ip_port.ip.family == AF_INET6) && IPV6_IPV4_IN_V6(ip_port.ip.ip6)) {
        ip_port.ip.family = AF_INET;
        ip_port.ip.ip4.uint32 = ip_port.ip.ip6.uint32[3];
    }

    /* NOTE: Current behavior if there are two clients with the same id is
     * to replace the first ip by the second.
     */
    if (!client_or_ip_port_in_list(dht->close_clientlist, LCLIENT_LIST, public_key, ip_port)) {
        if (add_to_close(dht, public_key, ip_port, 0))
            used++;
    } else
        used++;

    DHT_Friend *friend_foundip = 0;

    for (i = 0; i < dht->num_friends; ++i) {
        if (!client_or_ip_port_in_list(dht->friends_list[i].client_list,
                                       MAX_FRIEND_CLIENTS, public_key, ip_port)) {
            if (replace_all(dht->friends_list[i].client_list, MAX_FRIEND_CLIENTS,
                            public_key, ip_port, dht->friends_list[i].public_key)) {

                DHT_Friend *friend = &dht->friends_list[i];

                if (public_key_cmp(public_key, friend->public_key) == 0) {
                    friend_foundip = friend;
                }

                used++;
            }
        } else {
            DHT_Friend *friend = &dht->friends_list[i];

            if (public_key_cmp(public_key, friend->public_key) == 0) {
                friend_foundip = friend;
            }

            used++;
        }
    }

    if (friend_foundip) {
        uint32_t j;

        for (j = 0; j < friend_foundip->lock_count; ++j) {
            if (friend_foundip->callbacks[j].ip_callback)
                friend_foundip->callbacks[j].ip_callback(friend_foundip->callbacks[j].data, friend_foundip->callbacks[j].number,
                        ip_port);
        }
    }

#ifdef ENABLE_ASSOC_DHT

    if (dht->assoc) {
        IPPTs ippts;

        ippts.ip_port = ip_port;
        ippts.timestamp = unix_time();

        Assoc_add_entry(dht->assoc, public_key, &ippts, NULL, used ? 1 : 0);
    }

#endif
    return used;
}