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
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
#define  IPC_COMMAND 132 
 int IPC_GET_CONFIG ; 
#define  IPC_GET_INPUTS 131 
#define  IPC_GET_OUTPUTS 130 
#define  IPC_GET_SEATS 129 
 int IPC_GET_VERSION ; 
#define  IPC_GET_WORKSPACES 128 
 int IPC_SEND_TICK ; 
 int JSON_C_TO_STRING_PRETTY ; 
 int JSON_C_TO_STRING_SPACED ; 
 int /*<<< orphan*/ * json_object_array_get_idx (int /*<<< orphan*/ *,size_t) ; 
 size_t json_object_array_length (int /*<<< orphan*/ *) ; 
 char* json_object_to_json_string_ext (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pretty_print_cmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pretty_print_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pretty_print_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pretty_print_output (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pretty_print_seat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pretty_print_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pretty_print_workspace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void pretty_print(int type, json_object *resp) {
	if (type != IPC_COMMAND && type != IPC_GET_WORKSPACES &&
			type != IPC_GET_INPUTS && type != IPC_GET_OUTPUTS &&
			type != IPC_GET_VERSION && type != IPC_GET_SEATS &&
			type != IPC_GET_CONFIG && type != IPC_SEND_TICK) {
		printf("%s\n", json_object_to_json_string_ext(resp,
			JSON_C_TO_STRING_PRETTY | JSON_C_TO_STRING_SPACED));
		return;
	}

	if (type == IPC_SEND_TICK) {
		return;
	}

	if (type == IPC_GET_VERSION) {
		pretty_print_version(resp);
		return;
	}

	if (type == IPC_GET_CONFIG) {
		pretty_print_config(resp);
		return;
	}

	json_object *obj;
	size_t len = json_object_array_length(resp);
	for (size_t i = 0; i < len; ++i) {
		obj = json_object_array_get_idx(resp, i);
		switch (type) {
		case IPC_COMMAND:
			pretty_print_cmd(obj);
			break;
		case IPC_GET_WORKSPACES:
			pretty_print_workspace(obj);
			break;
		case IPC_GET_INPUTS:
			pretty_print_input(obj);
			break;
		case IPC_GET_OUTPUTS:
			pretty_print_output(obj);
			break;
		case IPC_GET_SEATS:
			pretty_print_seat(obj);
			break;
		}
	}
}