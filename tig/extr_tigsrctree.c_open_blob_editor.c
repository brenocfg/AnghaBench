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

/* Variables and functions */
 int SIZEOF_STR ; 
 int /*<<< orphan*/  get_temp_dir () ; 
 int /*<<< orphan*/  io_run_append (char const**,int) ; 
 int mkstemps (char*,scalar_t__) ; 
 int /*<<< orphan*/  open_editor (char*,unsigned int) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  string_format (char*,char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void
open_blob_editor(const char *id, const char *name, unsigned int lineno)
{
	const char *blob_argv[] = { "git", "cat-file", "blob", id, NULL };
	char file[SIZEOF_STR];
	int fd;

	if (!name)
		name = "unknown";

	if (!string_format(file, "%s/tigblob.XXXXXX.%s", get_temp_dir(), name)) {
		report("Temporary file name is too long");
		return;
	}

	fd = mkstemps(file, strlen(name) + 1);

	if (fd == -1)
		report("Failed to create temporary file");
	else if (!io_run_append(blob_argv, fd))
		report("Failed to save blob data to file");
	else
		open_editor(file, lineno);
	if (fd != -1)
		unlink(file);
}