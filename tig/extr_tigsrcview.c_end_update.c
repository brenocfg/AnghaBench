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
struct view {int /*<<< orphan*/ * pipe; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read ) (struct view*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  io_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct view*,int /*<<< orphan*/ *,int) ; 

void
end_update(struct view *view, bool force)
{
	if (!view->pipe)
		return;
	while (!view->ops->read(view, NULL, force))
		if (!force)
			return;
	if (force)
		io_kill(view->pipe);
	io_done(view->pipe);
	view->pipe = NULL;
}