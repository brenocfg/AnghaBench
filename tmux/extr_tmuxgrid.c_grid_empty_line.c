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
struct grid {int /*<<< orphan*/  sx; int /*<<< orphan*/ * linedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOUR_DEFAULT (size_t) ; 
 int /*<<< orphan*/  grid_expand_line (struct grid*,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
grid_empty_line(struct grid *gd, u_int py, u_int bg)
{
	memset(&gd->linedata[py], 0, sizeof gd->linedata[py]);
	if (!COLOUR_DEFAULT(bg))
		grid_expand_line(gd, py, gd->sx, bg);
}