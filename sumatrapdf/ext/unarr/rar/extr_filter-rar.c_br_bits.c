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
typedef  int /*<<< orphan*/  uint32_t ;
struct MemBitReader {int available; int bits; scalar_t__ at_eof; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_fill (struct MemBitReader*,int) ; 

__attribute__((used)) static inline uint32_t br_bits(struct MemBitReader *br, int bits)
{
    if (bits > br->available && (br->at_eof || !br_fill(br, bits)))
        return 0;
    return (uint32_t)((br->bits >> (br->available -= bits)) & (((uint64_t)1 << bits) - 1));
}