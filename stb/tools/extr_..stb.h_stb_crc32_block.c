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
typedef  int stb_uint ;

/* Variables and functions */

stb_uint stb_crc32_block(stb_uint crc, unsigned char *buffer, stb_uint len)
{
   static stb_uint crc_table[256];
   stb_uint i,j,s;
   crc = ~crc;

   if (crc_table[1] == 0)
      for(i=0; i < 256; i++) {
         for (s=i, j=0; j < 8; ++j)
            s = (s >> 1) ^ (s & 1 ? 0xedb88320 : 0);
         crc_table[i] = s;
      }
   for (i=0; i < len; ++i)
      crc = (crc >> 8) ^ crc_table[buffer[i] ^ (crc & 0xff)];
   return ~crc;
}