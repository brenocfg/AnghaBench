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
typedef  int /*<<< orphan*/  stb_uchar ;

/* Variables and functions */

stb_uint stb_adler32_old(stb_uint adler32, stb_uchar *buffer, stb_uint buflen)
{
   const stb_uint ADLER_MOD = 65521;
   stb_uint s1 = adler32 & 0xffff;
   stb_uint s2 = adler32 >> 16;

   while (buflen-- > 0) { // NOTE: much faster implementations are possible!
      s1 += *buffer++; if (s1 > ADLER_MOD) s1 -= ADLER_MOD;
      s2 += s1       ; if (s2 > ADLER_MOD) s2 -= ADLER_MOD;
   }
   return (s2 << 16) + s1;
}