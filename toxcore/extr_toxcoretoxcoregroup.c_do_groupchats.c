#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned int num_chats; } ;
struct TYPE_9__ {scalar_t__ status; } ;
typedef  TYPE_1__ Group_c ;
typedef  TYPE_2__ Group_Chats ;

/* Variables and functions */
 scalar_t__ GROUPCHAT_STATUS_CONNECTED ; 
 int /*<<< orphan*/  connect_to_closest (TYPE_2__*,unsigned int) ; 
 TYPE_1__* get_group_c (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  groupchat_clear_timedout (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  ping_groupchat (TYPE_2__*,unsigned int) ; 

void do_groupchats(Group_Chats *g_c)
{
    unsigned int i;

    for (i = 0; i < g_c->num_chats; ++i) {
        Group_c *g = get_group_c(g_c, i);

        if (!g)
            continue;

        if (g->status == GROUPCHAT_STATUS_CONNECTED) {
            connect_to_closest(g_c, i);
            ping_groupchat(g_c, i);
            groupchat_clear_timedout(g_c, i);
        }
    }

    //TODO
}