#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ mode; } ;
struct TYPE_4__ {char* rev; char* name; int /*<<< orphan*/  mode; } ;
struct status {unsigned char status; TYPE_2__ new; TYPE_1__ old; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;
struct TYPE_6__ {int /*<<< orphan*/  exec_dir; } ;

/* Variables and functions */
 int LINE_STAT_STAGED ; 
 int LINE_STAT_UNSTAGED ; 
 int LINE_STAT_UNTRACKED ; 
 int io_run_fg (char const**,int /*<<< orphan*/ ) ; 
 scalar_t__ prompt_yesno (char*) ; 
 TYPE_3__ repo ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  string_format (char*,char*,int /*<<< orphan*/ ) ; 

bool
status_revert(struct status *status, enum line_type type, bool has_none)
{
	if (!status || type != LINE_STAT_UNSTAGED) {
		if (type == LINE_STAT_STAGED) {
			report("Cannot revert changes to staged files");
		} else if (type == LINE_STAT_UNTRACKED) {
			report("Cannot revert changes to untracked files");
		} else if (has_none) {
			report("Nothing to revert");
		} else {
			report("Cannot revert changes to multiple files");
		}

	} else if (prompt_yesno("Are you sure you want to revert changes?")) {
		char mode[10] = "100644";
		const char *reset_argv[] = {
			"git", "update-index", "--cacheinfo", mode,
				status->old.rev, status->old.name, NULL
		};
		const char *checkout_argv[] = {
			"git", "checkout", "--", status->old.name, NULL
		};

		if (status->status == 'U') {
			string_format(mode, "%5o", status->old.mode);

			if (status->old.mode == 0 && status->new.mode == 0) {
				reset_argv[2] = "--force-remove";
				reset_argv[3] = status->old.name;
				reset_argv[4] = NULL;
			}

			if (!io_run_fg(reset_argv, repo.exec_dir))
				return false;
			if (status->old.mode == 0 && status->new.mode == 0)
				return true;
		}

		return io_run_fg(checkout_argv, repo.exec_dir);
	}

	return false;
}