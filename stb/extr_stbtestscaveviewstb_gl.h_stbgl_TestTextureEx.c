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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ malloc (int) ; 
 int stbgl_TexImage2D (int /*<<< orphan*/ ,int,int,unsigned char*,char*) ; 
 int stbgl_rand () ; 

int stbgl_TestTextureEx(int w, char *scale_table, int checks_log2, int r1,int g1,int b1, int r2, int b2, int g2)
{
   int rt[2] = {r1,r2}, gt[2] = {g1,g2}, bt[2] = {b1,b2};
   signed char modded[256];
   int i,j, m = w-1, s,k,scale;
   unsigned char *data = (unsigned char *) malloc(w*w*3);
   assert((m & w) == 0);
   data[0] = 128;
   for (s=0; s < 16; ++s) if ((1 << s) == w) break;
   assert(w == (1 << s));
   // plasma fractal noise
   for (k=s-1; k >= 0; --k) {
      int step = 1 << k;
      // interpolate from "parents"
      for (j=0; j < w; j += step*2) {
         for (i=0; i < w; i += step*2) {
            int i1 = i+step, j1=j+step;
            int i2 = (i+step*2)&m, j2 = (j+step*2)&m;
            int p00 = data[(j*w+i )*3], p01 = data[(j2*w+i )*3];
            int p10 = data[(j*w+i2)*3], p11 = data[(j2*w+i2)*3];
            data[(j*w+i1)*3] = (p00+p10)>>1;
            data[(j1*w+i)*3] = (p00+p01)>>1;
            data[(j1*w+i1)*3]= (p00+p01+p10+p11)>>2;
         }
      }
      scale = scale_table[s-k+1];
      if (!scale) continue; // just interpolate down the remaining data
      for (j=0,i=0; i < 256; i += 2, j == scale ? j=0 : ++j)
         modded[i] = j, modded[i+1] = -j; // precompute i%scale (plus sign)
      for (j=0; j < w; j += step)
         for (i=0; i < w; i += step) {
            int x = data[(j*w+i)*3] + modded[(stbgl_rand() >> 12) & 255];
            data[(j*w+i)*3] = x < 0 ? 0 : x > 255 ? 255 : x;
         }
   }
   for (j=0; j < w; ++j)
      for (i=0; i < w; ++i) {
         int check = ((i^j) & (1 << (s-checks_log2))) == 0;
         int v = data[(j*w+i)*3] >> 2;
         data[(j*w+i)*3+0] = rt[check]-v;
         data[(j*w+i)*3+1] = gt[check]-v;
         data[(j*w+i)*3+2] = bt[check]-v;
      }
   return stbgl_TexImage2D(0, w, w, data, "3m!"); // 3 channels, mipmap, free
}