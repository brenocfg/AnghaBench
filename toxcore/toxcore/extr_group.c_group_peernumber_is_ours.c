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
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ status; scalar_t__ numpeers; scalar_t__ peer_number; TYPE_1__* group; } ;
struct TYPE_4__ {scalar_t__ peer_number; } ;
typedef  TYPE_2__ Group_c ;
typedef  int /*<<< orphan*/  Group_Chats ;

/* Variables and functions */
 scalar_t__ GROUPCHAT_STATUS_CONNECTED ; 
 TYPE_2__* get_group_c (int /*<<< orphan*/  const*,int) ; 

unsigned int group_peernumber_is_ours(const Group_Chats *g_c, int groupnumber, int peernumber)
{
    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return 0;

    if (g->status != GROUPCHAT_STATUS_CONNECTED)
        return 0;

    if ((uint32_t)peernumber >= g->numpeers)
        return 0;

    return g->peer_number == g->group[peernumber].peer_number;
}