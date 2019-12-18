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
typedef  int /*<<< orphan*/  zfs_type_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct stat64 {int dummy; } ;
struct extmnttab {char* mnt_special; int /*<<< orphan*/  mnt_fstype; } ;
struct TYPE_4__ {int /*<<< orphan*/  libzfs_mnttab; } ;
typedef  TYPE_1__ libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MNTTAB ; 
 int /*<<< orphan*/  MNTTYPE_ZFS ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * freopen (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ getextmntent (char*,struct extmnttab*,struct stat64*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_open (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

zfs_handle_t *
zfs_path_to_zhandle(libzfs_handle_t *hdl, char *path, zfs_type_t argtype)
{
	struct stat64 statbuf;
	struct extmnttab entry;

	if (path[0] != '/' && strncmp(path, "./", strlen("./")) != 0) {
		/*
		 * It's not a valid path, assume it's a name of type 'argtype'.
		 */
		return (zfs_open(hdl, path, argtype));
	}

	/* Reopen MNTTAB to prevent reading stale data from open file */
	if (freopen(MNTTAB, "r", hdl->libzfs_mnttab) == NULL)
		return (NULL);

	if (getextmntent(path, &entry, &statbuf) != 0)
		return (NULL);

	if (strcmp(entry.mnt_fstype, MNTTYPE_ZFS) != 0) {
		(void) fprintf(stderr, gettext("'%s': not a ZFS filesystem\n"),
		    path);
		return (NULL);
	}

	return (zfs_open(hdl, entry.mnt_special, ZFS_TYPE_FILESYSTEM));
}