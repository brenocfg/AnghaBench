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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  sa_family_t ;
struct TYPE_5__ {size_t num_friends; TYPE_1__* friends_list; int /*<<< orphan*/  close_clientlist; } ;
struct TYPE_4__ {int /*<<< orphan*/  client_list; } ;
typedef  int /*<<< orphan*/  Node_format ;
typedef  TYPE_2__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  LCLIENT_LIST ; 
 int /*<<< orphan*/  MAX_FRIEND_CLIENTS ; 
 int /*<<< orphan*/  get_close_nodes_inner (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_somewhat_close_nodes(const DHT *dht, const uint8_t *public_key, Node_format *nodes_list,
                                    sa_family_t sa_family, uint8_t is_LAN, uint8_t want_good)
{
    uint32_t num_nodes = 0, i;
    get_close_nodes_inner(public_key, nodes_list, sa_family,
                          dht->close_clientlist, LCLIENT_LIST, &num_nodes, is_LAN, 0);

    /*TODO uncomment this when hardening is added to close friend clients
        for (i = 0; i < dht->num_friends; ++i)
            get_close_nodes_inner(dht, public_key, nodes_list, sa_family,
                                  dht->friends_list[i].client_list, MAX_FRIEND_CLIENTS,
                                  &num_nodes, is_LAN, want_good);
    */
    for (i = 0; i < dht->num_friends; ++i)
        get_close_nodes_inner(public_key, nodes_list, sa_family,
                              dht->friends_list[i].client_list, MAX_FRIEND_CLIENTS,
                              &num_nodes, is_LAN, 0);

    return num_nodes;
}