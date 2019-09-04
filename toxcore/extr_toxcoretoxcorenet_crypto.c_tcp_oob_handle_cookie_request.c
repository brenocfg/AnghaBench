#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_5__ {int /*<<< orphan*/  tcp_c; } ;
typedef  TYPE_1__ Net_Crypto ;

/* Variables and functions */
 int COOKIE_REQUEST_PLAIN_LENGTH ; 
 int COOKIE_RESPONSE_LENGTH ; 
 int create_cookie_response (TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int crypto_box_BEFORENMBYTES ; 
 int crypto_box_PUBLICKEYBYTES ; 
 scalar_t__ handle_cookie_request (TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ public_key_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int tcp_send_oob_packet (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tcp_oob_handle_cookie_request(const Net_Crypto *c, unsigned int tcp_connections_number,
        const uint8_t *dht_public_key, const uint8_t *packet, uint16_t length)
{
    uint8_t request_plain[COOKIE_REQUEST_PLAIN_LENGTH];
    uint8_t shared_key[crypto_box_BEFORENMBYTES];
    uint8_t dht_public_key_temp[crypto_box_PUBLICKEYBYTES];

    if (handle_cookie_request(c, request_plain, shared_key, dht_public_key_temp, packet, length) != 0)
        return -1;

    if (public_key_cmp(dht_public_key, dht_public_key_temp) != 0)
        return -1;

    uint8_t data[COOKIE_RESPONSE_LENGTH];

    if (create_cookie_response(c, data, request_plain, shared_key, dht_public_key) != sizeof(data))
        return -1;

    int ret = tcp_send_oob_packet(c->tcp_c, tcp_connections_number, dht_public_key, data, sizeof(data));
    return ret;
}