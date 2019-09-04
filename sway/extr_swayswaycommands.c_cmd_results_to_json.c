#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cmd_results {scalar_t__ status; scalar_t__ error; } ;
struct TYPE_3__ {int length; struct cmd_results** items; } ;
typedef  TYPE_1__ list_t ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
 scalar_t__ CMD_INVALID ; 
 scalar_t__ CMD_SUCCESS ; 
 int /*<<< orphan*/  json_object_array_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_new_array () ; 
 int /*<<< orphan*/  json_object_new_boolean (int) ; 
 int /*<<< orphan*/ * json_object_new_object () ; 
 int /*<<< orphan*/  json_object_new_string (scalar_t__) ; 
 int /*<<< orphan*/  json_object_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_put (int /*<<< orphan*/ *) ; 
 char* json_object_to_json_string (int /*<<< orphan*/ *) ; 
 char* strdup (char const*) ; 

char *cmd_results_to_json(list_t *res_list) {
	json_object *result_array = json_object_new_array();
	for (int i = 0; i < res_list->length; ++i) {
		struct cmd_results *results = res_list->items[i];
		json_object *root = json_object_new_object();
		json_object_object_add(root, "success",
				json_object_new_boolean(results->status == CMD_SUCCESS));
		if (results->error) {
			json_object_object_add(root, "parse_error",
					json_object_new_boolean(results->status == CMD_INVALID));
			json_object_object_add(
					root, "error", json_object_new_string(results->error));
		}
		json_object_array_add(result_array, root);
	}
	const char *json = json_object_to_json_string(result_array);
	char *res = strdup(json);
	json_object_put(result_array);
	return res;
}