#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct view {int /*<<< orphan*/  watch; int /*<<< orphan*/  env; } ;
struct TYPE_3__ {scalar_t__ internal; scalar_t__ exit; scalar_t__ confirm; int /*<<< orphan*/  quick; int /*<<< orphan*/  echo; int /*<<< orphan*/  silent; } ;
struct run_request {TYPE_1__ flags; int /*<<< orphan*/  argv; } ;
typedef  enum request { ____Placeholder_request } request ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {int /*<<< orphan*/  cdup; } ;

/* Variables and functions */
 int REQ_NONE ; 
 int REQ_QUIT ; 
 int REQ_REFRESH ; 
 int SIZEOF_ARG ; 
 int SIZEOF_MED_STR ; 
 int SIZEOF_STR ; 
 int /*<<< orphan*/  argv_format (int /*<<< orphan*/ ,char const***,char const**,int,int) ; 
 int /*<<< orphan*/  argv_free (char const**) ; 
 int /*<<< orphan*/  argv_from_string_no_quotes (char const**,int*,char*) ; 
 int /*<<< orphan*/  argv_to_string (int /*<<< orphan*/ ,char*,int,char*) ; 
 scalar_t__ argv_to_string_quoted (char const**,char*,int,char*) ; 
 int /*<<< orphan*/  free (char const**) ; 
 int /*<<< orphan*/  open_external_viewer (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ prompt_yesno (char*) ; 
 TYPE_2__ repo ; 
 int /*<<< orphan*/  report (char*) ; 
 int run_prompt_command (struct view*,char const**) ; 
 scalar_t__ string_format (char*,char*,char*,char const*) ; 
 scalar_t__ watch_dirty (int /*<<< orphan*/ *) ; 

enum request
exec_run_request(struct view *view, struct run_request *req)
{
	const char **argv = NULL;
	bool confirmed = false;
	enum request request = REQ_NONE;
	char cmd[SIZEOF_MED_STR];
	const char *req_argv[SIZEOF_ARG];
	int req_argc = 0;

	if (!argv_to_string(req->argv, cmd, sizeof(cmd), " ")
	    || !argv_from_string_no_quotes(req_argv, &req_argc, cmd)
	    || !argv_format(view->env, &argv, req_argv, false, true)
	    || !argv) {
		report("Failed to format arguments");
		return REQ_NONE;
	}

	if (req->flags.internal) {
		request = run_prompt_command(view, argv);

	} else {
		confirmed = !req->flags.confirm;

		if (req->flags.confirm) {
			char cmd[SIZEOF_STR], prompt[SIZEOF_STR];
			const char *and_exit = req->flags.exit ? " and exit" : "";

			if (argv_to_string_quoted(argv, cmd, sizeof(cmd), " ") &&
			    string_format(prompt, "Run `%s`%s?", cmd, and_exit) &&
			    prompt_yesno(prompt)) {
				confirmed = true;
			}
		}

		if (confirmed)
			open_external_viewer(argv, repo.cdup, req->flags.silent,
					     !req->flags.exit, req->flags.echo, req->flags.quick, false, "");
	}

	if (argv)
		argv_free(argv);
	free(argv);

	if (request == REQ_NONE) {
		if (req->flags.confirm && !confirmed)
			request = REQ_NONE;

		else if (req->flags.exit)
			request = REQ_QUIT;

		else if (!req->flags.internal && watch_dirty(&view->watch))
			request = REQ_REFRESH;

	}

	return request;
}