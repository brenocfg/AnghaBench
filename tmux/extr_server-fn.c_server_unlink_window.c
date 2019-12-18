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
struct session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  server_destroy_session_group (struct session*) ; 
 int /*<<< orphan*/  server_redraw_session_group (struct session*) ; 
 scalar_t__ session_detach (struct session*,struct winlink*) ; 

void
server_unlink_window(struct session *s, struct winlink *wl)
{
	if (session_detach(s, wl))
		server_destroy_session_group(s);
	else
		server_redraw_session_group(s);
}