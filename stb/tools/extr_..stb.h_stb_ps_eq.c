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
typedef  int /*<<< orphan*/  stb_ps ;

/* Variables and functions */
 scalar_t__ stb_ps_count (int /*<<< orphan*/ *) ; 
 int stb_ps_subset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int stb_ps_eq(stb_ps *p0, stb_ps *p1)
{
   if (stb_ps_count(p0) != stb_ps_count(p1))
      return 0;
   return stb_ps_subset(p0, p1);
}