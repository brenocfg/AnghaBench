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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  dht; } ;
typedef  TYPE_1__ Net_Crypto ;

/* Variables and functions */
 scalar_t__ COOKIE_REQUEST_LENGTH ; 
 int COOKIE_REQUEST_PLAIN_LENGTH ; 
 int /*<<< orphan*/  DHT_get_shared_key_sent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_box_MACBYTES ; 
 int crypto_box_NONCEBYTES ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int decrypt_data_symmetric (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int handle_cookie_request(const Net_Crypto *c, uint8_t *request_plain, uint8_t *shared_key,
                                 uint8_t *dht_public_key, const uint8_t *packet, uint16_t length)
{
    if (length != COOKIE_REQUEST_LENGTH)
        return -1;

    memcpy(dht_public_key, packet + 1, crypto_box_PUBLICKEYBYTES);
    DHT_get_shared_key_sent(c->dht, shared_key, dht_public_key);
    int len = decrypt_data_symmetric(shared_key, packet + 1 + crypto_box_PUBLICKEYBYTES,
                                     packet + 1 + crypto_box_PUBLICKEYBYTES + crypto_box_NONCEBYTES, COOKIE_REQUEST_PLAIN_LENGTH + crypto_box_MACBYTES,
                                     request_plain);

    if (len != COOKIE_REQUEST_PLAIN_LENGTH)
        return -1;

    return 0;
}