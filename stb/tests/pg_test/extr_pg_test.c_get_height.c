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
 float* hf ; 
 int hf_height ; 
 int hf_width ; 
 float stb_lerp (float,float,float) ; 

__attribute__((used)) static float get_height(float x, float y)
{
   float h00,h01,h10,h11,h0,h1;
   int ix,iy;
   if (x < 0) x = 0;
   if (x > hf_width-1) x = (float) hf_width-1;
   if (y < 0) y = 0;
   if (y > hf_height-1) y = (float) hf_height-1;
   ix = (int) x; x -= ix;
   iy = (int) y; y -= iy;
   h00 = hf[(iy+0)*hf_height+(ix+0)];
   h10 = hf[(iy+0)*hf_height+(ix+1)];
   h01 = hf[(iy+1)*hf_height+(ix+0)];
   h11 = hf[(iy+1)*hf_height+(ix+1)];
   h0 = stb_lerp(y, h00, h01);
   h1 = stb_lerp(y, h10, h11);
   return stb_lerp(x, h0, h1);
}