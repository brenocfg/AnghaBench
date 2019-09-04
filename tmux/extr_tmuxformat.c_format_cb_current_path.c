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
struct window_pane {int /*<<< orphan*/  fd; } ;
struct format_tree {struct window_pane* wp; } ;
struct format_entry {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 char* osdep_get_cwd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static void
format_cb_current_path(struct format_tree *ft, struct format_entry *fe)
{
	struct window_pane	*wp = ft->wp;
	char			*cwd;

	if (wp == NULL)
		return;

	cwd = osdep_get_cwd(wp->fd);
	if (cwd != NULL)
		fe->value = xstrdup(cwd);
}