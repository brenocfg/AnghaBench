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
struct window_mode_entry {struct window_clock_mode_data* data; } ;
struct window_clock_mode_data {int /*<<< orphan*/  screen; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct window_clock_mode_data*) ; 
 int /*<<< orphan*/  screen_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
window_clock_free(struct window_mode_entry *wme)
{
	struct window_clock_mode_data	*data = wme->data;

	evtimer_del(&data->timer);
	screen_free(&data->screen);
	free(data);
}