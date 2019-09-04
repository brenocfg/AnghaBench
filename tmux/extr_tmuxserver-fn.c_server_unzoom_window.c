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
struct window {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  server_redraw_window (struct window*) ; 
 scalar_t__ window_unzoom (struct window*) ; 

void
server_unzoom_window(struct window *w)
{
	if (window_unzoom(w) == 0)
		server_redraw_window(w);
}