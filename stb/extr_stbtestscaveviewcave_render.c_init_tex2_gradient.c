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
 int** tex2_data ; 

void init_tex2_gradient(void)
{
   int i;
   for (i=0; i < 16; ++i) {
      tex2_data[i+ 0][0] = 64 + 12*i;
      tex2_data[i+ 0][1] = 32;
      tex2_data[i+ 0][2] = 64;

      tex2_data[i+16][0] = 255;
      tex2_data[i+16][1] = 32 + 8*i;
      tex2_data[i+16][2] = 64;

      tex2_data[i+32][0] = 255;
      tex2_data[i+32][1] = 160;
      tex2_data[i+32][2] = 64 + 12*i;

      tex2_data[i+48][0] = 255;
      tex2_data[i+48][1] = 160 + 6*i;
      tex2_data[i+48][2] = 255;
   }
}