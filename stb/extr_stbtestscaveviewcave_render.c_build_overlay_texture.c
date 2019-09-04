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
typedef  int uint32 ;

/* Variables and functions */
 int TEX_SIZE ; 
 int stb_rand () ; 
 int** texture ; 

void build_overlay_texture(int n)
{
   int x,y;
   uint32 color = stb_rand();
   if (color & 16)
      color = 0xff000000;
   else
      color = 0xffffffff;
   for (y=0; y<TEX_SIZE; ++y)
      for (x=0; x<TEX_SIZE; ++x) {
         texture[y][x] = 0;
      }

   for (y=0; y < TEX_SIZE/8; ++y) {
      for (x=0; x < TEX_SIZE; ++x) {
         texture[y][x] = color;
         texture[TEX_SIZE-1-y][x] = color;
         texture[x][y] = color;
         texture[x][TEX_SIZE-1-y] = color;
      }
   }
}