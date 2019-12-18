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
 unsigned char STBDS_ROTATE_LEFT (size_t,int) ; 
 size_t STBDS_ROTATE_RIGHT (size_t,int) ; 

size_t stbds_hash_string(char *str, size_t seed)
{
  size_t hash = seed;
  while (*str)
     hash = STBDS_ROTATE_LEFT(hash, 9) + (unsigned char) *str++;

  // Thomas Wang 64-to-32 bit mix function, hopefully also works in 32 bits
  hash ^= seed;
  hash = (~hash) + (hash << 18);
  hash ^= hash ^ STBDS_ROTATE_RIGHT(hash,31);
  hash = hash * 21;
  hash ^= hash ^ STBDS_ROTATE_RIGHT(hash,11);
  hash += (hash << 6);
  hash ^= STBDS_ROTATE_RIGHT(hash,22);
  return hash+seed;
}