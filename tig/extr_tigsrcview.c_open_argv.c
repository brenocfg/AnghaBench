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
struct view {char const* dir; int /*<<< orphan*/  io; int /*<<< orphan*/  name; int /*<<< orphan*/  argv; scalar_t__ pipe; } ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;

/* Variables and functions */
 int OPEN_PREPARED ; 
 int /*<<< orphan*/  argv_copy (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  end_update (struct view*,int) ; 
 int /*<<< orphan*/  io_strerror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_view (struct view*,struct view*,int) ; 
 int /*<<< orphan*/  report (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
open_argv(struct view *prev, struct view *view, const char *argv[], const char *dir, enum open_flags flags)
{
	if (view->pipe)
		end_update(view, true);
	view->dir = dir;

	if (!argv_copy(&view->argv, argv)) {
		report("Failed to open %s view: %s", view->name, io_strerror(&view->io));
	} else {
		open_view(prev, view, flags | OPEN_PREPARED);
	}
}