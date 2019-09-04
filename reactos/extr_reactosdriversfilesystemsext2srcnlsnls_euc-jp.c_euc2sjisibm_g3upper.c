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

/* Variables and functions */
 int MAP_ELEMENT_OF (unsigned char**) ; 
 unsigned char** euc2sjisibm_g3upper_map ; 

__attribute__((used)) static inline int euc2sjisibm_g3upper(unsigned char *sjis, const unsigned char euc_hi,
                                      const unsigned char euc_lo)
{
    int index;

    if (euc_hi == 0xF3)
        index = ((euc_hi << 8) | euc_lo) - 0xF3F3;
    else
        index = ((euc_hi << 8) | euc_lo) - 0xF4A1 + 12;

    if ((index < 0) || (index >= MAP_ELEMENT_OF(euc2sjisibm_g3upper_map)))
        return 0;

    sjis[0] = euc2sjisibm_g3upper_map[index][0];
    sjis[1] = euc2sjisibm_g3upper_map[index][1];

    return 3;
}