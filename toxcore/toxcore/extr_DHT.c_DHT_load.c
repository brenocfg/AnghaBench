#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  DHT ;

/* Variables and functions */
 scalar_t__ DHT_STATE_COOKIE_GLOBAL ; 
 int /*<<< orphan*/  DHT_STATE_COOKIE_TYPE ; 
 int /*<<< orphan*/  dht_load_state_callback ; 
 int /*<<< orphan*/  lendian_to_host32 (scalar_t__*,int /*<<< orphan*/  const*) ; 
 int load_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ) ; 

int DHT_load(DHT *dht, const uint8_t *data, uint32_t length)
{
    uint32_t cookie_len = sizeof(uint32_t);

    if (length > cookie_len) {
        uint32_t data32;
        lendian_to_host32(&data32, data);

        if (data32 == DHT_STATE_COOKIE_GLOBAL)
            return load_state(dht_load_state_callback, dht, data + cookie_len,
                              length - cookie_len, DHT_STATE_COOKIE_TYPE);
    }

    return -1;
}