#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sway_server {int /*<<< orphan*/  wl_display; TYPE_2__* backend; } ;
struct TYPE_14__ {int /*<<< orphan*/  notify; } ;
struct sway_input_manager {TYPE_7__ inhibit_deactivate; TYPE_6__* inhibit; TYPE_7__ inhibit_activate; TYPE_7__ virtual_keyboard_new; TYPE_5__* virtual_keyboard; TYPE_7__ new_input; int /*<<< orphan*/  seats; int /*<<< orphan*/  devices; } ;
struct TYPE_11__ {int /*<<< orphan*/  deactivate; int /*<<< orphan*/  activate; } ;
struct TYPE_13__ {TYPE_4__ events; } ;
struct TYPE_10__ {int /*<<< orphan*/  new_virtual_keyboard; } ;
struct TYPE_12__ {TYPE_3__ events; } ;
struct TYPE_8__ {int /*<<< orphan*/  new_input; } ;
struct TYPE_9__ {TYPE_1__ events; } ;

/* Variables and functions */
 struct sway_input_manager* calloc (int,int) ; 
 int /*<<< orphan*/  handle_inhibit_activate ; 
 int /*<<< orphan*/  handle_inhibit_deactivate ; 
 int /*<<< orphan*/  handle_new_input ; 
 int /*<<< orphan*/  handle_virtual_keyboard ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_7__*) ; 
 TYPE_6__* wlr_input_inhibit_manager_create (int /*<<< orphan*/ ) ; 
 TYPE_5__* wlr_virtual_keyboard_manager_v1_create (int /*<<< orphan*/ ) ; 

struct sway_input_manager *input_manager_create(struct sway_server *server) {
	struct sway_input_manager *input =
		calloc(1, sizeof(struct sway_input_manager));
	if (!input) {
		return NULL;
	}

	wl_list_init(&input->devices);
	wl_list_init(&input->seats);

	input->new_input.notify = handle_new_input;
	wl_signal_add(&server->backend->events.new_input, &input->new_input);

	input->virtual_keyboard = wlr_virtual_keyboard_manager_v1_create(
		server->wl_display);
	wl_signal_add(&input->virtual_keyboard->events.new_virtual_keyboard,
		&input->virtual_keyboard_new);
	input->virtual_keyboard_new.notify = handle_virtual_keyboard;

	input->inhibit = wlr_input_inhibit_manager_create(server->wl_display);
	input->inhibit_activate.notify = handle_inhibit_activate;
	wl_signal_add(&input->inhibit->events.activate,
			&input->inhibit_activate);
	input->inhibit_deactivate.notify = handle_inhibit_deactivate;
	wl_signal_add(&input->inhibit->events.deactivate,
			&input->inhibit_deactivate);

	return input;
}