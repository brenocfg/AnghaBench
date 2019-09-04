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
struct request_info {int /*<<< orphan*/  request; } ;
struct key_visitor_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_NONE ; 
 int foreach_key_visit (struct key_visitor_state*,char const*,int /*<<< orphan*/ ,struct request_info const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
foreach_key_request(void *data, const struct request_info *req_info, const char *group)
{
	struct key_visitor_state *state = data;

	if (req_info->request == REQ_NONE)
		return true;

	return foreach_key_visit(state, group, req_info->request, req_info, NULL);
}