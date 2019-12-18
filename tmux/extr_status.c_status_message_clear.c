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
struct client {int /*<<< orphan*/  flags; TYPE_1__ tty; int /*<<< orphan*/ * prompt_string; int /*<<< orphan*/ * message_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_ALLREDRAWFLAGS ; 
 int TTY_FREEZE ; 
 int TTY_NOCURSOR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  status_pop_screen (struct client*) ; 

void
status_message_clear(struct client *c)
{
	if (c->message_string == NULL)
		return;

	free(c->message_string);
	c->message_string = NULL;

	if (c->prompt_string == NULL)
		c->tty.flags &= ~(TTY_NOCURSOR|TTY_FREEZE);
	c->flags |= CLIENT_ALLREDRAWFLAGS; /* was frozen and may have changed */

	status_pop_screen(c);
}