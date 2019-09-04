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
typedef  scalar_t__ stb_uint ;
typedef  int /*<<< orphan*/  stb_uchar ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stb__out ; 
 int /*<<< orphan*/  stb__outfile ; 
 int /*<<< orphan*/  stb_out (scalar_t__) ; 
 int /*<<< orphan*/  stb_out2 (scalar_t__) ; 
 int /*<<< orphan*/  stb_out3 (scalar_t__) ; 

__attribute__((used)) static void outliterals(stb_uchar *in, ptrdiff_t numlit)
{
   while (numlit > 65536) {
      outliterals(in,65536);
      in     += 65536;
      numlit -= 65536;
   }

   if      (numlit ==     0)    ;
   else if (numlit <=    32)    stb_out (0x000020 + (stb_uint) numlit-1);
   else if (numlit <=  2048)    stb_out2(0x000800 + (stb_uint) numlit-1);
   else /*  numlit <= 65536) */ stb_out3(0x070000 + (stb_uint) numlit-1);

   if (stb__out) {
      memcpy(stb__out,in,numlit);
      stb__out += numlit;
   } else
      fwrite(in, 1, numlit, stb__outfile);
}