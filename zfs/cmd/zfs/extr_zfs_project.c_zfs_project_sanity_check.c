#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ zpc_recursive; scalar_t__ zpc_dironly; } ;
typedef  TYPE_1__ zfs_project_control_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* gettext (char*) ; 
 int stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_project_sanity_check(const char *name, zfs_project_control_t *zpc,
    struct stat *st)
{
	int ret;

	ret = stat(name, st);
	if (ret) {
		(void) fprintf(stderr, gettext("failed to stat %s: %s\n"),
		    name, strerror(errno));
		return (ret);
	}

	if (!S_ISREG(st->st_mode) && !S_ISDIR(st->st_mode)) {
		(void) fprintf(stderr, gettext("only support project quota on "
		    "regular file or directory\n"));
		return (-1);
	}

	if (!S_ISDIR(st->st_mode)) {
		if (zpc->zpc_dironly) {
			(void) fprintf(stderr, gettext(
			    "'-d' option on non-dir target %s\n"), name);
			return (-1);
		}

		if (zpc->zpc_recursive) {
			(void) fprintf(stderr, gettext(
			    "'-r' option on non-dir target %s\n"), name);
			return (-1);
		}
	}

	return (0);
}