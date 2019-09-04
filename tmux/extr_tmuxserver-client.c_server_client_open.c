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
struct client {int flags; int /*<<< orphan*/  tty; int /*<<< orphan*/  ttyname; } ;

/* Variables and functions */
 int CLIENT_CONTROL ; 
 int CLIENT_TERMINAL ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tty_open (int /*<<< orphan*/ *,char**) ; 
 char* xstrdup (char*) ; 

int
server_client_open(struct client *c, char **cause)
{
	if (c->flags & CLIENT_CONTROL)
		return (0);

	if (strcmp(c->ttyname, "/dev/tty") == 0) {
		*cause = xstrdup("can't use /dev/tty");
		return (-1);
	}

	if (!(c->flags & CLIENT_TERMINAL)) {
		*cause = xstrdup("not a terminal");
		return (-1);
	}

	if (tty_open(&c->tty, cause) != 0)
		return (-1);

	return (0);
}