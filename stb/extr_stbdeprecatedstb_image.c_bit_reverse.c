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
 int /*<<< orphan*/  assert (int) ; 
 int bitreverse16 (int) ; 

__attribute__((used)) static int bit_reverse(int v, int bits)
{
   assert(bits <= 16);
   // to bit reverse n bits, reverse 16 and shift
   // e.g. 11 bits, bit reverse and shift away 5
   return bitreverse16(v) >> (16-bits);
}