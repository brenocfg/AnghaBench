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
struct io {int dummy; } ;
struct file_finder_line {int dummy; } ;
struct file_finder {TYPE_2__** line; TYPE_2__** file; } ;
struct buffer {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  text; } ;
struct TYPE_4__ {int /*<<< orphan*/  exec_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_RD ; 
 TYPE_2__* calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  io_done (struct io*) ; 
 scalar_t__ io_error (struct io*) ; 
 scalar_t__ io_get (struct io*,struct buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  io_run (struct io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  realloc_file_array (TYPE_2__***,size_t,size_t) ; 
 TYPE_1__ repo ; 
 scalar_t__ string_rev_is_null (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
file_finder_read(struct file_finder *finder, const char *commit)
{
	const char *tree = string_rev_is_null(commit) ? "HEAD" : commit;
	const char *ls_tree_files_argv[] = {
		"git", "ls-tree", "-z", "-r", "--name-only", "--full-name",
			tree, NULL
	};
	struct buffer buf;
	struct io io;
	size_t files;
	bool ok = true;

	if (!io_run(&io, IO_RD, repo.exec_dir, NULL, ls_tree_files_argv))
		return false;

	for (files = 0; io_get(&io, &buf, 0, true); files++) {
		/* Alloc two to ensure NULL terminated array. */
		if (!realloc_file_array(&finder->file, files, 2)) {
			ok = false;
			break;
		}

		finder->file[files] = calloc(1, sizeof(struct file_finder_line) + buf.size);
		if (!finder->file[files]) {
			ok = false;
			break;
		}

		strncpy(finder->file[files]->text, buf.data, buf.size);
	}

	if (io_error(&io) || !realloc_file_array(&finder->line, 0, files + 1))
		ok = false;
	io_done(&io);
	return ok;
}