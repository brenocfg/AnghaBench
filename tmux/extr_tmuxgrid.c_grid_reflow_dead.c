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
struct grid_line {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_LINE_DEAD ; 
 int /*<<< orphan*/  memset (struct grid_line*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
grid_reflow_dead(struct grid_line *gl)
{
	memset(gl, 0, sizeof *gl);
	gl->flags = GRID_LINE_DEAD;
}