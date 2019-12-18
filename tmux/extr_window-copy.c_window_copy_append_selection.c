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
struct paste_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  global_options ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  notify_pane (char*,struct window_pane*) ; 
 scalar_t__ options_get_number (int /*<<< orphan*/ ,char*) ; 
 char* paste_buffer_data (struct paste_buffer*,size_t*) ; 
 struct paste_buffer* paste_get_top (char const**) ; 
 scalar_t__ paste_set (char*,size_t,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  screen_write_setselection (struct screen_write_ctx*,char*,size_t) ; 
 int /*<<< orphan*/  screen_write_start (struct screen_write_ctx*,struct window_pane*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  screen_write_stop (struct screen_write_ctx*) ; 
 char* window_copy_get_selection (struct window_mode_entry*,size_t*) ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static void
window_copy_append_selection(struct window_mode_entry *wme)
{
	struct window_pane		*wp = wme->wp;
	char				*buf;
	struct paste_buffer		*pb;
	const char			*bufdata, *bufname = NULL;
	size_t				 len, bufsize;
	struct screen_write_ctx		 ctx;

	buf = window_copy_get_selection(wme, &len);
	if (buf == NULL)
		return;

	if (options_get_number(global_options, "set-clipboard") != 0) {
		screen_write_start(&ctx, wp, NULL);
		screen_write_setselection(&ctx, buf, len);
		screen_write_stop(&ctx);
		notify_pane("pane-set-clipboard", wp);
	}

	pb = paste_get_top(&bufname);
	if (pb != NULL) {
		bufdata = paste_buffer_data(pb, &bufsize);
		buf = xrealloc(buf, len + bufsize);
		memmove(buf + bufsize, buf, len);
		memcpy(buf, bufdata, bufsize);
		len += bufsize;
	}
	if (paste_set(buf, len, bufname, NULL) != 0)
		free(buf);
}