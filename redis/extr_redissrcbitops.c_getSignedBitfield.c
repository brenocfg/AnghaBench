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
typedef  int int64_t ;

/* Variables and functions */
 int getUnsignedBitfield (unsigned char*,int,int) ; 

int64_t getSignedBitfield(unsigned char *p, uint64_t offset, uint64_t bits) {
    int64_t value;
    union {uint64_t u; int64_t i;} conv;

    /* Converting from unsigned to signed is undefined when the value does
     * not fit, however here we assume two's complement and the original value
     * was obtained from signed -> unsigned conversion, so we'll find the
     * most significant bit set if the original value was negative.
     *
     * Note that two's complement is mandatory for exact-width types
     * according to the C99 standard. */
    conv.u = getUnsignedBitfield(p,offset,bits);
    value = conv.i;

    /* If the top significant bit is 1, propagate it to all the
     * higher bits for two's complement representation of signed
     * integers. */
    if (value & ((uint64_t)1 << (bits-1)))
        value |= ((uint64_t)-1) << bits;
    return value;
}