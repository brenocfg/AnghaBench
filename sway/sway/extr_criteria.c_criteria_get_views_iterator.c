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
struct sway_container {int /*<<< orphan*/  view; } ;
struct match_data {int /*<<< orphan*/  matches; int /*<<< orphan*/  criteria; } ;

/* Variables and functions */
 scalar_t__ criteria_matches_view (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void criteria_get_views_iterator(struct sway_container *container,
		void *data) {
	struct match_data *match_data = data;
	if (container->view) {
		if (criteria_matches_view(match_data->criteria, container->view)) {
			list_add(match_data->matches, container->view);
		}
	}
}