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
struct window_pane {int /*<<< orphan*/  modes; } ;
struct window_mode_entry {int /*<<< orphan*/ * mode; } ;
struct job {int dummy; } ;
struct cmd_run_shell_data {int wp_id; int /*<<< orphan*/ * item; } ;
struct cmd_find_state {struct window_pane* wp; } ;

/* Variables and functions */
 struct window_mode_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ cmd_find_from_nothing (struct cmd_find_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_print (int /*<<< orphan*/ *,char*,char const*) ; 
 struct cmd_run_shell_data* job_get_data (struct job*) ; 
 int /*<<< orphan*/  window_copy_add (struct window_pane*,char*,char const*) ; 
 struct window_pane* window_pane_find_by_id (int) ; 
 int /*<<< orphan*/  window_pane_set_mode (struct window_pane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_view_mode ; 

__attribute__((used)) static void
cmd_run_shell_print(struct job *job, const char *msg)
{
	struct cmd_run_shell_data	*cdata = job_get_data(job);
	struct window_pane		*wp = NULL;
	struct cmd_find_state		 fs;
	struct window_mode_entry	*wme;

	if (cdata->wp_id != -1)
		wp = window_pane_find_by_id(cdata->wp_id);
	if (wp == NULL) {
		if (cdata->item != NULL) {
			cmdq_print(cdata->item, "%s", msg);
			return;
		}
		if (cmd_find_from_nothing(&fs, 0) != 0)
			return;
		wp = fs.wp;
		if (wp == NULL)
			return;
	}

	wme = TAILQ_FIRST(&wp->modes);
	if (wme == NULL || wme->mode != &window_view_mode)
		window_pane_set_mode(wp, &window_view_mode, NULL, NULL);
	window_copy_add(wp, "%s", msg);
}