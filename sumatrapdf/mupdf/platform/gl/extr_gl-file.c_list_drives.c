#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct list {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int lineheight; } ;

/* Variables and functions */
 int PATH_MAX ; 
 TYPE_2__* common_dirs ; 
 char* getenv (char*) ; 
 scalar_t__ has_dir (char const*,char const*,int,char*,char*) ; 
 int /*<<< orphan*/  load_dir (char*) ; 
 int nelem (TYPE_2__*) ; 
 TYPE_1__ ui ; 
 int /*<<< orphan*/  ui_list_begin (struct list*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ui_list_end (struct list*) ; 
 scalar_t__ ui_list_item (struct list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void list_drives(void)
{
	static struct list drive_list;
	char dir[PATH_MAX], vis[PATH_MAX];
	const char *home = getenv("HOME");
	const char *user = getenv("USER");
	int i;

	ui_list_begin(&drive_list, nelem(common_dirs), 0, nelem(common_dirs) * ui.lineheight + 4);

	for (i = 0; i < (int)nelem(common_dirs); ++i)
		if (has_dir(home, user, i, dir, vis))
			if (ui_list_item(&drive_list, common_dirs[i].name, vis, 0))
				load_dir(dir);

	ui_list_end(&drive_list);
}