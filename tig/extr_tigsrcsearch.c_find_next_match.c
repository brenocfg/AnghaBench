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
struct view {int /*<<< orphan*/ * grep; int /*<<< orphan*/  matched_lines; TYPE_1__* env; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_2__ {int /*<<< orphan*/ * search; } ;

/* Variables and functions */
 int ERROR_OUT_OF_MEMORY ; 
#define  REQ_FIND_NEXT 131 
#define  REQ_FIND_PREV 130 
#define  REQ_SEARCH 129 
#define  REQ_SEARCH_BACK 128 
 int SUCCESS ; 
 int error (char*) ; 
 int /*<<< orphan*/  find_matches (struct view*) ; 
 int find_next_match_line (struct view*,int,int) ; 
 scalar_t__ opt_wrap_search ; 
 int setup_and_find_next (struct view*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int success (char*,...) ; 

__attribute__((used)) static enum status_code
find_next_match(struct view *view, enum request request)
{
	enum status_code code;
	int direction;

	if (!*view->grep || strcmp(view->grep, view->env->search)) {
		if (!*view->env->search)
			return success("No previous search");
		return setup_and_find_next(view, request);
	}

	switch (request) {
	case REQ_SEARCH:
	case REQ_FIND_NEXT:
		direction = 1;
		break;

	case REQ_SEARCH_BACK:
	case REQ_FIND_PREV:
		direction = -1;
		break;

	default:
		return error("Unknown search request");
	}

	if (!view->matched_lines && !find_matches(view))
		return ERROR_OUT_OF_MEMORY;

	code = find_next_match_line(view, direction, false);
	if (code != SUCCESS && opt_wrap_search)
		code = find_next_match_line(view, direction, true);

	return code == SUCCESS ? code : success("No match found for '%s'", view->grep);
}