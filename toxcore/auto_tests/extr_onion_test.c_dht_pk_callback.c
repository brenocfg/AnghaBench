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
typedef  int uint16_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {TYPE_1__* onion; } ;
struct TYPE_3__ {int /*<<< orphan*/  dht; } ;
typedef  TYPE_2__ Onions ;

/* Variables and functions */
 int DHT_addfriend (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,void*,scalar_t__,int*) ; 
 scalar_t__ NUM_FIRST ; 
 scalar_t__ NUM_LAST ; 
 int /*<<< orphan*/  ck_abort_msg (char*) ; 
 int /*<<< orphan*/  ck_assert_msg (int,char*,...) ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  dht_ip_callback ; 
 int first ; 
 int /*<<< orphan*/  first_dht_pk ; 
 int last ; 
 int /*<<< orphan*/  last_dht_pk ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dht_pk_callback(void *object, int32_t number, const uint8_t *dht_public_key)
{
    if ((NUM_FIRST == number && !first) || (NUM_LAST == number && !last)) {
        Onions *on = object;
        uint16_t count = 0;
        int ret = DHT_addfriend(on->onion->dht, dht_public_key, &dht_ip_callback, object, number, &count);
        ck_assert_msg(ret == 0, "DHT_addfriend() did not return 0");
        ck_assert_msg(count == 1, "Count not 1, count is %u", count);

        if (NUM_FIRST == number && !first) {
            first = 1;

            if (memcmp(dht_public_key, last_dht_pk, crypto_box_PUBLICKEYBYTES) != 0) {
                ck_abort_msg("Error wrong dht key.");
            }

            return;
        }

        if (NUM_LAST == number && !last) {
            last = 1;

            if (memcmp(dht_public_key, first_dht_pk, crypto_box_PUBLICKEYBYTES) != 0) {
                ck_abort_msg("Error wrong dht key.");
            }

            return;
        }

        ck_abort_msg("Error.");
    }
}