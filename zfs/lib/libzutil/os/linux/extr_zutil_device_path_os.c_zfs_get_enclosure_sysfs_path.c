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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int asprintf (char**,char*,char const*,...) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 size_t readlink (char*,char*,int) ; 
 char* strrchr (char const*,char) ; 
 char* strstr (char*,char*) ; 

char *
zfs_get_enclosure_sysfs_path(const char *dev_name)
{
	DIR *dp = NULL;
	struct dirent *ep;
	char buf[MAXPATHLEN];
	char *tmp1 = NULL;
	char *tmp2 = NULL;
	char *tmp3 = NULL;
	char *path = NULL;
	size_t size;
	int tmpsize;

	if (dev_name == NULL)
		return (NULL);

	/* If they preface 'dev' with a path (like "/dev") then strip it off */
	tmp1 = strrchr(dev_name, '/');
	if (tmp1 != NULL)
		dev_name = tmp1 + 1;    /* +1 since we want the chr after '/' */

	tmpsize = asprintf(&tmp1, "/sys/block/%s/device", dev_name);
	if (tmpsize == -1 || tmp1 == NULL) {
		tmp1 = NULL;
		goto end;
	}

	dp = opendir(tmp1);
	if (dp == NULL) {
		tmp1 = NULL;	/* To make free() at the end a NOP */
		goto end;
	}

	/*
	 * Look though all sysfs entries in /sys/block/<dev>/device for
	 * the enclosure symlink.
	 */
	while ((ep = readdir(dp))) {
		/* Ignore everything that's not our enclosure_device link */
		if (strstr(ep->d_name, "enclosure_device") == NULL)
			continue;

		if (asprintf(&tmp2, "%s/%s", tmp1, ep->d_name) == -1 ||
		    tmp2 == NULL)
			break;

		size = readlink(tmp2, buf, sizeof (buf));

		/* Did readlink fail or crop the link name? */
		if (size == -1 || size >= sizeof (buf)) {
			free(tmp2);
			tmp2 = NULL;	/* To make free() at the end a NOP */
			break;
		}

		/*
		 * We got a valid link.  readlink() doesn't terminate strings
		 * so we have to do it.
		 */
		buf[size] = '\0';

		/*
		 * Our link will look like:
		 *
		 * "../../../../port-11:1:2/..STUFF../enclosure/1:0:3:0/SLOT 1"
		 *
		 * We want to grab the "enclosure/1:0:3:0/SLOT 1" part
		 */
		tmp3 = strstr(buf, "enclosure");
		if (tmp3 == NULL)
			break;

		if (asprintf(&path, "/sys/class/%s", tmp3) == -1) {
			/* If asprintf() fails, 'path' is undefined */
			path = NULL;
			break;
		}

		if (path == NULL)
			break;
	}

end:
	free(tmp2);
	free(tmp1);

	if (dp != NULL)
		closedir(dp);

	return (path);
}