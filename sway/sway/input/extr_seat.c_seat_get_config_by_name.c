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
struct seat_config {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__* seat_configs; } ;
struct TYPE_3__ {int length; struct seat_config** items; } ;

/* Variables and functions */
 TYPE_2__* config ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

struct seat_config *seat_get_config_by_name(const char *name) {
	struct seat_config *seat_config = NULL;
	for (int i = 0; i < config->seat_configs->length; ++i ) {
		seat_config = config->seat_configs->items[i];
		if (strcmp(name, seat_config->name) == 0) {
			return seat_config;
		}
	}

	return NULL;
}