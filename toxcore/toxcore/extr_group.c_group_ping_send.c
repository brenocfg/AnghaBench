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
typedef  int /*<<< orphan*/  Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  GROUP_MESSAGE_PING_ID ; 
 scalar_t__ send_message_group (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int group_ping_send(const Group_Chats *g_c, int groupnumber)
{
    if (send_message_group(g_c, groupnumber, GROUP_MESSAGE_PING_ID, 0, 0)) {
        return 0;
    } else {
        return -1;
    }
}