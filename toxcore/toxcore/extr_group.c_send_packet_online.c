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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  packet ;
struct TYPE_4__ {int /*<<< orphan*/  net_crypto; } ;
typedef  TYPE_1__ Friend_Connections ;

/* Variables and functions */
 int GROUP_IDENTIFIER_LENGTH ; 
 int /*<<< orphan*/  ONLINE_PACKET_DATA_SIZE ; 
 int /*<<< orphan*/  PACKET_ID_ONLINE_PACKET ; 
 int /*<<< orphan*/  friend_connection_crypt_connection_id (TYPE_1__*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int write_cryptpacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_packet_online(Friend_Connections *fr_c, int friendcon_id, uint16_t group_num, uint8_t *identifier)
{
    uint8_t packet[1 + ONLINE_PACKET_DATA_SIZE];
    group_num = htons(group_num);
    packet[0] = PACKET_ID_ONLINE_PACKET;
    memcpy(packet + 1, &group_num, sizeof(uint16_t));
    memcpy(packet + 1 + sizeof(uint16_t), identifier, GROUP_IDENTIFIER_LENGTH);
    return write_cryptpacket(fr_c->net_crypto, friend_connection_crypt_connection_id(fr_c, friendcon_id), packet,
                             sizeof(packet), 0) != -1;
}