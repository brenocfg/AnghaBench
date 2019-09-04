#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  const uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  packet ;
typedef  int /*<<< orphan*/  nospam_num ;
struct TYPE_7__ {scalar_t__ status; int /*<<< orphan*/  onion_friendnum; int /*<<< orphan*/  crypt_connection_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  onion_c; int /*<<< orphan*/  net_crypto; } ;
typedef  TYPE_1__ Friend_Connections ;
typedef  TYPE_2__ Friend_Conn ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_PACKET_FRIEND_REQ ; 
 scalar_t__ FRIENDCONN_STATUS_CONNECTED ; 
 int ONION_CLIENT_MAX_DATA_SIZE ; 
 int /*<<< orphan*/  PACKET_ID_FRIEND_REQUESTS ; 
 TYPE_2__* get_conn (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int send_onion_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int write_cryptpacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int send_friend_request_packet(Friend_Connections *fr_c, int friendcon_id, uint32_t nospam_num, const uint8_t *data,
                               uint16_t length)
{
    if (1 + sizeof(nospam_num) + length > ONION_CLIENT_MAX_DATA_SIZE || length == 0)
        return -1;

    Friend_Conn *friend_con = get_conn(fr_c, friendcon_id);

    if (!friend_con)
        return -1;

    uint8_t packet[1 + sizeof(nospam_num) + length];
    memcpy(packet + 1, &nospam_num, sizeof(nospam_num));
    memcpy(packet + 1 + sizeof(nospam_num), data, length);

    if (friend_con->status == FRIENDCONN_STATUS_CONNECTED) {
        packet[0] = PACKET_ID_FRIEND_REQUESTS;
        return write_cryptpacket(fr_c->net_crypto, friend_con->crypt_connection_id, packet, sizeof(packet), 0) != -1;
    } else {
        packet[0] = CRYPTO_PACKET_FRIEND_REQ;
        int num = send_onion_data(fr_c->onion_c, friend_con->onion_friendnum, packet, sizeof(packet));

        if (num <= 0)
            return -1;

        return num;
    }
}