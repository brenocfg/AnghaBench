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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  packet ;
struct TYPE_3__ {int /*<<< orphan*/  lossy_message_number; int /*<<< orphan*/  peer_number; } ;
typedef  TYPE_1__ Group_c ;
typedef  int /*<<< orphan*/  Group_Chats ;

/* Variables and functions */
 TYPE_1__* get_group_c (int /*<<< orphan*/  const*,int) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 scalar_t__ send_lossy_all_close (int /*<<< orphan*/  const*,int,int*,int,int) ; 

int send_group_lossy_packet(const Group_Chats *g_c, int groupnumber, const uint8_t *data, uint16_t length)
{
    //TODO: length check here?
    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return -1;

    uint8_t packet[sizeof(uint16_t) * 2 + length];
    uint16_t peer_number = htons(g->peer_number);
    memcpy(packet, &peer_number, sizeof(uint16_t));
    uint16_t message_num = htons(g->lossy_message_number);
    memcpy(packet + sizeof(uint16_t), &message_num, sizeof(uint16_t));
    memcpy(packet + sizeof(uint16_t) * 2, data, length);

    if (send_lossy_all_close(g_c, groupnumber, packet, sizeof(packet), -1) == 0) {
        return -1;
    }

    ++g->lossy_message_number;
    return 0;
}