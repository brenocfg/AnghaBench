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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  packet ;
struct TYPE_3__ {int /*<<< orphan*/  fr_c; } ;
typedef  TYPE_1__ Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_ID_DIRECT_GROUPCHAT ; 
 int /*<<< orphan*/  PEER_KILL_ID ; 
 unsigned int send_packet_group_peer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned int send_peer_kill(Group_Chats *g_c, int friendcon_id, uint16_t group_num)
{
    uint8_t packet[1];
    packet[0] = PEER_KILL_ID;
    return send_packet_group_peer(g_c->fr_c, friendcon_id, PACKET_ID_DIRECT_GROUPCHAT, group_num, packet, sizeof(packet));
}