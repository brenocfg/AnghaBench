#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  GROUPCHAT_CLOSE_CONNECTION ; 
 int /*<<< orphan*/  GROUPCHAT_CLOSE_ONLINE ; 
 int /*<<< orphan*/  set_conns_status_groups (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_status(void *object, int friendcon_id, uint8_t status)
{
    Group_Chats *g_c = object;

    if (status) { /* Went online */
        set_conns_status_groups(g_c, friendcon_id, GROUPCHAT_CLOSE_ONLINE);
    } else { /* Went offline */
        set_conns_status_groups(g_c, friendcon_id, GROUPCHAT_CLOSE_CONNECTION);
        //TODO remove timedout connections?
    }

    return 0;
}