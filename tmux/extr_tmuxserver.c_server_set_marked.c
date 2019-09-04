#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct winlink {int /*<<< orphan*/  window; } ;
struct window_pane {int dummy; } ;
struct session {int dummy; } ;
struct TYPE_3__ {struct window_pane* wp; int /*<<< orphan*/  w; struct winlink* wl; struct session* s; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_find_clear_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ marked_pane ; 

void
server_set_marked(struct session *s, struct winlink *wl, struct window_pane *wp)
{
	cmd_find_clear_state(&marked_pane, 0);
	marked_pane.s = s;
	marked_pane.wl = wl;
	marked_pane.w = wl->window;
	marked_pane.wp = wp;
}