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
struct TYPE_2__ {int (* filter ) (char const*) ;int /*<<< orphan*/  input_file; } ;

/* Variables and functions */
 int PATH_MAX ; 
 TYPE_1__ fc ; 
 int /*<<< orphan*/  fz_cleanname (char*) ; 
 int /*<<< orphan*/  fz_strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  load_dir (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  ui_input_init (int /*<<< orphan*/ *,char*) ; 

void ui_init_save_file(const char *path, int (*filter)(const char *fn))
{
	char dir[PATH_MAX], *p;
	fc.filter = filter;
	fz_strlcpy(dir, path, sizeof dir);
	for (p=dir; *p; ++p)
		if (*p == '\\') *p = '/';
	fz_cleanname(dir);
	p = strrchr(dir, '/');
	if (p)
	{
		*p = 0;
		load_dir(dir);
		ui_input_init(&fc.input_file, p+1);
	}
	else
	{
		load_dir(".");
		ui_input_init(&fc.input_file, dir);
	}
}