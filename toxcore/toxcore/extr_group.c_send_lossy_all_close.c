#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {int /*<<< orphan*/  fr_c; } ;
struct TYPE_8__ {TYPE_1__* close; int /*<<< orphan*/ * real_pk; } ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  group_number; int /*<<< orphan*/  number; scalar_t__ closest; } ;
typedef  TYPE_2__ Group_c ;
typedef  TYPE_3__ Group_Chats ;

/* Variables and functions */
 int DESIRED_CLOSE_CONNECTIONS ; 
 scalar_t__ GROUPCHAT_CLOSE_ONLINE ; 
 unsigned int MAX_GROUP_CONNECTIONS ; 
 int /*<<< orphan*/  PACKET_ID_LOSSY_GROUPCHAT ; 
 scalar_t__ calculate_comp_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  get_friendcon_public_keys (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_group_c (TYPE_3__ const*,int) ; 
 scalar_t__ send_lossy_group_peer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int send_lossy_all_close(const Group_Chats *g_c, int groupnumber, const uint8_t *data, uint16_t length,
        int receiver)
{
    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return 0;

    unsigned int i, sent = 0, num_connected_closest = 0, connected_closest[DESIRED_CLOSE_CONNECTIONS];

    for (i = 0; i < MAX_GROUP_CONNECTIONS; ++i) {
        if (g->close[i].type != GROUPCHAT_CLOSE_ONLINE)
            continue;

        if ((int)i == receiver)
            continue;

        if (g->close[i].closest) {
            connected_closest[num_connected_closest] = i;
            ++num_connected_closest;
            continue;
        }

        if (send_lossy_group_peer(g_c->fr_c, g->close[i].number, PACKET_ID_LOSSY_GROUPCHAT, g->close[i].group_number, data,
                                  length))
            ++sent;
    }

    if (!num_connected_closest) {
        return sent;
    }

    unsigned int to_send = 0;
    uint64_t comp_val_old = ~0;

    for (i = 0; i < num_connected_closest; ++i) {
        uint8_t real_pk[crypto_box_PUBLICKEYBYTES];
        uint8_t dht_temp_pk[crypto_box_PUBLICKEYBYTES];
        get_friendcon_public_keys(real_pk, dht_temp_pk, g_c->fr_c, g->close[connected_closest[i]].number);
        uint64_t comp_val = calculate_comp_value(g->real_pk, real_pk);

        if (comp_val < comp_val_old) {
            to_send = connected_closest[i];
            comp_val_old = comp_val;
        }
    }

    if (send_lossy_group_peer(g_c->fr_c, g->close[to_send].number, PACKET_ID_LOSSY_GROUPCHAT,
                              g->close[to_send].group_number, data, length)) {
        ++sent;
    }

    unsigned int to_send_other = 0;
    comp_val_old = ~0;

    for (i = 0; i < num_connected_closest; ++i) {
        uint8_t real_pk[crypto_box_PUBLICKEYBYTES];
        uint8_t dht_temp_pk[crypto_box_PUBLICKEYBYTES];
        get_friendcon_public_keys(real_pk, dht_temp_pk, g_c->fr_c, g->close[connected_closest[i]].number);
        uint64_t comp_val = calculate_comp_value(real_pk, g->real_pk);

        if (comp_val < comp_val_old) {
            to_send_other = connected_closest[i];
            comp_val_old = comp_val;
        }
    }

    if (to_send_other == to_send) {
        return sent;
    }

    if (send_lossy_group_peer(g_c->fr_c, g->close[to_send_other].number, PACKET_ID_LOSSY_GROUPCHAT,
                              g->close[to_send_other].group_number, data, length)) {
        ++sent;
    }

    return sent;
}