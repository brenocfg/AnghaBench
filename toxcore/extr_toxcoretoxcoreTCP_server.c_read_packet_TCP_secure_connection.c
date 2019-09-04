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
typedef  int /*<<< orphan*/  sock_t ;

/* Variables and functions */
 int crypto_box_MACBYTES ; 
 int decrypt_data_symmetric (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  increment_nonce (int /*<<< orphan*/ *) ; 
 scalar_t__ read_TCP_length (int /*<<< orphan*/ ) ; 
 int read_TCP_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

int read_packet_TCP_secure_connection(sock_t sock, uint16_t *next_packet_length, const uint8_t *shared_key,
                                      uint8_t *recv_nonce, uint8_t *data, uint16_t max_len)
{
    if (*next_packet_length == 0) {
        uint16_t len = read_TCP_length(sock);

        if (len == (uint16_t)~0)
            return -1;

        if (len == 0)
            return 0;

        *next_packet_length = len;
    }

    if (max_len + crypto_box_MACBYTES < *next_packet_length)
        return -1;

    uint8_t data_encrypted[*next_packet_length];
    int len_packet = read_TCP_packet(sock, data_encrypted, *next_packet_length);

    if (len_packet != *next_packet_length)
        return 0;

    *next_packet_length = 0;

    int len = decrypt_data_symmetric(shared_key, recv_nonce, data_encrypted, len_packet, data);

    if (len + crypto_box_MACBYTES != len_packet)
        return -1;

    increment_nonce(recv_nonce);

    return len;
}