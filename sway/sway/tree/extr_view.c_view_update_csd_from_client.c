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
struct sway_view {int using_csd; struct sway_container* container; } ;
struct sway_container {scalar_t__ border; scalar_t__ saved_border; } ;

/* Variables and functions */
 scalar_t__ B_CSD ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 scalar_t__ container_is_floating (struct sway_container*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,struct sway_view*,int) ; 

void view_update_csd_from_client(struct sway_view *view, bool enabled) {
	sway_log(SWAY_DEBUG, "View %p updated CSD to %i", view, enabled);
	struct sway_container *con = view->container;
	if (enabled && con && con->border != B_CSD) {
		con->saved_border = con->border;
		if (container_is_floating(con)) {
			con->border = B_CSD;
		}
	} else if (!enabled && con && con->border == B_CSD) {
		con->border = con->saved_border;
	}
	view->using_csd = enabled;
}