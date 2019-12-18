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
 scalar_t__ json_object_is_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_type_array ; 
 int /*<<< orphan*/  json_type_object ; 
 int success_object (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool success(json_object *r, bool fallback) {
	if (!json_object_is_type(r, json_type_array)) {
		if (json_object_is_type(r, json_type_object)) {
			return success_object(r);
		}
		return fallback;
	}

	size_t results_len = json_object_array_length(r);
	if (!results_len) {
		return fallback;
	}

	for (size_t i = 0; i < results_len; ++i) {
		json_object *result = json_object_array_get_idx(r, i);

		if (!success_object(result)) {
			return false;
		}
	}

	return true;
}