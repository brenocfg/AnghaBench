#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numpeers; } ;
typedef  TYPE_1__ Group_c ;
typedef  int /*<<< orphan*/  Group_Chats ;

/* Variables and functions */
 TYPE_1__* get_group_c (int /*<<< orphan*/  const*,int) ; 

int group_number_peers(const Group_Chats *g_c, int groupnumber)
{
    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return -1;

    return g->numpeers;
}