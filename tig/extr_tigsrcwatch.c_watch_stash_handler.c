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
struct watch_handler {int /*<<< orphan*/  last_modified; } ;
typedef  enum watch_trigger { ____Placeholder_watch_trigger } watch_trigger ;
typedef  enum watch_event { ____Placeholder_watch_event } watch_event ;
struct TYPE_2__ {int /*<<< orphan*/  git_dir; } ;

/* Variables and functions */
 int WATCH_NONE ; 
 int WATCH_STASH ; 
 scalar_t__ check_file_mtime (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ repo ; 

__attribute__((used)) static enum watch_trigger
watch_stash_handler(struct watch_handler *handler, enum watch_event event, enum watch_trigger check)
{
	if (check_file_mtime(&handler->last_modified, "%s/refs/stash", repo.git_dir))
		return WATCH_STASH;

	return WATCH_NONE;
}