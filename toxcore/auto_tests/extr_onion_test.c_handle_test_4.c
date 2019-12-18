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
typedef  char uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {TYPE_1__* dht; } ;
struct TYPE_3__ {int /*<<< orphan*/  self_secret_key; } ;
typedef  TYPE_2__ Onion ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 int crypto_box_MACBYTES ; 
 int crypto_box_NONCEBYTES ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int decrypt_data (char const*,int /*<<< orphan*/ ,char const*,char const*,int,char*) ; 
 int handled_test_4 ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 char* nonce ; 

__attribute__((used)) static int handle_test_4(void *object, IP_Port source, const uint8_t *packet, uint16_t length)
{
    Onion *onion = object;

    if (length != (1 + crypto_box_NONCEBYTES + crypto_box_PUBLICKEYBYTES + sizeof("Install gentoo") + crypto_box_MACBYTES))
        return 1;

    uint8_t plain[sizeof("Install gentoo")] = {0};

    if (memcmp(nonce, packet + 1, crypto_box_NONCEBYTES) != 0)
        return 1;

    int len = decrypt_data(packet + 1 + crypto_box_NONCEBYTES, onion->dht->self_secret_key, packet + 1,
                           packet + 1 + crypto_box_NONCEBYTES + crypto_box_PUBLICKEYBYTES, sizeof("Install gentoo") + crypto_box_MACBYTES, plain);

    if (len == -1)
        return 1;

    if (memcmp(plain, "Install gentoo", sizeof("Install gentoo")) != 0)
        return 1;

    handled_test_4 = 1;
    return 0;
}