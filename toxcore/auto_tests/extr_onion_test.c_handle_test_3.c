#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {TYPE_1__* dht; } ;
struct TYPE_3__ {int /*<<< orphan*/  self_secret_key; } ;
typedef  TYPE_2__ Onion ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 scalar_t__ ONION_ANNOUNCE_SENDBACK_DATA_LENGTH ; 
 scalar_t__ crypto_box_MACBYTES ; 
 scalar_t__ crypto_box_NONCEBYTES ; 
 scalar_t__ crypto_hash_sha256_BYTES ; 
 int decrypt_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int handled_test_3 ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sb_data ; 
 int /*<<< orphan*/  test_3_ping_id ; 
 int /*<<< orphan*/  test_3_pub_key ; 

__attribute__((used)) static int handle_test_3(void *object, IP_Port source, const uint8_t *packet, uint16_t length)
{
    Onion *onion = object;

    if (length != (1 + crypto_box_NONCEBYTES + ONION_ANNOUNCE_SENDBACK_DATA_LENGTH + 1 + crypto_hash_sha256_BYTES +
                   crypto_box_MACBYTES))
        return 1;

    uint8_t plain[1 + crypto_hash_sha256_BYTES];
    //print_client_id(packet, length);
    int len = decrypt_data(test_3_pub_key, onion->dht->self_secret_key, packet + 1 + ONION_ANNOUNCE_SENDBACK_DATA_LENGTH,
                           packet + 1 + ONION_ANNOUNCE_SENDBACK_DATA_LENGTH + crypto_box_NONCEBYTES,
                           1 + crypto_hash_sha256_BYTES + crypto_box_MACBYTES, plain);

    if (len == -1)
        return 1;


    if (memcmp(packet + 1, sb_data, ONION_ANNOUNCE_SENDBACK_DATA_LENGTH) != 0)
        return 1;

    memcpy(test_3_ping_id, plain + 1, crypto_hash_sha256_BYTES);
    //print_client_id(test_3_ping_id, sizeof(test_3_ping_id));
    handled_test_3 = 1;
    return 0;
}