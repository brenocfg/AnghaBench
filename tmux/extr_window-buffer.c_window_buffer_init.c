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
struct window_mode_entry {struct window_buffer_modedata* data; struct window_pane* wp; } ;
struct window_buffer_modedata {int /*<<< orphan*/  data; void* command; void* format; int /*<<< orphan*/  fs; struct window_pane* wp; } ;
struct screen {int dummy; } ;
struct cmd_find_state {int dummy; } ;
struct args {scalar_t__ argc; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WINDOW_BUFFER_DEFAULT_COMMAND ; 
 int /*<<< orphan*/  WINDOW_BUFFER_DEFAULT_FORMAT ; 
 int /*<<< orphan*/  args_get (struct args*,float) ; 
 int /*<<< orphan*/  args_has (struct args*,float) ; 
 int /*<<< orphan*/  cmd_find_copy_state (int /*<<< orphan*/ *,struct cmd_find_state*) ; 
 int /*<<< orphan*/  mode_tree_build (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode_tree_draw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode_tree_start (struct window_pane*,struct args*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct window_buffer_modedata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct screen**) ; 
 int /*<<< orphan*/  mode_tree_zoom (int /*<<< orphan*/ ,struct args*) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_buffer_build ; 
 int /*<<< orphan*/  window_buffer_draw ; 
 int /*<<< orphan*/  window_buffer_menu ; 
 int /*<<< orphan*/  window_buffer_menu_items ; 
 int /*<<< orphan*/  window_buffer_search ; 
 int /*<<< orphan*/  window_buffer_sort_list ; 
 struct window_buffer_modedata* xcalloc (int,int) ; 
 void* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct screen *
window_buffer_init(struct window_mode_entry *wme, struct cmd_find_state *fs,
    struct args *args)
{
	struct window_pane		*wp = wme->wp;
	struct window_buffer_modedata	*data;
	struct screen			*s;

	wme->data = data = xcalloc(1, sizeof *data);
	data->wp = wp;
	cmd_find_copy_state(&data->fs, fs);

	if (args == NULL || !args_has(args, 'F'))
		data->format = xstrdup(WINDOW_BUFFER_DEFAULT_FORMAT);
	else
		data->format = xstrdup(args_get(args, 'F'));
	if (args == NULL || args->argc == 0)
		data->command = xstrdup(WINDOW_BUFFER_DEFAULT_COMMAND);
	else
		data->command = xstrdup(args->argv[0]);

	data->data = mode_tree_start(wp, args, window_buffer_build,
	    window_buffer_draw, window_buffer_search, window_buffer_menu, data,
	    window_buffer_menu_items, window_buffer_sort_list,
	    nitems(window_buffer_sort_list), &s);
	mode_tree_zoom(data->data, args);

	mode_tree_build(data->data);
	mode_tree_draw(data->data);

	return (s);
}