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
typedef  int uint16_t ;
struct sec_TCP_con {int /*<<< orphan*/  sock; int /*<<< orphan*/  sent_nonce; int /*<<< orphan*/  shared_key; } ;
typedef  int /*<<< orphan*/  packet ;

/* Variables and functions */
 int /*<<< orphan*/  ck_assert_msg (int,char*) ; 
 int crypto_box_MACBYTES ; 
 int encrypt_data_symmetric (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int htons (int) ; 
 int /*<<< orphan*/  increment_nonce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int write_packet_TCP_secure_connection(struct sec_TCP_con *con, uint8_t *data, uint16_t length)
{
    uint8_t packet[sizeof(uint16_t) + length + crypto_box_MACBYTES];

    uint16_t c_length = htons(length + crypto_box_MACBYTES);
    memcpy(packet, &c_length, sizeof(uint16_t));
    int len = encrypt_data_symmetric(con->shared_key, con->sent_nonce, data, length, packet + sizeof(uint16_t));

    if ((unsigned int)len != (sizeof(packet) - sizeof(uint16_t)))
        return -1;

    increment_nonce(con->sent_nonce);

    ck_assert_msg(send(con->sock, packet, sizeof(packet), 0) == sizeof(packet), "send failed");
    return 0;
}