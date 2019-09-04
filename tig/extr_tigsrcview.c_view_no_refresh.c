#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct view {TYPE_1__* ops; int /*<<< orphan*/  vid; int /*<<< orphan*/  lines; } ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int OPEN_ALWAYS_LOAD ; 
 int OPEN_REFRESH ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  view_can_refresh (struct view*) ; 

__attribute__((used)) static bool
view_no_refresh(struct view *view, enum open_flags flags)
{
	bool reload = !!(flags & OPEN_ALWAYS_LOAD) || !view->lines;

	return (!reload && !strcmp(view->vid, view->ops->id)) ||
	       ((flags & OPEN_REFRESH) && !view_can_refresh(view));
}