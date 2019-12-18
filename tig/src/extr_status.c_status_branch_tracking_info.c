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
struct io {int dummy; } ;
struct buffer {scalar_t__ size; char* data; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  exec_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_RD ; 
 int /*<<< orphan*/  io_done (struct io*) ; 
 int io_error (struct io*) ; 
 scalar_t__ io_get (struct io*,struct buffer*,char,int) ; 
 int /*<<< orphan*/  io_run (struct io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const**) ; 
 TYPE_1__ repo ; 
 int string_nformat (char*,size_t,int /*<<< orphan*/ *,char*,char const*,...) ; 

__attribute__((used)) static bool
status_branch_tracking_info(char *buf, size_t buf_len, const char *head,
			    const char *remote)
{
	if (!string_nformat(buf, buf_len, NULL, "%s...%s",
			    head, remote)) {
		return false;
	}

	const char *tracking_info_argv[] = {
		"git", "rev-list", "--left-right", buf, NULL
	};

	struct io io;

	if (!io_run(&io, IO_RD, repo.exec_dir, NULL, tracking_info_argv)) {
		return false;
	}

	struct buffer result = { 0 };
	int ahead = 0;
	int behind = 0;

	while (io_get(&io, &result, '\n', true)) {
		if (result.size > 0 && result.data) {
			if (result.data[0] == '<') {
				ahead++;
			} else if (result.data[0] == '>') {
				behind++;
			}
		}
	}

	bool io_failed = io_error(&io);
	io_done(&io);

	if (io_failed) {
		return false;
	}

	if (ahead == 0 && behind == 0) {
		return string_nformat(buf, buf_len, NULL,
				      "Your branch is up-to-date with '%s'.",
				      remote);
	} else if (ahead > 0 && behind > 0) {
		return string_nformat(buf, buf_len, NULL,
				      "Your branch and '%s' have diverged, "
				      "and have %d and %d different commits "
				      "each, respectively",
				      remote, ahead, behind);
	} else if (ahead > 0) {
		return string_nformat(buf, buf_len, NULL,
				      "Your branch is ahead of '%s' by "
				      "%d commit%s.", remote, ahead,
				      ahead > 1 ? "s" : "");
	} else if (behind > 0) {
		return string_nformat(buf, buf_len, NULL,
				      "Your branch is behind '%s' by "
				      "%d commit%s.", remote, behind,
				      behind > 1 ? "s" : "");
	}

	return false;
}