#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sway_switch_binding {scalar_t__ type; scalar_t__ state; int flags; int /*<<< orphan*/  command; } ;
struct sway_switch {scalar_t__ type; scalar_t__ state; TYPE_1__* seat_device; } ;
struct sway_seat {int /*<<< orphan*/ * exclusive_client; } ;
struct sway_binding {int flags; int /*<<< orphan*/  command; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int length; struct sway_switch_binding** items; } ;
typedef  TYPE_3__ list_t ;
struct TYPE_8__ {scalar_t__ reloading; TYPE_2__* current_mode; } ;
struct TYPE_6__ {TYPE_3__* switch_bindings; } ;
struct TYPE_5__ {struct sway_seat* sway_seat; } ;

/* Variables and functions */
 int BINDING_LOCKED ; 
 int BINDING_RELOAD ; 
 int /*<<< orphan*/  BINDING_SWITCH ; 
 scalar_t__ WLR_SWITCH_STATE_TOGGLE ; 
 struct sway_binding* calloc (int,int) ; 
 TYPE_4__* config ; 
 int /*<<< orphan*/  free (struct sway_binding*) ; 
 int /*<<< orphan*/  seat_execute_command (struct sway_seat*,struct sway_binding*) ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 

__attribute__((used)) static void execute_binding(struct sway_switch *sway_switch) {
	struct sway_seat* seat = sway_switch->seat_device->sway_seat;
	bool input_inhibited = seat->exclusive_client != NULL;

	list_t *bindings = config->current_mode->switch_bindings;
	struct sway_switch_binding *matched_binding = NULL;
	for (int i = 0; i < bindings->length; ++i) {
		struct sway_switch_binding *binding = bindings->items[i];
		if (binding->type != sway_switch->type) {
			continue;
		}
		if (binding->state != WLR_SWITCH_STATE_TOGGLE &&
				binding->state != sway_switch->state) {
			continue;
		}
		if (config->reloading && (binding->state == WLR_SWITCH_STATE_TOGGLE
				|| (binding->flags & BINDING_RELOAD) == 0)) {
			continue;
		}
		bool binding_locked = binding->flags & BINDING_LOCKED;
		if (!binding_locked && input_inhibited) {
			continue;
		}

		matched_binding = binding;

		if (binding_locked == input_inhibited) {
			break;
		}
	}

	if (matched_binding) {
		struct sway_binding *dummy_binding =
			calloc(1, sizeof(struct sway_binding));
		dummy_binding->type = BINDING_SWITCH;
		dummy_binding->flags = matched_binding->flags;
		dummy_binding->command = matched_binding->command;

		seat_execute_command(seat, dummy_binding);
		free(dummy_binding);
	}

	transaction_commit_dirty();

}