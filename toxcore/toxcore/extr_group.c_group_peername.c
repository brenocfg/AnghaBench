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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ numpeers; TYPE_1__* group; } ;
struct TYPE_4__ {int nick_len; char* nick; } ;
typedef  TYPE_2__ Group_c ;
typedef  int /*<<< orphan*/  Group_Chats ;

/* Variables and functions */
 TYPE_2__* get_group_c (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

int group_peername(const Group_Chats *g_c, int groupnumber, int peernumber, uint8_t *name)
{
    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return -1;

    if ((uint32_t)peernumber >= g->numpeers)
        return -1;

    if (g->group[peernumber].nick_len == 0) {
        memcpy(name, "Tox User", 8);
        return 8;
    }

    memcpy(name, g->group[peernumber].nick, g->group[peernumber].nick_len);
    return g->group[peernumber].nick_len;
}