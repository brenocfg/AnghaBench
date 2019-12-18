#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  packet ;
typedef  int int64_t ;
typedef  size_t int32_t ;
struct TYPE_6__ {TYPE_1__* friendlist; int /*<<< orphan*/  fr_c; int /*<<< orphan*/  net_crypto; } ;
struct TYPE_5__ {int /*<<< orphan*/  friendcon_id; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_ID_FILE_DATA ; 
 int /*<<< orphan*/  friend_connection_crypt_connection_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ friend_not_valid (TYPE_2__ const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int write_cryptpacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int64_t send_file_data_packet(const Messenger *m, int32_t friendnumber, uint8_t filenumber, const uint8_t *data,
                                     uint16_t length)
{
    if (friend_not_valid(m, friendnumber))
        return -1;

    uint8_t packet[2 + length];
    packet[0] = PACKET_ID_FILE_DATA;
    packet[1] = filenumber;

    if (length) {
        memcpy(packet + 2, data, length);
    }

    return write_cryptpacket(m->net_crypto, friend_connection_crypt_connection_id(m->fr_c,
                             m->friendlist[friendnumber].friendcon_id), packet, sizeof(packet), 1);
}