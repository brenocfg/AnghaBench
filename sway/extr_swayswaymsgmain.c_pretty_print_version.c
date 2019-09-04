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
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void pretty_print_version(json_object *v) {
	json_object *ver;
	json_object_object_get_ex(v, "human_readable", &ver);
	printf("sway version %s\n", json_object_get_string(ver));
}