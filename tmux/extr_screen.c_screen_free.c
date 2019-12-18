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
struct screen {int /*<<< orphan*/  grid; int /*<<< orphan*/  ccolour; int /*<<< orphan*/  title; int /*<<< orphan*/  tabs; int /*<<< orphan*/  sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grid_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_free_titles (struct screen*) ; 

void
screen_free(struct screen *s)
{
	free(s->sel);
	free(s->tabs);
	free(s->title);
	free(s->ccolour);

	grid_destroy(s->grid);

	screen_free_titles(s);
}