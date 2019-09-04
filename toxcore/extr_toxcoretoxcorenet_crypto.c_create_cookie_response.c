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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  plain ;
struct TYPE_3__ {int /*<<< orphan*/  secret_symmetric_key; } ;
typedef  TYPE_1__ Net_Crypto ;

/* Variables and functions */
 int COOKIE_DATA_LENGTH ; 
 int COOKIE_LENGTH ; 
 int COOKIE_RESPONSE_LENGTH ; 
 int /*<<< orphan*/  NET_PACKET_COOKIE_RESPONSE ; 
 scalar_t__ create_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int crypto_box_NONCEBYTES ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int encrypt_data_symmetric (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  new_nonce (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_cookie_response(const Net_Crypto *c, uint8_t *packet, const uint8_t *request_plain,
                                  const uint8_t *shared_key, const uint8_t *dht_public_key)
{
    uint8_t cookie_plain[COOKIE_DATA_LENGTH];
    memcpy(cookie_plain, request_plain, crypto_box_PUBLICKEYBYTES);
    memcpy(cookie_plain + crypto_box_PUBLICKEYBYTES, dht_public_key, crypto_box_PUBLICKEYBYTES);
    uint8_t plain[COOKIE_LENGTH + sizeof(uint64_t)];

    if (create_cookie(plain, cookie_plain, c->secret_symmetric_key) != 0)
        return -1;

    memcpy(plain + COOKIE_LENGTH, request_plain + COOKIE_DATA_LENGTH, sizeof(uint64_t));
    packet[0] = NET_PACKET_COOKIE_RESPONSE;
    new_nonce(packet + 1);
    int len = encrypt_data_symmetric(shared_key, packet + 1, plain, sizeof(plain), packet + 1 + crypto_box_NONCEBYTES);

    if (len != COOKIE_RESPONSE_LENGTH - (1 + crypto_box_NONCEBYTES))
        return -1;

    return COOKIE_RESPONSE_LENGTH;
}