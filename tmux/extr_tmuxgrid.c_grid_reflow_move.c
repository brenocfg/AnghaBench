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
struct grid_line {int dummy; } ;
struct grid {int dummy; } ;

/* Variables and functions */
 struct grid_line* grid_reflow_add (struct grid*,int) ; 
 int /*<<< orphan*/  grid_reflow_dead (struct grid_line*) ; 
 int /*<<< orphan*/  memcpy (struct grid_line*,struct grid_line*,int) ; 

__attribute__((used)) static struct grid_line *
grid_reflow_move(struct grid *gd, struct grid_line *from)
{
	struct grid_line	*to;

	to = grid_reflow_add(gd, 1);
	memcpy(to, from, sizeof *to);
	grid_reflow_dead(from);
	return (to);
}