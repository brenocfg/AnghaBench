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
typedef  int uint_fast16_t ;
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int crypto_box_NONCEBYTES ; 

void increment_nonce(uint8_t *nonce)
{
    /* FIXME use increment_nonce_number(nonce, 1) or sodium_increment (change to little endian)
     * NOTE don't use breaks inside this loop
     * In particular, make sure, as far as possible,
     * that loop bounds and their potential underflow or overflow
     * are independent of user-controlled input (you may have heard of the Heartbleed bug).
     */
    uint32_t i = crypto_box_NONCEBYTES;
    uint_fast16_t carry = 1U;

    for (; i != 0; --i) {
        carry += (uint_fast16_t) nonce[i - 1];
        nonce[i - 1] = (uint8_t) carry;
        carry >>= 8;
    }
}