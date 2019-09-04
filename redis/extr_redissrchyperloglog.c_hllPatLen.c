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
typedef  int uint64_t ;

/* Variables and functions */
 int HLL_P ; 
 int HLL_P_MASK ; 
 int HLL_Q ; 
 int MurmurHash64A (unsigned char*,size_t,int) ; 

int hllPatLen(unsigned char *ele, size_t elesize, long *regp) {
    uint64_t hash, bit, index;
    int count;

    /* Count the number of zeroes starting from bit HLL_REGISTERS
     * (that is a power of two corresponding to the first bit we don't use
     * as index). The max run can be 64-P+1 = Q+1 bits.
     *
     * Note that the final "1" ending the sequence of zeroes must be
     * included in the count, so if we find "001" the count is 3, and
     * the smallest count possible is no zeroes at all, just a 1 bit
     * at the first position, that is a count of 1.
     *
     * This may sound like inefficient, but actually in the average case
     * there are high probabilities to find a 1 after a few iterations. */
    hash = MurmurHash64A(ele,elesize,0xadc83b19ULL);
    index = hash & HLL_P_MASK; /* Register index. */
    hash >>= HLL_P; /* Remove bits used to address the register. */
    hash |= ((uint64_t)1<<HLL_Q); /* Make sure the loop terminates
                                     and count will be <= Q+1. */
    bit = 1;
    count = 1; /* Initialized to 1 since we count the "00000...1" pattern. */
    while((hash & bit) == 0) {
        count++;
        bit <<= 1;
    }
    *regp = (int) index;
    return count;
}