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
struct view {int dummy; } ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;

/* Variables and functions */
 int OPEN_RELOAD ; 
 int /*<<< orphan*/  open_view (struct view*,int /*<<< orphan*/ *,int) ; 
 int show_untracked_only ; 
 int /*<<< orphan*/  status_view ; 

void
open_status_view(struct view *prev, bool untracked_only, enum open_flags flags)
{
	if (show_untracked_only != untracked_only) {
		show_untracked_only = untracked_only;
		flags |= OPEN_RELOAD;
	}
	open_view(prev, &status_view, flags);
}