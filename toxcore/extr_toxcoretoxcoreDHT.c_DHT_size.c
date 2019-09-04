#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_17__ {size_t num_friends; TYPE_7__* friends_list; TYPE_3__* close_clientlist; } ;
struct TYPE_16__ {TYPE_6__* client_list; } ;
struct TYPE_14__ {scalar_t__ timestamp; } ;
struct TYPE_13__ {scalar_t__ timestamp; } ;
struct TYPE_15__ {TYPE_5__ assoc6; TYPE_4__ assoc4; } ;
struct TYPE_11__ {scalar_t__ timestamp; } ;
struct TYPE_10__ {scalar_t__ timestamp; } ;
struct TYPE_12__ {TYPE_2__ assoc6; TYPE_1__ assoc4; } ;
typedef  TYPE_7__ DHT_Friend ;
typedef  TYPE_8__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 size_t DHT_FAKE_FRIEND_NUMBER ; 
 size_t LCLIENT_LIST ; 
 size_t MAX_FRIEND_CLIENTS ; 
 size_t packed_node_size (int /*<<< orphan*/ ) ; 

uint32_t DHT_size(const DHT *dht)
{
    uint32_t numv4 = 0, numv6 = 0, i, j;

    for (i = 0; i < LCLIENT_LIST; ++i) {
        numv4 += (dht->close_clientlist[i].assoc4.timestamp != 0);
        numv6 += (dht->close_clientlist[i].assoc6.timestamp != 0);
    }

    for (i = 0; i < DHT_FAKE_FRIEND_NUMBER && i < dht->num_friends; ++i) {
        DHT_Friend *fr = &dht->friends_list[i];

        for (j = 0; j < MAX_FRIEND_CLIENTS; ++j) {
            numv4 += (fr->client_list[j].assoc4.timestamp != 0);
            numv6 += (fr->client_list[j].assoc6.timestamp != 0);
        }
    }

    uint32_t size32 = sizeof(uint32_t), sizesubhead = size32 * 2;

    return size32 + sizesubhead + (packed_node_size(AF_INET) * numv4) + (packed_node_size(AF_INET6) * numv6);
}