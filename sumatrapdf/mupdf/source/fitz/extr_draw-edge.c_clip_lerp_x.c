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
 int ENTER ; 
 int INSIDE ; 
 int LEAVE ; 
 int OUTSIDE ; 

__attribute__((used)) static int
clip_lerp_x(int val, int m, int x0, int y0, int x1, int y1, int *out)
{
	int v0out = m ? x0 > val : x0 < val;
	int v1out = m ? x1 > val : x1 < val;

	if (v0out + v1out == 0)
		return INSIDE;

	if (v0out + v1out == 2)
		return OUTSIDE;

	if (v1out)
	{
		*out = y0 + (int)(((float)(y1 - y0)) * (val - x0) / (x1 - x0));
		return LEAVE;
	}

	else
	{
		*out = y1 + (int)(((float)(y0 - y1)) * (val - x1) / (x0 - x1));
		return ENTER;
	}
}