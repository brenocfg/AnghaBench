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
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 int error (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  io_fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  save_option_colors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_option_keybindings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_option_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

enum status_code
save_options(const char *path)
{
	int fd = open(path, O_WRONLY | O_CREAT | O_EXCL, 0666);
	FILE *file = fd != -1 ? fdopen(fd, "w") : NULL;
	enum status_code code = SUCCESS;

	if (!file)
		return error("%s", strerror(errno));

	if (!io_fprintf(file, "%s", "# Saved by Tig\n")
	    || !save_option_settings(file)
	    || !save_option_keybindings(file)
	    || !save_option_colors(file))
		code = error("Write returned an error");

	fclose(file);
	return code;
}