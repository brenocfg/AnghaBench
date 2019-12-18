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
struct view {int dummy; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_2__ {scalar_t__* search; } ;

/* Variables and functions */
 int REQ_SEARCH ; 
 TYPE_1__ argv_env ; 
 int /*<<< orphan*/  find_next (struct view*,int) ; 
 int /*<<< orphan*/  get_status_message (int) ; 
 char* read_prompt (char const*) ; 
 int /*<<< orphan*/  report (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_clear () ; 
 int setup_and_find_next (struct view*,int) ; 
 int /*<<< orphan*/  string_ncopy (scalar_t__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void
search_view(struct view *view, enum request request)
{
	const char *prompt = request == REQ_SEARCH ? "/" : "?";
	char *search = read_prompt(prompt);

	if (search && *search) {
		enum status_code code;

		string_ncopy(argv_env.search, search, strlen(search));
		code = setup_and_find_next(view, request);
		report("%s", get_status_message(code));
	} else if (search && *argv_env.search) {
		find_next(view, request);
	} else {
		report_clear();
	}
}