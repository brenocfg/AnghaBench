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
typedef  int uint32_t ;
typedef  size_t ULONG ;

/* Variables and functions */
 int* crctable ; 

__attribute__((used)) static uint32_t calc_crc32c(uint32_t seed, uint8_t* msg, ULONG msglen) {
    uint32_t rem;
    ULONG i;

    rem = seed;

    for (i = 0; i < msglen; i++) {
        rem = crctable[(rem ^ msg[i]) & 0xff] ^ (rem >> 8);
    }

    return rem;
}