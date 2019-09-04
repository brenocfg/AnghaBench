#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * chats; } ;
typedef  int /*<<< orphan*/  Group_c ;
typedef  TYPE_1__ Group_Chats ;

/* Variables and functions */
 scalar_t__ groupnumber_not_valid (TYPE_1__ const*,int) ; 

__attribute__((used)) static Group_c *get_group_c(const Group_Chats *g_c, int groupnumber)
{
    if (groupnumber_not_valid(g_c, groupnumber))
        return 0;

    return &g_c->chats[groupnumber];
}