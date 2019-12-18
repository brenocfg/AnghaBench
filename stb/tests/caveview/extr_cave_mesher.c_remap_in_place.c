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
 int* remap ; 
 int** remap_data ; 

void remap_in_place(int bt, int rm)
{
   int i;
   remap[bt] = rm;
   for (i=0; i < 16; ++i)
      remap_data[rm][i] = bt;
}