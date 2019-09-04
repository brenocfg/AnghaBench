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
 unsigned int stb__hashsize ; 

void stb_compress_hashsize(unsigned int y)
{
   unsigned int z = 1024;
   while (z < y) z <<= 1;
   stb__hashsize = z >> 2;   // pass in bytes, store #pointers
}