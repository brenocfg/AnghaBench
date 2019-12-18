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

int stb_size_varlenu(unsigned int v)
{
   if (v < 0x00000080) return 1;
   if (v < 0x00004000) return 2;
   if (v < 0x00200000) return 3;
   if (v < 0x10000000) return 4;
   return 5;
}