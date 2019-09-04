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
typedef  int /*<<< orphan*/  u_int ;
struct screen {int /*<<< orphan*/ * sel; int /*<<< orphan*/ * tabs; void* ccolour; scalar_t__ cstyle; int /*<<< orphan*/ * titles; void* title; int /*<<< orphan*/  grid; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_reinit (struct screen*) ; 
 void* xstrdup (char*) ; 

void
screen_init(struct screen *s, u_int sx, u_int sy, u_int hlimit)
{
	s->grid = grid_create(sx, sy, hlimit);
	s->title = xstrdup("");
	s->titles = NULL;

	s->cstyle = 0;
	s->ccolour = xstrdup("");
	s->tabs = NULL;
	s->sel = NULL;

	screen_reinit(s);
}