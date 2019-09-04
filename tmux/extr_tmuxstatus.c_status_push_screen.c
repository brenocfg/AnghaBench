#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct status_line {int /*<<< orphan*/  references; int /*<<< orphan*/ * active; int /*<<< orphan*/  screen; } ;
struct TYPE_2__ {int /*<<< orphan*/  sx; } ;
struct client {TYPE_1__ tty; struct status_line status; } ;

/* Variables and functions */
 int /*<<< orphan*/  screen_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_line_size (struct client*) ; 
 int /*<<< orphan*/ * xmalloc (int) ; 

__attribute__((used)) static void
status_push_screen(struct client *c)
{
	struct status_line *sl = &c->status;

	if (sl->active == &sl->screen) {
		sl->active = xmalloc(sizeof *sl->active);
		screen_init(sl->active, c->tty.sx, status_line_size(c), 0);
	}
	sl->references++;
}