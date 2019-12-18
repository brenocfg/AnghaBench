#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_20__ {size_t num_friends; TYPE_8__* friends_list; TYPE_3__* close_clientlist; } ;
struct TYPE_19__ {TYPE_6__* client_list; } ;
struct TYPE_18__ {int /*<<< orphan*/  ip_port; int /*<<< orphan*/  public_key; } ;
struct TYPE_16__ {scalar_t__ timestamp; int /*<<< orphan*/  ip_port; } ;
struct TYPE_15__ {scalar_t__ timestamp; int /*<<< orphan*/  ip_port; } ;
struct TYPE_17__ {TYPE_5__ assoc6; int /*<<< orphan*/  public_key; TYPE_4__ assoc4; } ;
struct TYPE_13__ {scalar_t__ timestamp; int /*<<< orphan*/  ip_port; } ;
struct TYPE_12__ {scalar_t__ timestamp; int /*<<< orphan*/  ip_port; } ;
struct TYPE_14__ {TYPE_2__ assoc6; int /*<<< orphan*/  public_key; TYPE_1__ assoc4; } ;
typedef  TYPE_7__ Node_format ;
typedef  TYPE_8__ DHT_Friend ;
typedef  TYPE_9__ DHT ;

/* Variables and functions */
 size_t DHT_FAKE_FRIEND_NUMBER ; 
 int /*<<< orphan*/  DHT_STATE_COOKIE_GLOBAL ; 
 int /*<<< orphan*/  DHT_STATE_TYPE_NODES ; 
 size_t LCLIENT_LIST ; 
 size_t MAX_FRIEND_CLIENTS ; 
 int MAX_SAVED_DHT_NODES ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  host_to_lendian32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pack_nodes (int /*<<< orphan*/ *,int,TYPE_7__*,size_t) ; 
 int /*<<< orphan*/ * z_state_save_subheader (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void DHT_save(DHT *dht, uint8_t *data)
{
    host_to_lendian32(data,  DHT_STATE_COOKIE_GLOBAL);
    data += sizeof(uint32_t);

    uint32_t num, i, j;

    uint8_t *old_data = data;

    /* get right offset. we write the actual header later. */
    data = z_state_save_subheader(data, 0, 0);

    Node_format clients[MAX_SAVED_DHT_NODES];

    for (num = 0, i = 0; i < LCLIENT_LIST; ++i) {
        if (dht->close_clientlist[i].assoc4.timestamp != 0) {
            memcpy(clients[num].public_key, dht->close_clientlist[i].public_key, crypto_box_PUBLICKEYBYTES);
            clients[num].ip_port = dht->close_clientlist[i].assoc4.ip_port;
            ++num;
        }

        if (dht->close_clientlist[i].assoc6.timestamp != 0) {
            memcpy(clients[num].public_key, dht->close_clientlist[i].public_key, crypto_box_PUBLICKEYBYTES);
            clients[num].ip_port = dht->close_clientlist[i].assoc6.ip_port;
            ++num;
        }
    }

    for (i = 0; i < DHT_FAKE_FRIEND_NUMBER && i < dht->num_friends; ++i) {
        DHT_Friend *fr = &dht->friends_list[i];

        for (j = 0; j < MAX_FRIEND_CLIENTS; ++j) {
            if (fr->client_list[j].assoc4.timestamp != 0) {
                memcpy(clients[num].public_key, fr->client_list[j].public_key, crypto_box_PUBLICKEYBYTES);
                clients[num].ip_port = fr->client_list[j].assoc4.ip_port;
                ++num;
            }

            if (fr->client_list[j].assoc6.timestamp != 0) {
                memcpy(clients[num].public_key, fr->client_list[j].public_key, crypto_box_PUBLICKEYBYTES);
                clients[num].ip_port = fr->client_list[j].assoc6.ip_port;
                ++num;
            }
        }
    }

    z_state_save_subheader(old_data, pack_nodes(data, sizeof(Node_format) * num, clients, num), DHT_STATE_TYPE_NODES);
}