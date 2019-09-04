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
 int euc2sjisibm_g3upper (unsigned char*,unsigned char const,unsigned char const) ; 
 int euc2sjisibm_jisx0212 (unsigned char*,unsigned char const,unsigned char const) ; 

__attribute__((used)) static inline int euc2sjisibm(unsigned char *sjis, const unsigned char euc_hi,
                              const unsigned char euc_lo)
{
    int n;

#if 0
    if ((euc_hi == 0xA2) && (euc_lo == 0xCC)) {
        sjis[0] = 0xFA;
        sjis[1] = 0x54;
        return 2;
    } else if ((euc_hi == 0xA2) && (euc_lo == 0xE8)) {
        sjis[0] = 0xFA;
        sjis[1] = 0x5B;
        return 2;
    }
#endif
    if ((n = euc2sjisibm_g3upper(sjis, euc_hi, euc_lo))) {
        return n;
    } else if ((n = euc2sjisibm_jisx0212(sjis, euc_hi, euc_lo))) {
        return n;
    }

    return 0;
}