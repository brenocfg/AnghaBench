#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dirent {char* d_name; } ;
struct TYPE_5__ {char* curdir; int selected; size_t count; TYPE_1__* files; scalar_t__ (* filter ) (char*) ;int /*<<< orphan*/  input_dir; } ;
struct TYPE_4__ {int is_dir; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmp_entry ; 
 int /*<<< orphan*/  ctx ; 
 TYPE_3__ fc ; 
 int fz_is_directory (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  fz_strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ nelem (TYPE_1__*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  qsort (TYPE_1__*,size_t,int,int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  realpath (char const*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ stub1 (char*) ; 
 int /*<<< orphan*/  ui_input_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void load_dir(const char *path)
{
	char buf[PATH_MAX];
	DIR *dir;
	struct dirent *dp;

	realpath(path, fc.curdir);
	if (!fz_is_directory(ctx, fc.curdir))
		return;

	ui_input_init(&fc.input_dir, fc.curdir);

	fc.selected = -1;
	fc.count = 0;
	dir = opendir(fc.curdir);
	if (!dir)
	{
		fc.files[fc.count].is_dir = 1;
		fz_strlcpy(fc.files[fc.count].name, "..", FILENAME_MAX);
		++fc.count;
	}
	else
	{
		while ((dp = readdir(dir)) && fc.count < (int)nelem(fc.files))
		{
			/* skip hidden files */
			if (dp->d_name[0] == '.' && strcmp(dp->d_name, ".") && strcmp(dp->d_name, ".."))
				continue;
			fz_snprintf(buf, sizeof buf, "%s/%s", fc.curdir, dp->d_name);
			fc.files[fc.count].is_dir = fz_is_directory(ctx, buf);
			if (fc.files[fc.count].is_dir || !fc.filter || fc.filter(buf))
			{
				fz_strlcpy(fc.files[fc.count].name, dp->d_name, FILENAME_MAX);
				++fc.count;
			}
		}
		closedir(dir);
	}

	qsort(fc.files, fc.count, sizeof fc.files[0], cmp_entry);
}