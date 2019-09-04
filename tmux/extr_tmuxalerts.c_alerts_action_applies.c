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
struct winlink {TYPE_1__* session; } ;
struct TYPE_2__ {struct winlink* curw; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int ALERT_ANY ; 
 int ALERT_CURRENT ; 
 int ALERT_OTHER ; 
 int options_get_number (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
alerts_action_applies(struct winlink *wl, const char *name)
{
	int	action;

	/*
	 * {bell,activity,silence}-action determines when to alert: none means
	 * nothing happens, current means only do something for the current
	 * window and other means only for windows other than the current.
	 */

	action = options_get_number(wl->session->options, name);
	if (action == ALERT_ANY)
		return (1);
	if (action == ALERT_CURRENT)
		return (wl == wl->session->curw);
	if (action == ALERT_OTHER)
		return (wl != wl->session->curw);
	return (0);
}