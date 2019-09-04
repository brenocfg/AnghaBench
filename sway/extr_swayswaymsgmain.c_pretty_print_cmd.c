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
 char* json_object_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_object_get_ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  success_object (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pretty_print_cmd(json_object *r) {
	if (!success_object(r)) {
		json_object *error;
		if (!json_object_object_get_ex(r, "error", &error)) {
			printf("An unknkown error occurred");
		} else {
			printf("Error: %s\n", json_object_get_string(error));
		}
	}
}