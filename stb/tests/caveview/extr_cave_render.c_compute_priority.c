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
 int view_dist_in_chunks ; 

float compute_priority(int cx, int cy, float x, float y)
{
   float distx, disty, dist2;
   distx = (cx*16+8) - x;
   disty = (cy*16+8) - y;
   dist2 = distx*distx + disty*disty;
   return view_dist_in_chunks*view_dist_in_chunks * 16 * 16 - dist2;
}