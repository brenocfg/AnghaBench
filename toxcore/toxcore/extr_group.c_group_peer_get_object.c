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
struct TYPE_5__ {scalar_t__ numpeers; TYPE_1__* group; } ;
struct TYPE_4__ {void* object; } ;
typedef  TYPE_2__ Group_c ;
typedef  int /*<<< orphan*/  Group_Chats ;

/* Variables and functions */
 TYPE_2__* get_group_c (int /*<<< orphan*/  const*,int) ; 

void *group_peer_get_object(const Group_Chats *g_c, int groupnumber, int peernumber)
{
    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return NULL;

    if ((uint32_t)peernumber >= g->numpeers)
        return NULL;

    return g->group[peernumber].object;
}