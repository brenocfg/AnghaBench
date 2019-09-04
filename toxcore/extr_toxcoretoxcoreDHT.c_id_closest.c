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
typedef  int uint8_t ;

/* Variables and functions */
 size_t crypto_box_PUBLICKEYBYTES ; 

int id_closest(const uint8_t *pk, const uint8_t *pk1, const uint8_t *pk2)
{
    size_t   i;
    uint8_t distance1, distance2;

    for (i = 0; i < crypto_box_PUBLICKEYBYTES; ++i) {

        distance1 = pk[i] ^ pk1[i];
        distance2 = pk[i] ^ pk2[i];

        if (distance1 < distance2)
            return 1;

        if (distance1 > distance2)
            return 2;
    }

    return 0;
}