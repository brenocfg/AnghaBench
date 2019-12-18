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
struct sway_seat {TYPE_1__* wlr_seat; } ;
struct seat_config {int fallback; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  input_has_seat_fallback_configuration () ; 
 int /*<<< orphan*/  input_manager_apply_seat_config (struct seat_config*) ; 
 struct sway_seat* input_manager_get_default_seat () ; 
 struct seat_config* new_seat_config (int /*<<< orphan*/ ) ; 
 struct seat_config* store_seat_config (struct seat_config*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

void input_manager_verify_fallback_seat(void) {
	struct sway_seat *seat = NULL;
	if (!input_has_seat_fallback_configuration()) {
		sway_log(SWAY_DEBUG, "no fallback seat config - creating default");
		seat = input_manager_get_default_seat();
		struct seat_config *sc = new_seat_config(seat->wlr_seat->name);
		sc->fallback = true;
		sc = store_seat_config(sc);
		input_manager_apply_seat_config(sc);
	}
}