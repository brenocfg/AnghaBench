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
typedef  size_t uint32_t ;
struct TYPE_5__ {size_t numpeers; scalar_t__ peer_number; TYPE_1__* group; } ;
struct TYPE_4__ {scalar_t__ peer_number; int /*<<< orphan*/  last_recv; } ;
typedef  TYPE_2__ Group_c ;
typedef  int /*<<< orphan*/  Group_Chats ;

/* Variables and functions */
 int GROUP_PING_INTERVAL ; 
 int /*<<< orphan*/  delpeer (int /*<<< orphan*/ *,int,size_t) ; 
 TYPE_2__* get_group_c (int /*<<< orphan*/ *,int) ; 
 scalar_t__ is_timeout (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int groupchat_clear_timedout(Group_Chats *g_c, int groupnumber)
{
    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return -1;

    uint32_t i;

    for (i = 0; i < g->numpeers; ++i) {
        if (g->peer_number != g->group[i].peer_number && is_timeout(g->group[i].last_recv, GROUP_PING_INTERVAL * 3)) {
            delpeer(g_c, groupnumber, i);
        }

        if (g->group == NULL || i >= g->numpeers)
            break;
    }

    return 0;
}