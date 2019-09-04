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
 int STB__MT_LEN ; 
 int /*<<< orphan*/ * stb__mt_buffer ; 
 int stb__mt_index ; 
 int /*<<< orphan*/  stb_randLCG () ; 
 unsigned int stb_srandLCG (unsigned int) ; 

void stb_srand(unsigned int seed)
{
   int i;
   unsigned int old = stb_srandLCG(seed);
   for (i = 0; i < STB__MT_LEN; i++)
      stb__mt_buffer[i] = stb_randLCG();
   stb_srandLCG(old);
   stb__mt_index = STB__MT_LEN*sizeof(unsigned int);
}