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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ MAX_CRYPTO_REQUEST_SIZE ; 
 int /*<<< orphan*/  NET_PACKET_CRYPTO ; 
 scalar_t__ crypto_box_MACBYTES ; 
 scalar_t__ crypto_box_NONCEBYTES ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int encrypt_data (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  new_nonce (int /*<<< orphan*/ *) ; 

int create_request(const uint8_t *send_public_key, const uint8_t *send_secret_key, uint8_t *packet,
                   const uint8_t *recv_public_key, const uint8_t *data, uint32_t length, uint8_t request_id)
{
    if (!send_public_key || !packet || !recv_public_key || !data)
        return -1;

    if (MAX_CRYPTO_REQUEST_SIZE < length + 1 + crypto_box_PUBLICKEYBYTES * 2 + crypto_box_NONCEBYTES + 1 +
            crypto_box_MACBYTES)
        return -1;

    uint8_t *nonce = packet + 1 + crypto_box_PUBLICKEYBYTES * 2;
    new_nonce(nonce);
    uint8_t temp[MAX_CRYPTO_REQUEST_SIZE]; // FIXME sodium_memzero before exit function
    memcpy(temp + 1, data, length);
    temp[0] = request_id;
    int len = encrypt_data(recv_public_key, send_secret_key, nonce, temp, length + 1,
                           1 + crypto_box_PUBLICKEYBYTES * 2 + crypto_box_NONCEBYTES + packet);

    if (len == -1)
        return -1;

    packet[0] = NET_PACKET_CRYPTO;
    memcpy(packet + 1, recv_public_key, crypto_box_PUBLICKEYBYTES);
    memcpy(packet + 1 + crypto_box_PUBLICKEYBYTES, send_public_key, crypto_box_PUBLICKEYBYTES);

    return len + 1 + crypto_box_PUBLICKEYBYTES * 2 + crypto_box_NONCEBYTES;
}