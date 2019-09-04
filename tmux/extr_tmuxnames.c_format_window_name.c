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
struct window {int id; int /*<<< orphan*/  options; int /*<<< orphan*/  active; } ;
struct format_tree {int dummy; } ;

/* Variables and functions */
 int FORMAT_WINDOW ; 
 struct format_tree* format_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_defaults_pane (struct format_tree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_defaults_window (struct format_tree*,struct window*) ; 
 char* format_expand (struct format_tree*,char const*) ; 
 int /*<<< orphan*/  format_free (struct format_tree*) ; 
 char* options_get_string (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
format_window_name(struct window *w)
{
	struct format_tree	*ft;
	const char		*fmt;
	char			*name;

	ft = format_create(NULL, NULL, FORMAT_WINDOW|w->id, 0);
	format_defaults_window(ft, w);
	format_defaults_pane(ft, w->active);

	fmt = options_get_string(w->options, "automatic-rename-format");
	name = format_expand(ft, fmt);

	format_free(ft);
	return (name);
}