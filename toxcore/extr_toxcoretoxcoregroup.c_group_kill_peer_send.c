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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  packet ;
typedef  int /*<<< orphan*/  Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  GROUP_MESSAGE_KILL_PEER_ID ; 
 int GROUP_MESSAGE_KILL_PEER_LENGTH ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ send_message_group (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int group_kill_peer_send(const Group_Chats *g_c, int groupnumber, uint16_t peer_num)
{
    uint8_t packet[GROUP_MESSAGE_KILL_PEER_LENGTH];

    peer_num = htons(peer_num);
    memcpy(packet, &peer_num, sizeof(uint16_t));

    if (send_message_group(g_c, groupnumber, GROUP_MESSAGE_KILL_PEER_ID, packet, sizeof(packet))) {
        return 0;
    } else {
        return -1;
    }
}