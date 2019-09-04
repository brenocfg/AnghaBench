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
 int /*<<< orphan*/ * frustum ; 
 int /*<<< orphan*/  test_plane (int /*<<< orphan*/ *,float,float,float,float,float,float) ; 

__attribute__((used)) static int is_box_in_frustum(float *bmin, float *bmax)
{
   int i;
   for (i=0; i < 6; ++i)
      if (!test_plane(&frustum[i], bmin[0], bmin[1], bmin[2], bmax[0], bmax[1], bmax[2]))
         return 0;
   return 1;
}