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
struct window_pane {int dummy; } ;
struct window_mode_entry {struct window_pane* wp; } ;
struct screen_write_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  global_options ; 
 int /*<<< orphan*/  notify_pane (char*,struct window_pane*) ; 
 scalar_t__ options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  paste_add (char const*,void*,size_t) ; 
 int /*<<< orphan*/  screen_write_setselection (struct screen_write_ctx*,void*,size_t) ; 
 int /*<<< orphan*/  screen_write_start (struct screen_write_ctx*,struct window_pane*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  screen_write_stop (struct screen_write_ctx*) ; 

__attribute__((used)) static void
window_copy_copy_buffer(struct window_mode_entry *wme, const char *prefix,
    void *buf, size_t len)
{
	struct window_pane	*wp = wme->wp;
	struct screen_write_ctx	 ctx;

	if (options_get_number(global_options, "set-clipboard") != 0) {
		screen_write_start(&ctx, wp, NULL);
		screen_write_setselection(&ctx, buf, len);
		screen_write_stop(&ctx);
		notify_pane("pane-set-clipboard", wp);
	}

	paste_add(prefix, buf, len);
}