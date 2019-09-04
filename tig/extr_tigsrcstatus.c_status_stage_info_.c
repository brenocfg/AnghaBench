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
struct TYPE_2__ {char* name; } ;
struct status {int /*<<< orphan*/  status; TYPE_1__ new; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
#define  LINE_HEADER 131 
#define  LINE_STAT_STAGED 130 
#define  LINE_STAT_UNSTAGED 129 
#define  LINE_STAT_UNTRACKED 128 
 int string_nformat (char*,size_t,int /*<<< orphan*/ *,char const*,char const*) ; 

bool
status_stage_info_(char *buf, size_t bufsize,
		   enum line_type type, struct status *status)
{
	const char *file = status ? status->new.name : "";
	const char *info;

	switch (type) {
	case LINE_STAT_STAGED:
		if (status && status->status)
			info = "Staged changes to %s";
		else
			info = "Staged changes";
		break;

	case LINE_STAT_UNSTAGED:
		if (status && status->status)
			info = "Unstaged changes to %s";
		else
			info = "Unstaged changes";
		break;

	case LINE_STAT_UNTRACKED:
		info = "Untracked file %s";
		break;

	case LINE_HEADER:
	default:
		info = "";
	}

	return string_nformat(buf, bufsize, NULL, info, file);
}