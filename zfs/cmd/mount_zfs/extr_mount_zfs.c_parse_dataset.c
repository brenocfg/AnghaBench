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
struct stat64 {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_NAME ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int stat64 (char*,struct stat64*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int zpool_read_label (int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
parse_dataset(char *dataset)
{
	char cwd[PATH_MAX];
	struct stat64 statbuf;
	int error;
	int len;

	/*
	 * We expect a pool/dataset to be provided, however if we're
	 * given a device which is a member of a zpool we attempt to
	 * extract the pool name stored in the label.  Given the pool
	 * name we can mount the root dataset.
	 */
	error = stat64(dataset, &statbuf);
	if (error == 0) {
		nvlist_t *config;
		char *name;
		int fd;

		fd = open(dataset, O_RDONLY);
		if (fd < 0)
			goto out;

		error = zpool_read_label(fd, &config, NULL);
		(void) close(fd);
		if (error)
			goto out;

		error = nvlist_lookup_string(config,
		    ZPOOL_CONFIG_POOL_NAME, &name);
		if (error) {
			nvlist_free(config);
		} else {
			dataset = strdup(name);
			nvlist_free(config);
			return (dataset);
		}
	}
out:
	/*
	 * If a file or directory in your current working directory is
	 * named 'dataset' then mount(8) will prepend your current working
	 * directory to the dataset.  There is no way to prevent this
	 * behavior so we simply check for it and strip the prepended
	 * patch when it is added.
	 */
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (dataset);

	len = strlen(cwd);

	/* Do not add one when cwd already ends in a trailing '/' */
	if (strncmp(cwd, dataset, len) == 0)
		return (dataset + len + (cwd[len-1] != '/'));

	return (dataset);
}