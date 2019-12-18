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
struct view {int /*<<< orphan*/  private; int /*<<< orphan*/  lines; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;

/* Variables and functions */
 int OPEN_PREPARED ; 
 int /*<<< orphan*/  REQ_PROMPT ; 
 int SUCCESS ; 
 int begin_update (struct view*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int diff_init_highlight (struct view*,int /*<<< orphan*/ ) ; 
 int error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_view_key (struct view*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_from_stdin (int) ; 

__attribute__((used)) static enum status_code
pager_open(struct view *view, enum open_flags flags)
{
	enum status_code code;

	if (!open_from_stdin(flags) && !view->lines && !(flags & OPEN_PREPARED))
		return error("No pager content, press %s to run command from prompt",
			     get_view_key(view, REQ_PROMPT));

	code = begin_update(view, NULL, NULL, flags);
	if (code != SUCCESS)
		return code;

	return diff_init_highlight(view, view->private);
}