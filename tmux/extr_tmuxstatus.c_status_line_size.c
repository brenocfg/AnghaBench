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
struct session {int /*<<< orphan*/  statuslines; } ;
struct client {int flags; struct session* session; } ;

/* Variables and functions */
 int CLIENT_STATUSOFF ; 

u_int
status_line_size(struct client *c)
{
	struct session	*s = c->session;

	if (c->flags & CLIENT_STATUSOFF)
		return (0);
	return (s->statuslines);
}