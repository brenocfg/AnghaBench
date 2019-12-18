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
struct screen {int dummy; } ;
struct window_pane {TYPE_1__* window; int /*<<< orphan*/ * searchstr; struct screen base; } ;
struct window_mode_entry {struct window_copy_mode_data* data; struct window_pane* wp; } ;
struct window_copy_mode_data {int searchx; int searchy; int searcho; char jumpchar; int /*<<< orphan*/  dragtimer; int /*<<< orphan*/  modekeys; int /*<<< orphan*/  screen; void* jumptype; int /*<<< orphan*/ * searchmark; int /*<<< orphan*/ * searchstr; void* searchtype; int /*<<< orphan*/  lineflag; int /*<<< orphan*/  cursordrag; } ;
struct TYPE_2__ {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSORDRAG_NONE ; 
 int /*<<< orphan*/  LINE_SEL_NONE ; 
 void* WINDOW_COPY_OFF ; 
 void* WINDOW_COPY_SEARCHUP ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct window_mode_entry*) ; 
 int /*<<< orphan*/  options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  screen_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_size_x (struct screen*) ; 
 int /*<<< orphan*/  screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  window_copy_scroll_timer ; 
 struct window_copy_mode_data* xcalloc (int,int) ; 
 int /*<<< orphan*/ * xstrdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct window_copy_mode_data *
window_copy_common_init(struct window_mode_entry *wme)
{
	struct window_pane		*wp = wme->wp;
	struct window_copy_mode_data	*data;
	struct screen			*base = &wp->base;

	wme->data = data = xcalloc(1, sizeof *data);

	data->cursordrag = CURSORDRAG_NONE;
	data->lineflag = LINE_SEL_NONE;

	if (wp->searchstr != NULL) {
		data->searchtype = WINDOW_COPY_SEARCHUP;
		data->searchstr = xstrdup(wp->searchstr);
	} else {
		data->searchtype = WINDOW_COPY_OFF;
		data->searchstr = NULL;
	}
	data->searchmark = NULL;
	data->searchx = data->searchy = data->searcho = -1;

	data->jumptype = WINDOW_COPY_OFF;
	data->jumpchar = '\0';

	screen_init(&data->screen, screen_size_x(base), screen_size_y(base), 0);
	data->modekeys = options_get_number(wp->window->options, "mode-keys");

	evtimer_set(&data->dragtimer, window_copy_scroll_timer, wme);

	return (data);
}