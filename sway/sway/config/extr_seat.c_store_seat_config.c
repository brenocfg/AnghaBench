#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seat_config {char* name; } ;
struct TYPE_5__ {TYPE_1__* seat_configs; } ;
struct TYPE_4__ {struct seat_config** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  free_seat_config (struct seat_config*) ; 
 int /*<<< orphan*/  list_add (TYPE_1__*,struct seat_config*) ; 
 int list_seq_find (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  merge_seat_config (struct seat_config*,struct seat_config*) ; 
 int /*<<< orphan*/  merge_wildcard_on_all (struct seat_config*) ; 
 struct seat_config* new_seat_config (char*) ; 
 int /*<<< orphan*/  seat_name_cmp ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 

struct seat_config *store_seat_config(struct seat_config *sc) {
	bool wildcard = strcmp(sc->name, "*") == 0;
	if (wildcard) {
		merge_wildcard_on_all(sc);
	}

	int i = list_seq_find(config->seat_configs, seat_name_cmp, sc->name);
	if (i >= 0) {
		sway_log(SWAY_DEBUG, "Merging on top of existing seat config");
		struct seat_config *current = config->seat_configs->items[i];
		merge_seat_config(current, sc);
		free_seat_config(sc);
		sc = current;
	} else if (!wildcard) {
		sway_log(SWAY_DEBUG, "Adding non-wildcard seat config");
		i = list_seq_find(config->seat_configs, seat_name_cmp, "*");
		if (i >= 0) {
			sway_log(SWAY_DEBUG, "Merging on top of seat * config");
			struct seat_config *current = new_seat_config(sc->name);
			merge_seat_config(current, config->seat_configs->items[i]);
			merge_seat_config(current, sc);
			free_seat_config(sc);
			sc = current;
		}
		list_add(config->seat_configs, sc);
	} else {
		// New wildcard config. Just add it
		sway_log(SWAY_DEBUG, "Adding seat * config");
		list_add(config->seat_configs, sc);
	}

	sway_log(SWAY_DEBUG, "Config stored for seat %s", sc->name);

	return sc;
}