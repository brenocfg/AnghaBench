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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  size_t int32_t ;
struct TYPE_6__ {TYPE_1__* friendlist; int /*<<< orphan*/  fr_c; int /*<<< orphan*/  net_crypto; } ;
struct TYPE_5__ {scalar_t__ status; int /*<<< orphan*/  friendcon_id; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 scalar_t__ FRIEND_ONLINE ; 
 scalar_t__ MAX_CRYPTO_DATA_SIZE ; 
 scalar_t__ const PACKET_ID_LOSSLESS_RANGE_SIZE ; 
 scalar_t__ const PACKET_ID_LOSSLESS_RANGE_START ; 
 int /*<<< orphan*/  friend_connection_crypt_connection_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ friend_not_valid (TYPE_2__ const*,size_t) ; 
 int write_cryptpacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__,int) ; 

int send_custom_lossless_packet(const Messenger *m, int32_t friendnumber, const uint8_t *data, uint32_t length)
{
    if (friend_not_valid(m, friendnumber))
        return -1;

    if (length == 0 || length > MAX_CRYPTO_DATA_SIZE)
        return -2;

    if (data[0] < PACKET_ID_LOSSLESS_RANGE_START)
        return -3;

    if (data[0] >= (PACKET_ID_LOSSLESS_RANGE_START + PACKET_ID_LOSSLESS_RANGE_SIZE))
        return -3;

    if (m->friendlist[friendnumber].status != FRIEND_ONLINE)
        return -4;

    if (write_cryptpacket(m->net_crypto, friend_connection_crypt_connection_id(m->fr_c,
                          m->friendlist[friendnumber].friendcon_id), data, length, 1) == -1) {
        return -5;
    } else {
        return 0;
    }
}