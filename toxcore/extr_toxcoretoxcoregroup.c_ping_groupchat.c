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
struct TYPE_3__ {int /*<<< orphan*/  last_sent_ping; } ;
typedef  TYPE_1__ Group_c ;
typedef  int /*<<< orphan*/  Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  GROUP_PING_INTERVAL ; 
 TYPE_1__* get_group_c (int /*<<< orphan*/ *,int) ; 
 int group_ping_send (int /*<<< orphan*/ *,int) ; 
 scalar_t__ is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unix_time () ; 

__attribute__((used)) static int ping_groupchat(Group_Chats *g_c, int groupnumber)
{
    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return -1;

    if (is_timeout(g->last_sent_ping, GROUP_PING_INTERVAL)) {
        if (group_ping_send(g_c, groupnumber) != -1) /* Ping */
            g->last_sent_ping = unix_time();
    }

    return 0;
}