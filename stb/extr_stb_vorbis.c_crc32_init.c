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
typedef  int uint32 ;

/* Variables and functions */
 int CRC32_POLY ; 
 int* crc_table ; 

__attribute__((used)) static void crc32_init(void)
{
   int i,j;
   uint32 s;
   for(i=0; i < 256; i++) {
      for (s=(uint32) i << 24, j=0; j < 8; ++j)
         s = (s << 1) ^ (s >= (1U<<31) ? CRC32_POLY : 0);
      crc_table[i] = s;
   }
}