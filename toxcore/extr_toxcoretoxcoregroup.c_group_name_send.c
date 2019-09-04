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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  GROUP_MESSAGE_NAME_ID ; 
 scalar_t__ MAX_NAME_LENGTH ; 
 scalar_t__ send_message_group (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static int group_name_send(const Group_Chats *g_c, int groupnumber, const uint8_t *nick, uint16_t nick_len)
{
    if (nick_len > MAX_NAME_LENGTH)
        return -1;

    if (send_message_group(g_c, groupnumber, GROUP_MESSAGE_NAME_ID, nick, nick_len)) {
        return 0;
    } else {
        return -1;
    }
}