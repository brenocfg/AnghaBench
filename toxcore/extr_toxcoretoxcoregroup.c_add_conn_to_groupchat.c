#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_12__ {TYPE_2__* m; int /*<<< orphan*/  fr_c; } ;
struct TYPE_11__ {TYPE_1__* close; } ;
struct TYPE_10__ {int /*<<< orphan*/  fr_c; } ;
struct TYPE_9__ {scalar_t__ type; int number; void* closest; } ;
typedef  TYPE_3__ Group_c ;
typedef  TYPE_4__ Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  GROUPCHAT_CALLBACK_INDEX ; 
 scalar_t__ GROUPCHAT_CLOSE_CONNECTION ; 
 scalar_t__ GROUPCHAT_CLOSE_NONE ; 
 size_t MAX_GROUP_CONNECTIONS ; 
 int /*<<< orphan*/  friend_connection_callbacks (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  friend_connection_lock (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* get_group_c (TYPE_4__*,int) ; 
 int /*<<< orphan*/  handle_lossy ; 
 int /*<<< orphan*/  handle_packet ; 
 int /*<<< orphan*/  handle_status ; 

__attribute__((used)) static int add_conn_to_groupchat(Group_Chats *g_c, int friendcon_id, int groupnumber, uint8_t closest, uint8_t lock)
{
    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return -1;

    uint16_t i, ind = MAX_GROUP_CONNECTIONS;

    for (i = 0; i < MAX_GROUP_CONNECTIONS; ++i) {
        if (g->close[i].type == GROUPCHAT_CLOSE_NONE) {
            ind = i;
            continue;
        }

        if (g->close[i].number == (uint32_t)friendcon_id) {
            g->close[i].closest = closest;
            return i; /* Already in list. */
        }
    }

    if (ind == MAX_GROUP_CONNECTIONS)
        return -1;

    if (lock)
        friend_connection_lock(g_c->fr_c, friendcon_id);

    g->close[ind].type = GROUPCHAT_CLOSE_CONNECTION;
    g->close[ind].number = friendcon_id;
    g->close[ind].closest = closest;
    //TODO
    friend_connection_callbacks(g_c->m->fr_c, friendcon_id, GROUPCHAT_CALLBACK_INDEX, &handle_status, &handle_packet,
                                &handle_lossy, g_c, friendcon_id);

    return ind;
}