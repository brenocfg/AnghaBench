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
 unsigned int ULONG_BITS ; 

__attribute__((used)) static void bitset_put(unsigned long *bits, unsigned i) {
        bits[i / ULONG_BITS] |= (unsigned long) 1 << (i % ULONG_BITS);
}