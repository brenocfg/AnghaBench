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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  step2 ;
typedef  int /*<<< orphan*/  step1 ;
struct TYPE_3__ {int /*<<< orphan*/  shared_key2; int /*<<< orphan*/  const* public_key2; int /*<<< orphan*/  ip_port2; int /*<<< orphan*/  shared_key3; int /*<<< orphan*/  const* public_key3; int /*<<< orphan*/  ip_port3; } ;
typedef  TYPE_1__ Onion_Path ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 int SEND_BASE ; 
 scalar_t__ SIZE_IPPORT ; 
 scalar_t__ crypto_box_MACBYTES ; 
 scalar_t__ crypto_box_NONCEBYTES ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int encrypt_data_symmetric (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ipport_pack (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  random_nonce (int /*<<< orphan*/  const*) ; 

int create_onion_packet_tcp(uint8_t *packet, uint16_t max_packet_length, const Onion_Path *path, IP_Port dest,
                            const uint8_t *data, uint16_t length)
{
    if (crypto_box_NONCEBYTES + SIZE_IPPORT + SEND_BASE * 2 + length > max_packet_length || length == 0)
        return -1;

    uint8_t step1[SIZE_IPPORT + length];

    ipport_pack(step1, &dest);
    memcpy(step1 + SIZE_IPPORT, data, length);

    uint8_t nonce[crypto_box_NONCEBYTES];
    random_nonce(nonce);

    uint8_t step2[SIZE_IPPORT + SEND_BASE + length];
    ipport_pack(step2, &path->ip_port3);
    memcpy(step2 + SIZE_IPPORT, path->public_key3, crypto_box_PUBLICKEYBYTES);

    int len = encrypt_data_symmetric(path->shared_key3, nonce, step1, sizeof(step1),
                                     step2 + SIZE_IPPORT + crypto_box_PUBLICKEYBYTES);

    if (len != SIZE_IPPORT + length + crypto_box_MACBYTES)
        return -1;

    ipport_pack(packet + crypto_box_NONCEBYTES, &path->ip_port2);
    memcpy(packet + crypto_box_NONCEBYTES + SIZE_IPPORT, path->public_key2, crypto_box_PUBLICKEYBYTES);
    len = encrypt_data_symmetric(path->shared_key2, nonce, step2, sizeof(step2),
                                 packet + crypto_box_NONCEBYTES + SIZE_IPPORT + crypto_box_PUBLICKEYBYTES);

    if (len != SIZE_IPPORT + SEND_BASE + length + crypto_box_MACBYTES)
        return -1;

    memcpy(packet, nonce, crypto_box_NONCEBYTES);

    return crypto_box_NONCEBYTES + SIZE_IPPORT + crypto_box_PUBLICKEYBYTES + len;
}