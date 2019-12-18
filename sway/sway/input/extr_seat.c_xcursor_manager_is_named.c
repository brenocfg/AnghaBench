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
struct wlr_xcursor_manager {scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static bool xcursor_manager_is_named(const struct wlr_xcursor_manager *manager,
		const char *name) {
	return (!manager->name && !name) ||
		(name && manager->name && strcmp(name, manager->name) == 0);
}