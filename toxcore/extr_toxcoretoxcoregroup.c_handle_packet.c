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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  Group_c ;
typedef  int /*<<< orphan*/  Group_Chats ;

/* Variables and functions */
#define  PACKET_ID_DIRECT_GROUPCHAT 129 
#define  PACKET_ID_MESSAGE_GROUPCHAT 128 
 int PACKET_ID_ONLINE_PACKET ; 
 int friend_in_close (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * get_group_c (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  handle_direct_packet (int /*<<< orphan*/ *,int,int*,int,int) ; 
 int /*<<< orphan*/  handle_message_packet_group (int /*<<< orphan*/ *,int,int*,int,int) ; 
 int handle_packet_online (int /*<<< orphan*/ *,int,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int ntohs (int) ; 

__attribute__((used)) static int handle_packet(void *object, int friendcon_id, uint8_t *data, uint16_t length)
{
    Group_Chats *g_c = object;

    if (length < 1 + sizeof(uint16_t) + 1)
        return -1;

    if (data[0] == PACKET_ID_ONLINE_PACKET) {
        return handle_packet_online(g_c, friendcon_id, data + 1, length - 1);
    }

    if (data[0] != PACKET_ID_DIRECT_GROUPCHAT && data[0] != PACKET_ID_MESSAGE_GROUPCHAT)
        return -1;

    uint16_t groupnumber;
    memcpy(&groupnumber, data + 1, sizeof(uint16_t));
    groupnumber = ntohs(groupnumber);
    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return -1;

    int index = friend_in_close(g, friendcon_id);

    if (index == -1)
        return -1;

    switch (data[0]) {
        case PACKET_ID_DIRECT_GROUPCHAT: {
            handle_direct_packet(g_c, groupnumber, data + 1 + sizeof(uint16_t), length - (1 + sizeof(uint16_t)), index);
            break;
        }

        case PACKET_ID_MESSAGE_GROUPCHAT: {
            handle_message_packet_group(g_c, groupnumber, data + 1 + sizeof(uint16_t), length - (1 + sizeof(uint16_t)), index);
            break;
        }

        default: {
            return 0;
        }
    }

    return 0;
}