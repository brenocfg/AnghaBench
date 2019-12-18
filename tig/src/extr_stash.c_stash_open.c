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
struct view {int /*<<< orphan*/  watch; struct main_state* private; } ;
struct main_state {int with_graph; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;

/* Variables and functions */
 int OPEN_RELOAD ; 
 int /*<<< orphan*/  WATCH_STASH ; 
 int begin_update (struct view*,int /*<<< orphan*/ *,char const**,int) ; 
#define  encoding_arg 128 
 int /*<<< orphan*/  watch_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum status_code
stash_open(struct view *view, enum open_flags flags)
{
	static const char *stash_argv[] = { "git", "stash", "list",
		encoding_arg, "--no-color", "--pretty=raw", NULL };
	struct main_state *state = view->private;

	state->with_graph = false;
	watch_register(&view->watch, WATCH_STASH);
	return begin_update(view, NULL, stash_argv, flags | OPEN_RELOAD);
}