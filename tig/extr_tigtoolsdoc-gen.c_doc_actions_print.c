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
struct doc_action_iterator {int member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  doc_action_print ; 
 int /*<<< orphan*/  doc_action_table_print (int) ; 
 int /*<<< orphan*/  foreach_request (int /*<<< orphan*/ ,struct doc_action_iterator*) ; 

__attribute__((used)) static void
doc_actions_print(void)
{
	struct doc_action_iterator iterator = { false };

	foreach_request(doc_action_print, &iterator);
	doc_action_table_print(false);
}