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
struct view {int /*<<< orphan*/  private; } ;
struct buffer {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int diff_common_read (struct view*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_done_highlight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_diff_highlight ; 
 int /*<<< orphan*/  report (char*,int /*<<< orphan*/ ) ; 

bool
pager_read(struct view *view, struct buffer *buf, bool force_stop)
{
	if (!buf) {
		if (!diff_done_highlight(view->private)) {
			report("Failed run the diff-highlight program: %s", opt_diff_highlight);
			return false;
		}

		return true;
	}

	return diff_common_read(view, buf->data, view->private);
}