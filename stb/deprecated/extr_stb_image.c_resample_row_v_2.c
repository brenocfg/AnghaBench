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
typedef  int stbi__uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  STBI_NOTUSED (int) ; 
 int div4 (int) ; 

__attribute__((used)) static stbi__uint8* resample_row_v_2(stbi__uint8 *out, stbi__uint8 *in_near, stbi__uint8 *in_far, int w, int hs)
{
   // need to generate two samples vertically for every one in input
   int i;
   STBI_NOTUSED(hs);
   for (i=0; i < w; ++i)
      out[i] = div4(3*in_near[i] + in_far[i] + 2);
   return out;
}