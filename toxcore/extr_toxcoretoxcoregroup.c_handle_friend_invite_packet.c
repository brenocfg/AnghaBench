#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_18__ {int /*<<< orphan*/  fr_c; int /*<<< orphan*/  invite_callback_userdata; int /*<<< orphan*/  (* invite_callback ) (TYPE_2__*,int /*<<< orphan*/ ,int const,int const*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {TYPE_1__* close; int /*<<< orphan*/  identifier; } ;
struct TYPE_16__ {TYPE_4__* group_chat_object; } ;
struct TYPE_15__ {int group_number; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ Messenger ;
typedef  TYPE_3__ Group_c ;
typedef  TYPE_4__ Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  GROUPCHAT_CLOSE_ONLINE ; 
 int /*<<< orphan*/  GROUP_IDENTIFIER_LENGTH ; 
#define  INVITE_ID 129 
 int INVITE_PACKET_SIZE ; 
#define  INVITE_RESPONSE_ID 128 
 int INVITE_RESPONSE_PACKET_SIZE ; 
 int add_conn_to_groupchat (TYPE_4__*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  addpeer (TYPE_4__*,int,int*,int*,int) ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  get_friendcon_public_keys (int*,int*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* get_group_c (TYPE_4__*,int) ; 
 int get_group_num (TYPE_4__*,int const*) ; 
 int get_peer_index (TYPE_3__*,int) ; 
 int getfriendcon_id (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  group_new_peer_send (TYPE_4__*,int,int,int*,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int ntohs (int) ; 
 int rand () ; 
 int /*<<< orphan*/  sodium_memcmp (int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int const,int const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_friend_invite_packet(Messenger *m, uint32_t friendnumber, const uint8_t *data, uint16_t length)
{
    Group_Chats *g_c = m->group_chat_object;

    if (length <= 1)
        return;

    const uint8_t *invite_data = data + 1;
    uint16_t invite_length = length - 1;

    switch (data[0]) {
        case INVITE_ID: {
            if (length != INVITE_PACKET_SIZE)
                return;

            int groupnumber = get_group_num(g_c, data + 1 + sizeof(uint16_t));

            if (groupnumber == -1) {
                if (g_c->invite_callback)
                    g_c->invite_callback(m, friendnumber, *(invite_data + sizeof(uint16_t)), invite_data, invite_length,
                                         g_c->invite_callback_userdata);

                return;
            }

            break;
        }

        case INVITE_RESPONSE_ID: {
            if (length != INVITE_RESPONSE_PACKET_SIZE)
                return;

            uint16_t other_groupnum, groupnum;
            memcpy(&groupnum, data + 1 + sizeof(uint16_t), sizeof(uint16_t));
            groupnum = ntohs(groupnum);

            Group_c *g = get_group_c(g_c, groupnum);

            if (!g)
                return;

            if (sodium_memcmp(data + 1 + sizeof(uint16_t) * 2, g->identifier, GROUP_IDENTIFIER_LENGTH) != 0)
                return;

            uint16_t peer_number = rand(); /* TODO: what if two people enter the group at the same time and
  are given the same peer_number by different nodes? */

            unsigned int tries = 0;

            while (get_peer_index(g, peer_number) != -1) {
                peer_number = rand();
                ++tries;

                if (tries > 32)
                    return;
            }

            memcpy(&other_groupnum, data + 1, sizeof(uint16_t));
            other_groupnum = ntohs(other_groupnum);

            int friendcon_id = getfriendcon_id(m, friendnumber);
            uint8_t real_pk[crypto_box_PUBLICKEYBYTES], temp_pk[crypto_box_PUBLICKEYBYTES];
            get_friendcon_public_keys(real_pk, temp_pk, g_c->fr_c, friendcon_id);

            addpeer(g_c, groupnum, real_pk, temp_pk, peer_number);
            int close_index = add_conn_to_groupchat(g_c, friendcon_id, groupnum, 0, 1);

            if (close_index != -1) {
                g->close[close_index].group_number = other_groupnum;
                g->close[close_index].type = GROUPCHAT_CLOSE_ONLINE;
            }

            group_new_peer_send(g_c, groupnum, peer_number, real_pk, temp_pk);
            break;
        }

        default:
            return;
    }
}