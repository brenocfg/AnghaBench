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
 unsigned long stb__rand_seed ; 

unsigned long stb_srandLCG(unsigned long seed)
{
   unsigned long previous = stb__rand_seed;
   stb__rand_seed = seed;
   return previous;
}