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

unsigned int stb_hash2(char *str, unsigned int *hash2_ptr)
{
   unsigned int hash1 = 0x3141592c;
   unsigned int hash2 = 0x77f044ed;
   while (*str) {
      hash1 = (hash1 << 7) + (hash1 >> 25) + *str;
      hash2 = (hash2 << 11) + (hash2 >> 21) + *str;
      ++str;
   }
   *hash2_ptr = hash2 + (hash1 >> 16);
   return       hash1 + (hash2 >> 16);
}