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
 int MAX (int,scalar_t__) ; 
 int MIN (int,scalar_t__) ; 
 scalar_t__ MIN_VIEW_WIDTH ; 
 int apply_step (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opt_split_view_width ; 

int
apply_vertical_split(int base_width)
{
	int width  = apply_step(opt_split_view_width, base_width);

	width = MAX(width, MIN_VIEW_WIDTH);
	width = MIN(width, base_width - MIN_VIEW_WIDTH);

	return width;
}