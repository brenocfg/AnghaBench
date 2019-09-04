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
typedef  size_t u_int ;
struct grid_line {int dummy; } ;
struct grid {struct grid_line* linedata; } ;

/* Variables and functions */

struct grid_line *
grid_get_line(struct grid *gd, u_int line)
{
	return (&gd->linedata[line]);
}