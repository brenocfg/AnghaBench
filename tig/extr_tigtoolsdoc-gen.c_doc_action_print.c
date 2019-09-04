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
struct request_info {char* help; int /*<<< orphan*/  name; } ;
struct doc_action_iterator {char const* group; int end_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  doc_action_group_name_print (char const*) ; 
 int /*<<< orphan*/  doc_action_table_print (int) ; 
 char* enum_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static bool
doc_action_print(void *data, const struct request_info *req_info, const char *group)
{
	struct doc_action_iterator *iterator = data;

	if (iterator->group != group) {
		if (iterator->end_group) {
			doc_action_table_print(false);
			printf("\n");
		}

		doc_action_group_name_print(group);
		doc_action_table_print(true);

		iterator->group = group;
		iterator->end_group = true;
	}

	printf("|%-24s|%s\n", enum_name(req_info->name), req_info->help);
	return true;
}