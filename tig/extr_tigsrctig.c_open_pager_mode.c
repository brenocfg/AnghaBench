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
typedef  enum request { ____Placeholder_request } request ;

/* Variables and functions */
 int /*<<< orphan*/  OPEN_FORWARD_STDIN ; 
 int /*<<< orphan*/  OPEN_STDIN ; 
 int REQ_NONE ; 
 int REQ_VIEW_DIFF ; 
 int REQ_VIEW_PAGER ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 scalar_t__ argv_contains (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_diff_view (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_main_view (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_pager_view (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_cmdline_args ; 
 int /*<<< orphan*/  opt_rev_args ; 
 int /*<<< orphan*/  report (char*) ; 

__attribute__((used)) static enum request
open_pager_mode(enum request request)
{
	if (request == REQ_VIEW_PAGER) {
		/* Detect if the user requested the main view. */
		if (argv_contains(opt_rev_args, "--stdin")) {
			open_main_view(NULL, OPEN_FORWARD_STDIN);
		} else if (argv_contains(opt_cmdline_args, "--pretty=raw")) {
			open_main_view(NULL, OPEN_STDIN);
		} else {
			open_pager_view(NULL, OPEN_STDIN);
		}

	} else if (request == REQ_VIEW_DIFF) {
		if (argv_contains(opt_rev_args, "--stdin"))
			open_diff_view(NULL, OPEN_FORWARD_STDIN);
		else
			open_diff_view(NULL, OPEN_STDIN);

	} else {
		close(STDIN_FILENO);
		report("Ignoring stdin.");
		return request;
	}

	return REQ_NONE;
}