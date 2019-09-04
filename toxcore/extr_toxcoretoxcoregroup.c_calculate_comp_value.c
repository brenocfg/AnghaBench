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
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t calculate_comp_value(const uint8_t *pk1, const uint8_t *pk2)
{
    uint64_t cmp1 = 0, cmp2 = 0;

    unsigned int i;

    for (i = 0; i < sizeof(uint64_t); ++i) {
        cmp1 = (cmp1 << 8) + (uint64_t)pk1[i];
        cmp2 = (cmp2 << 8) + (uint64_t)pk2[i];
    }

    return (cmp1 - cmp2);
}