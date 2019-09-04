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
struct TYPE_5__ {TYPE_1__* close; } ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ number; } ;
typedef  TYPE_2__ Group_c ;

/* Variables and functions */
 scalar_t__ GROUPCHAT_CLOSE_NONE ; 
 unsigned int MAX_GROUP_CONNECTIONS ; 

__attribute__((used)) static int friend_in_close(Group_c *g, int friendcon_id)
{
    unsigned int i;

    for (i = 0; i < MAX_GROUP_CONNECTIONS; ++i) {
        if (g->close[i].type == GROUPCHAT_CLOSE_NONE)
            continue;

        if (g->close[i].number != (uint32_t)friendcon_id)
            continue;

        return i;
    }

    return -1;
}