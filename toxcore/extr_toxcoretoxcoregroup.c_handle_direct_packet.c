#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_12__ {int /*<<< orphan*/  fr_c; } ;
struct TYPE_11__ {TYPE_1__* close; } ;
struct TYPE_10__ {int /*<<< orphan*/  group_number; int /*<<< orphan*/  number; int /*<<< orphan*/  type; int /*<<< orphan*/  closest; } ;
typedef  TYPE_2__ Group_c ;
typedef  TYPE_3__ Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  GROUPCHAT_CLOSE_NONE ; 
#define  PEER_KILL_ID 131 
#define  PEER_QUERY_ID 130 
#define  PEER_RESPONSE_ID 129 
#define  PEER_TITLE_ID 128 
 TYPE_2__* get_group_c (TYPE_3__*,int) ; 
 int /*<<< orphan*/  handle_send_peers (TYPE_3__*,int,int const*,scalar_t__) ; 
 int /*<<< orphan*/  kill_friend_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_peers (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settitle (TYPE_3__*,int,int,int const*,scalar_t__) ; 

__attribute__((used)) static void handle_direct_packet(Group_Chats *g_c, int groupnumber, const uint8_t *data, uint16_t length,
                                 int close_index)
{
    if (length == 0)
        return;

    switch (data[0]) {
        case PEER_KILL_ID: {
            Group_c *g = get_group_c(g_c, groupnumber);

            if (!g)
                return;

            if (!g->close[close_index].closest) {
                g->close[close_index].type = GROUPCHAT_CLOSE_NONE;
                kill_friend_connection(g_c->fr_c, g->close[close_index].number);
            }
        }

        break;

        case PEER_QUERY_ID: {
            Group_c *g = get_group_c(g_c, groupnumber);

            if (!g)
                return;

            send_peers(g_c, groupnumber, g->close[close_index].number, g->close[close_index].group_number);
        }

        break;

        case PEER_RESPONSE_ID: {
            handle_send_peers(g_c, groupnumber, data + 1, length - 1);
        }

        break;

        case PEER_TITLE_ID: {
            settitle(g_c, groupnumber, -1, data + 1, length - 1);
        }

        break;
    }
}