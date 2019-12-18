#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ zpc_recursive; scalar_t__ zpc_ignore_noent; } ;
typedef  TYPE_1__ zfs_project_control_t ;
struct dirent {char const* d_name; scalar_t__ d_type; } ;
typedef  int /*<<< orphan*/  list_t ;
typedef  int /*<<< orphan*/  fullname ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ B_TRUE ; 
 scalar_t__ DT_DIR ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strerror (int) ; 
 int strlen (char const*) ; 
 int zfs_project_handle_one (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_project_item_alloc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
zfs_project_handle_dir(const char *name, zfs_project_control_t *zpc,
    list_t *head)
{
	char fullname[PATH_MAX];
	struct dirent *ent;
	DIR *dir;
	int ret = 0;

	dir = opendir(name);
	if (dir == NULL) {
		if (errno == ENOENT && zpc->zpc_ignore_noent)
			return (0);

		ret = -errno;
		(void) fprintf(stderr, gettext("failed to opendir %s: %s\n"),
		    name, strerror(errno));
		return (ret);
	}

	/* Non-top item, ignore the case of being removed or renamed by race. */
	zpc->zpc_ignore_noent = B_TRUE;
	errno = 0;
	while (!ret && (ent = readdir(dir)) != NULL) {
		/* skip "." and ".." */
		if (strcmp(ent->d_name, ".") == 0 ||
		    strcmp(ent->d_name, "..") == 0)
			continue;

		if (strlen(ent->d_name) + strlen(name) >=
		    sizeof (fullname) + 1) {
			errno = ENAMETOOLONG;
			break;
		}

		sprintf(fullname, "%s/%s", name, ent->d_name);
		ret = zfs_project_handle_one(fullname, zpc);
		if (!ret && zpc->zpc_recursive && ent->d_type == DT_DIR)
			zfs_project_item_alloc(head, fullname);
	}

	if (errno && !ret) {
		ret = -errno;
		(void) fprintf(stderr, gettext("failed to readdir %s: %s\n"),
		    name, strerror(errno));
	}

	closedir(dir);
	return (ret);
}