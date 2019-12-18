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
struct sway_xwayland_view {int dummy; } ;
struct sway_view {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ SWAY_VIEW_XWAYLAND ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 

__attribute__((used)) static struct sway_xwayland_view *xwayland_view_from_view(
		struct sway_view *view) {
	if (!sway_assert(view->type == SWAY_VIEW_XWAYLAND,
			"Expected xwayland view")) {
		return NULL;
	}
	return (struct sway_xwayland_view *)view;
}