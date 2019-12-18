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
struct key_visitor_state {void* member_1; int member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  key_visitor_fn ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  foreach_key_request ; 
 int /*<<< orphan*/  foreach_key_run_request (struct key_visitor_state*,int,int) ; 
 int /*<<< orphan*/  foreach_request (int /*<<< orphan*/ ,struct key_visitor_state*) ; 
 int /*<<< orphan*/ * keymaps ; 

bool
foreach_key(key_visitor_fn visitor, void *data, bool combine_keys)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(keymaps); i++) {
		struct key_visitor_state state = { visitor, data, &keymaps[i], combine_keys };

		if (!foreach_request(foreach_key_request, &state)
		    || !foreach_key_run_request(&state, true, true)
		    || !foreach_key_run_request(&state, true, false)
		    || !foreach_key_run_request(&state, false, false))
			return false;
	}

	return true;
}