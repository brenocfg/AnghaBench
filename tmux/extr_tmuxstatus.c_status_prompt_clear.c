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
struct TYPE_2__ {int flags; } ;
struct client {int /*<<< orphan*/  flags; TYPE_1__ tty; int /*<<< orphan*/ * prompt_saved; int /*<<< orphan*/ * prompt_buffer; int /*<<< orphan*/ * prompt_string; int /*<<< orphan*/ * prompt_data; int /*<<< orphan*/  (* prompt_freecb ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_ALLREDRAWFLAGS ; 
 int TTY_FREEZE ; 
 int TTY_NOCURSOR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  status_pop_screen (struct client*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void
status_prompt_clear(struct client *c)
{
	if (c->prompt_string == NULL)
		return;

	if (c->prompt_freecb != NULL && c->prompt_data != NULL)
		c->prompt_freecb(c->prompt_data);

	free(c->prompt_string);
	c->prompt_string = NULL;

	free(c->prompt_buffer);
	c->prompt_buffer = NULL;

	free(c->prompt_saved);
	c->prompt_saved = NULL;

	c->tty.flags &= ~(TTY_NOCURSOR|TTY_FREEZE);
	c->flags |= CLIENT_ALLREDRAWFLAGS; /* was frozen and may have changed */

	status_pop_screen(c);
}