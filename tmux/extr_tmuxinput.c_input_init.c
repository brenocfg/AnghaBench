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
struct window_pane {struct input_ctx* ictx; } ;
struct input_ctx {int /*<<< orphan*/  timer; int /*<<< orphan*/ * since_ground; int /*<<< orphan*/  input_buf; int /*<<< orphan*/  input_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_BUF_START ; 
 int /*<<< orphan*/ * evbuffer_new () ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct input_ctx*) ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 int /*<<< orphan*/  input_reset (struct window_pane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_timer_callback ; 
 struct input_ctx* xcalloc (int,int) ; 
 int /*<<< orphan*/  xmalloc (int /*<<< orphan*/ ) ; 

void
input_init(struct window_pane *wp)
{
	struct input_ctx	*ictx;

	ictx = wp->ictx = xcalloc(1, sizeof *ictx);

	ictx->input_space = INPUT_BUF_START;
	ictx->input_buf = xmalloc(INPUT_BUF_START);

	ictx->since_ground = evbuffer_new();
	if (ictx->since_ground == NULL)
		fatalx("out of memory");

	evtimer_set(&ictx->timer, input_timer_callback, ictx);

	input_reset(wp, 0);
}