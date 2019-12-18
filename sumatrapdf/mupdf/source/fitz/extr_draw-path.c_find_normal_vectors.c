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
 float FLT_EPSILON ; 
 float FLT_TINY ; 
 float sqrtf (float) ; 

__attribute__((used)) static int find_normal_vectors(float dx, float dy, float linewidth, float *dlx, float *dly)
{
	if (dx == 0)
	{
		if (dy < FLT_TINY && dy > - FLT_TINY)
			goto tiny;
		else if (dy > 0)
			*dlx = linewidth;
		else
			*dlx = -linewidth;
		*dly = 0;
	}
	else if (dy == 0)
	{
		if (dx < FLT_TINY && dx > - FLT_TINY)
			goto tiny;
		else if (dx > 0)
			*dly = -linewidth;
		else
			*dly = linewidth;
		*dlx = 0;
	}
	else
	{
		float sq = dx * dx + dy * dy;
		float scale;

		if (sq < FLT_EPSILON)
			goto tiny;
		scale = linewidth / sqrtf(sq);
		*dlx = dy * scale;
		*dly = -dx * scale;
	}
	return 0;
tiny:
	*dlx = 0;
	*dly = 0;
	return 1;
}