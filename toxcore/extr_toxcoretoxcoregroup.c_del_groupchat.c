#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  object; } ;
struct TYPE_12__ {int /*<<< orphan*/  fr_c; } ;
struct TYPE_11__ {unsigned int numpeers; int /*<<< orphan*/  object; int /*<<< orphan*/  (* group_on_delete ) (int /*<<< orphan*/ ,int) ;TYPE_8__* group; int /*<<< orphan*/  (* peer_on_leave ) (int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ) ;TYPE_1__* close; int /*<<< orphan*/  peer_number; } ;
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/  number; } ;
typedef  TYPE_2__ Group_c ;
typedef  TYPE_3__ Group_Chats ;

/* Variables and functions */
 scalar_t__ GROUPCHAT_CLOSE_NONE ; 
 unsigned int MAX_GROUP_CONNECTIONS ; 
 int /*<<< orphan*/  free (TYPE_8__*) ; 
 TYPE_2__* get_group_c (TYPE_3__*,int) ; 
 int /*<<< orphan*/  group_kill_peer_send (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_friend_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int wipe_group_chat (TYPE_3__*,int) ; 

int del_groupchat(Group_Chats *g_c, int groupnumber)
{
    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return -1;

    group_kill_peer_send(g_c, groupnumber, g->peer_number);

    unsigned int i;

    for (i = 0; i < MAX_GROUP_CONNECTIONS; ++i) {
        if (g->close[i].type == GROUPCHAT_CLOSE_NONE)
            continue;

        g->close[i].type = GROUPCHAT_CLOSE_NONE;
        kill_friend_connection(g_c->fr_c, g->close[i].number);
    }

    for (i = 0; i < g->numpeers; ++i) {
        if (g->peer_on_leave)
            g->peer_on_leave(g->object, groupnumber, i, g->group[i].object);
    }

    free(g->group);

    if (g->group_on_delete)
        g->group_on_delete(g->object, groupnumber);

    return wipe_group_chat(g_c, groupnumber);
}