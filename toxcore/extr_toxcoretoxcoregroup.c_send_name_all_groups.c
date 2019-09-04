#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned int num_chats; TYPE_1__* m; } ;
struct TYPE_9__ {scalar_t__ status; } ;
struct TYPE_8__ {int /*<<< orphan*/  name_length; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ Group_c ;
typedef  TYPE_3__ Group_Chats ;

/* Variables and functions */
 scalar_t__ GROUPCHAT_STATUS_CONNECTED ; 
 TYPE_2__* get_group_c (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  group_name_send (TYPE_3__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void send_name_all_groups(Group_Chats *g_c)
{
    unsigned int i;

    for (i = 0; i < g_c->num_chats; ++i) {
        Group_c *g = get_group_c(g_c, i);

        if (!g)
            continue;

        if (g->status == GROUPCHAT_STATUS_CONNECTED) {
            group_name_send(g_c, i, g_c->m->name, g_c->m->name_length);
        }
    }
}