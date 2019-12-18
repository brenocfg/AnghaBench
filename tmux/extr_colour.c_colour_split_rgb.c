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
typedef  int u_char ;

/* Variables and functions */

void
colour_split_rgb(int c, u_char *r, u_char *g, u_char *b)
{
	*r = (c >> 16) & 0xff;
	*g = (c >> 8) & 0xff;
	*b = c & 0xff;
}