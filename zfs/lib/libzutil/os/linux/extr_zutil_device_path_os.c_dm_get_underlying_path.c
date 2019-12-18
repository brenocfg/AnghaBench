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
struct dirent {scalar_t__ d_type; char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 char* realpath (char const*,int /*<<< orphan*/ *) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static char *
dm_get_underlying_path(const char *dm_name)
{
	DIR *dp = NULL;
	struct dirent *ep;
	char *realp;
	char *tmp = NULL;
	char *path = NULL;
	char *dev_str;
	int size;

	if (dm_name == NULL)
		return (NULL);

	/* dm name may be a symlink (like /dev/disk/by-vdev/A0) */
	realp = realpath(dm_name, NULL);
	if (realp == NULL)
		return (NULL);

	/*
	 * If they preface 'dev' with a path (like "/dev") then strip it off.
	 * We just want the 'dm-N' part.
	 */
	tmp = strrchr(realp, '/');
	if (tmp != NULL)
		dev_str = tmp + 1;    /* +1 since we want the chr after '/' */
	else
		dev_str = tmp;

	size = asprintf(&tmp, "/sys/block/%s/slaves/", dev_str);
	if (size == -1 || !tmp)
		goto end;

	dp = opendir(tmp);
	if (dp == NULL)
		goto end;

	/* Return first sd* entry in /sys/block/dm-N/slaves/ */
	while ((ep = readdir(dp))) {
		if (ep->d_type != DT_DIR) {	/* skip "." and ".." dirs */
			size = asprintf(&path, "/dev/%s", ep->d_name);
			break;
		}
	}

end:
	if (dp != NULL)
		closedir(dp);
	free(tmp);
	free(realp);
	return (path);
}