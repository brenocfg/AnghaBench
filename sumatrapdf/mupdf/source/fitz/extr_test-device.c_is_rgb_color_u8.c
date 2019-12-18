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
 int fz_absi (int) ; 

__attribute__((used)) static int
is_rgb_color_u8(int threshold_u8, int r, int g, int b)
{
	int rg_diff = fz_absi(r - g);
	int rb_diff = fz_absi(r - b);
	int gb_diff = fz_absi(g - b);
	return rg_diff > threshold_u8 || rb_diff > threshold_u8 || gb_diff > threshold_u8;
}