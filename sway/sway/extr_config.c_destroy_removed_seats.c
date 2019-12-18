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
struct sway_seat {int dummy; } ;
struct sway_config {TYPE_1__* seat_configs; } ;
struct seat_config {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int length; struct seat_config** items; } ;

/* Variables and functions */
 struct sway_seat* input_manager_get_seat (int /*<<< orphan*/ ,int) ; 
 scalar_t__ list_seq_find (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seat_destroy (struct sway_seat*) ; 
 int /*<<< orphan*/  seat_name_cmp ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void destroy_removed_seats(struct sway_config *old_config,
		struct sway_config *new_config) {
	struct seat_config *seat_config;
	struct sway_seat *seat;
	int i;
	for (i = 0; i < old_config->seat_configs->length; i++) {
		seat_config = old_config->seat_configs->items[i];
		// Skip the wildcard seat config, it won't have a matching real seat.
		if (strcmp(seat_config->name, "*") == 0) {
			continue;
		}

		/* Also destroy seats that aren't present in new config */
		if (new_config && list_seq_find(new_config->seat_configs,
				seat_name_cmp, seat_config->name) < 0) {
			seat = input_manager_get_seat(seat_config->name, false);
			if (seat) {
				seat_destroy(seat);
			}
		}
	}
}