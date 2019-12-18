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
struct sway_view_impl {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  unmap; } ;
struct sway_view {int type; int allow_request_urgent; TYPE_1__ events; int /*<<< orphan*/  executed_criteria; struct sway_view_impl const* impl; } ;
typedef  enum sway_view_type { ____Placeholder_sway_view_type } sway_view_type ;

/* Variables and functions */
 int /*<<< orphan*/  create_list () ; 
 int /*<<< orphan*/  wl_signal_init (int /*<<< orphan*/ *) ; 

void view_init(struct sway_view *view, enum sway_view_type type,
		const struct sway_view_impl *impl) {
	view->type = type;
	view->impl = impl;
	view->executed_criteria = create_list();
	view->allow_request_urgent = true;
	wl_signal_init(&view->events.unmap);
}