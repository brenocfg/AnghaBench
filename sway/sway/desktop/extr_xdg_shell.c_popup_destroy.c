#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  link; } ;
struct TYPE_3__ {int /*<<< orphan*/  link; } ;
struct sway_xdg_popup {TYPE_2__ destroy; TYPE_1__ new_popup; } ;
struct sway_view_child {int /*<<< orphan*/ * impl; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_xdg_popup*) ; 
 int /*<<< orphan*/  popup_impl ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void popup_destroy(struct sway_view_child *child) {
	if (!sway_assert(child->impl == &popup_impl,
			"Expected an xdg_shell popup")) {
		return;
	}
	struct sway_xdg_popup *popup = (struct sway_xdg_popup *)child;
	wl_list_remove(&popup->new_popup.link);
	wl_list_remove(&popup->destroy.link);
	free(popup);
}