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
struct sway_view {TYPE_1__* impl; } ;
struct TYPE_2__ {char const* (* get_string_prop ) (struct sway_view*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VIEW_PROP_TITLE ; 
 char const* stub1 (struct sway_view*,int /*<<< orphan*/ ) ; 

const char *view_get_title(struct sway_view *view) {
	if (view->impl->get_string_prop) {
		return view->impl->get_string_prop(view, VIEW_PROP_TITLE);
	}
	return NULL;
}