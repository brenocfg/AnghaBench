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
typedef  int u_int ;
struct grid_line {int dummy; } ;
struct grid {size_t sy; struct grid_line* linedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct grid_line*,int /*<<< orphan*/ ,int) ; 
 struct grid_line* xreallocarray (struct grid_line*,int,int) ; 

__attribute__((used)) static struct grid_line *
grid_reflow_add(struct grid *gd, u_int n)
{
	struct grid_line	*gl;
	u_int			 sy = gd->sy + n;

	gd->linedata = xreallocarray(gd->linedata, sy, sizeof *gd->linedata);
	gl = &gd->linedata[gd->sy];
	memset(gl, 0, n * (sizeof *gl));
	gd->sy = sy;
	return (gl);
}