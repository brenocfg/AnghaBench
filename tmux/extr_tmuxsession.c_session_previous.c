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
 struct winlink* RB_MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct winlink* session_previous_alert (struct winlink*) ; 
 int session_set_current (struct session*,struct winlink*) ; 
 struct winlink* winlink_previous (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  winlinks ; 

int
session_previous(struct session *s, int alert)
{
	struct winlink	*wl;

	if (s->curw == NULL)
		return (-1);

	wl = winlink_previous(s->curw);
	if (alert)
		wl = session_previous_alert(wl);
	if (wl == NULL) {
		wl = RB_MAX(winlinks, &s->windows);
		if (alert && (wl = session_previous_alert(wl)) == NULL)
			return (-1);
	}
	return (session_set_current(s, wl));
}