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
struct winlink {int dummy; } ;
struct session {struct winlink* curw; int /*<<< orphan*/  lastw; } ;

/* Variables and functions */
 struct winlink* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int session_set_current (struct session*,struct winlink*) ; 

int
session_last(struct session *s)
{
	struct winlink	*wl;

	wl = TAILQ_FIRST(&s->lastw);
	if (wl == NULL)
		return (-1);
	if (wl == s->curw)
		return (1);

	return (session_set_current(s, wl));
}