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
 scalar_t__* sqlite3UpperToLower ; 

__attribute__((used)) static unsigned int strHash(const char *z){
  unsigned int h = 0;
  unsigned char c;
  while( (c = (unsigned char)*z++)!=0 ){     /*OPTIMIZATION-IF-TRUE*/
    /* Knuth multiplicative hashing.  (Sorting & Searching, p. 510).
    ** 0x9e3779b1 is 2654435761 which is the closest prime number to
    ** (2**32)*golden_ratio, where golden_ratio = (sqrt(5) - 1)/2. */
    h += sqlite3UpperToLower[c];
    h *= 0x9e3779b1;
  }
  return h;
}