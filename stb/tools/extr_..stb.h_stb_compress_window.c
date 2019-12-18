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
 int stb__window ; 

void stb_compress_window(int z)
{
   if (z >= 0x1000000) z = 0x1000000; // limit of implementation
   if (z <      0x100) z = 0x100;   // insanely small
   stb__window = z;
}