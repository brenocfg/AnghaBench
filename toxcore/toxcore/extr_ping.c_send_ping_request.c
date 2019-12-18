#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  pk ;
typedef  int /*<<< orphan*/  ping_plain ;
typedef  int /*<<< orphan*/  ping_id ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_5__ {int /*<<< orphan*/  net; int /*<<< orphan*/  const* self_public_key; } ;
struct TYPE_4__ {TYPE_3__* dht; int /*<<< orphan*/  ping_array; } ;
typedef  TYPE_1__ PING ;
typedef  scalar_t__ IP_Port ;

/* Variables and functions */
 int DHT_PING_SIZE ; 
 int /*<<< orphan*/  DHT_get_shared_key_sent (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  NET_PACKET_PING_REQUEST ; 
 int PING_DATA_SIZE ; 
 int PING_PLAIN_SIZE ; 
 int crypto_box_BEFORENMBYTES ; 
 int crypto_box_MACBYTES ; 
 int crypto_box_NONCEBYTES ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int encrypt_data_symmetric (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  id_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ id_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  new_nonce (int /*<<< orphan*/ *) ; 
 scalar_t__ ping_array_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int sendpacket (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 

int send_ping_request(PING *ping, IP_Port ipp, const uint8_t *public_key)
{
    uint8_t   pk[DHT_PING_SIZE];
    int       rc;
    uint64_t  ping_id;

    if (id_equal(public_key, ping->dht->self_public_key))
        return 1;

    uint8_t shared_key[crypto_box_BEFORENMBYTES];

    // generate key to encrypt ping_id with recipient privkey
    DHT_get_shared_key_sent(ping->dht, shared_key, public_key);
    // Generate random ping_id.
    uint8_t data[PING_DATA_SIZE];
    id_copy(data, public_key);
    memcpy(data + crypto_box_PUBLICKEYBYTES, &ipp, sizeof(IP_Port));
    ping_id = ping_array_add(&ping->ping_array, data, sizeof(data));

    if (ping_id == 0)
        return 1;

    uint8_t ping_plain[PING_PLAIN_SIZE];
    ping_plain[0] = NET_PACKET_PING_REQUEST;
    memcpy(ping_plain + 1, &ping_id, sizeof(ping_id));

    pk[0] = NET_PACKET_PING_REQUEST;
    id_copy(pk + 1, ping->dht->self_public_key);     // Our pubkey
    new_nonce(pk + 1 + crypto_box_PUBLICKEYBYTES); // Generate new nonce


    rc = encrypt_data_symmetric(shared_key,
                                pk + 1 + crypto_box_PUBLICKEYBYTES,
                                ping_plain, sizeof(ping_plain),
                                pk + 1 + crypto_box_PUBLICKEYBYTES + crypto_box_NONCEBYTES);

    if (rc != PING_PLAIN_SIZE + crypto_box_MACBYTES)
        return 1;

    return sendpacket(ping->dht->net, ipp, pk, sizeof(pk));
}