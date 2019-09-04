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
struct view {int /*<<< orphan*/  start_time; int /*<<< orphan*/  io; int /*<<< orphan*/ * pipe; int /*<<< orphan*/  vid; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_view (struct view*) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
setup_update(struct view *view, const char *vid)
{
	reset_view(view);
	/* XXX: Do not use string_copy_rev(), it copies until first space. */
	string_ncopy(view->vid, vid, strlen(vid));
	view->pipe = &view->io;
	view->start_time = time(NULL);
}