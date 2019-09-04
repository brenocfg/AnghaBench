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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_6__ {TYPE_1__* dht; } ;
struct TYPE_5__ {int /*<<< orphan*/  net; } ;
typedef  TYPE_2__ Net_Crypto ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 int COOKIE_REQUEST_PLAIN_LENGTH ; 
 int COOKIE_RESPONSE_LENGTH ; 
 int create_cookie_response (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int crypto_box_BEFORENMBYTES ; 
 int crypto_box_PUBLICKEYBYTES ; 
 scalar_t__ handle_cookie_request (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ sendpacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int udp_handle_cookie_request(void *object, IP_Port source, const uint8_t *packet, uint16_t length)
{
    Net_Crypto *c = object;
    uint8_t request_plain[COOKIE_REQUEST_PLAIN_LENGTH];
    uint8_t shared_key[crypto_box_BEFORENMBYTES];
    uint8_t dht_public_key[crypto_box_PUBLICKEYBYTES];

    if (handle_cookie_request(c, request_plain, shared_key, dht_public_key, packet, length) != 0)
        return 1;

    uint8_t data[COOKIE_RESPONSE_LENGTH];

    if (create_cookie_response(c, data, request_plain, shared_key, dht_public_key) != sizeof(data))
        return 1;

    if ((uint32_t)sendpacket(c->dht->net, source, data, sizeof(data)) != sizeof(data))
        return 1;

    return 0;
}