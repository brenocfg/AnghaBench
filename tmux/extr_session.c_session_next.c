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
struct session {int /*<<< orphan*/  windows; int /*<<< orphan*/ * curw; } ;

/* Variables and functions */
 struct winlink* RB_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct winlink* session_next_alert (struct winlink*) ; 
 int session_set_current (struct session*,struct winlink*) ; 
 struct winlink* winlink_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  winlinks ; 

int
session_next(struct session *s, int alert)
{
	struct winlink	*wl;

	if (s->curw == NULL)
		return (-1);

	wl = winlink_next(s->curw);
	if (alert)
		wl = session_next_alert(wl);
	if (wl == NULL) {
		wl = RB_MIN(winlinks, &s->windows);
		if (alert && ((wl = session_next_alert(wl)) == NULL))
			return (-1);
	}
	return (session_set_current(s, wl));
}