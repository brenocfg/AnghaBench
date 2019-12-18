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
typedef  int /*<<< orphan*/  plain ;
struct TYPE_3__ {int /*<<< orphan*/  self_secret_key; int /*<<< orphan*/  secret_symmetric_key; } ;
typedef  TYPE_1__ Net_Crypto ;

/* Variables and functions */
 int COOKIE_DATA_LENGTH ; 
 int COOKIE_LENGTH ; 
 int HANDSHAKE_PACKET_LENGTH ; 
 int /*<<< orphan*/  NET_PACKET_CRYPTO_HS ; 
 scalar_t__ create_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int crypto_box_NONCEBYTES ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  crypto_hash_sha512 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int crypto_hash_sha512_BYTES ; 
 int encrypt_data (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  new_nonce (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_crypto_handshake(const Net_Crypto *c, uint8_t *packet, const uint8_t *cookie, const uint8_t *nonce,
                                   const uint8_t *session_pk, const uint8_t *peer_real_pk, const uint8_t *peer_dht_pubkey)
{
    uint8_t plain[crypto_box_NONCEBYTES + crypto_box_PUBLICKEYBYTES + crypto_hash_sha512_BYTES + COOKIE_LENGTH];
    memcpy(plain, nonce, crypto_box_NONCEBYTES);
    memcpy(plain + crypto_box_NONCEBYTES, session_pk, crypto_box_PUBLICKEYBYTES);
    crypto_hash_sha512(plain + crypto_box_NONCEBYTES + crypto_box_PUBLICKEYBYTES, cookie, COOKIE_LENGTH);
    uint8_t cookie_plain[COOKIE_DATA_LENGTH];
    memcpy(cookie_plain, peer_real_pk, crypto_box_PUBLICKEYBYTES);
    memcpy(cookie_plain + crypto_box_PUBLICKEYBYTES, peer_dht_pubkey, crypto_box_PUBLICKEYBYTES);

    if (create_cookie(plain + crypto_box_NONCEBYTES + crypto_box_PUBLICKEYBYTES + crypto_hash_sha512_BYTES, cookie_plain,
                      c->secret_symmetric_key) != 0)
        return -1;

    new_nonce(packet + 1 + COOKIE_LENGTH);
    int len = encrypt_data(peer_real_pk, c->self_secret_key, packet + 1 + COOKIE_LENGTH, plain, sizeof(plain),
                           packet + 1 + COOKIE_LENGTH + crypto_box_NONCEBYTES);

    if (len != HANDSHAKE_PACKET_LENGTH - (1 + COOKIE_LENGTH + crypto_box_NONCEBYTES))
        return -1;

    packet[0] = NET_PACKET_CRYPTO_HS;
    memcpy(packet + 1, cookie, COOKIE_LENGTH);

    return HANDSHAKE_PACKET_LENGTH;
}