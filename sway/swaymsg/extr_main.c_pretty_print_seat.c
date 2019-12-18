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
 int /*<<< orphan*/ * json_object_array_get_idx (int /*<<< orphan*/ *,size_t) ; 
 size_t json_object_array_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_get_int (int /*<<< orphan*/ *) ; 
 char* json_object_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_object_get_ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  printf (char const*,...) ; 

__attribute__((used)) static void pretty_print_seat(json_object *i) {
	json_object *name, *capabilities, *devices;
	json_object_object_get_ex(i, "name", &name);
	json_object_object_get_ex(i, "capabilities", &capabilities);
	json_object_object_get_ex(i, "devices", &devices);

	const char *fmt =
		"Seat: %s\n"
		"  Capabilities: %d\n";

	printf(fmt, json_object_get_string(name),
		json_object_get_int(capabilities));

	size_t devices_len = json_object_array_length(devices);
	if (devices_len > 0) {
		printf("  Devices:\n");
		for (size_t i = 0; i < devices_len; ++i) {
			json_object *device = json_object_array_get_idx(devices, i);

			json_object *device_name;
			json_object_object_get_ex(device, "name", &device_name);

			printf("    %s\n", json_object_get_string(device_name));
		}
	}

	printf("\n");
}