#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int internal; } ;
struct run_request {int /*<<< orphan*/ * argv; struct keymap* keymap; TYPE_1__ flags; } ;
struct keymap {int dummy; } ;
struct key_visitor_state {struct keymap* keymap; } ;
typedef  enum request { ____Placeholder_request } request ;

/* Variables and functions */
 int REQ_RUN_REQUESTS ; 
 int /*<<< orphan*/  foreach_key_visit (struct key_visitor_state*,char const*,int,int /*<<< orphan*/ *,struct run_request*) ; 
 char* get_keys (struct keymap*,int,int) ; 
 struct run_request* get_run_request (int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
foreach_key_run_request(struct key_visitor_state *state, bool internal, bool toggles)
{
	struct keymap *keymap = state->keymap;
	const char *group = !internal ?	"External commands:" :
			    toggles ?	"Option toggling:" :
					"Internal commands:";
	enum request request = REQ_RUN_REQUESTS + 1;

	for (; true; request++) {
		struct run_request *req = get_run_request(request);
		const char *key;

		if (!req)
			break;

		if (req->flags.internal != !!internal ||
		    req->keymap != keymap ||
		    !*(key = get_keys(keymap, request, true)))
			continue;

		if (toggles != !strcmp(req->argv[0], "toggle"))
			continue;

		if (!foreach_key_visit(state, group, request, NULL, req))
			return false;
	}

	return true;
}