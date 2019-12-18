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
 int SA_OK ; 
 int SA_SYSTEM_ERR ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_linux_hostspec (char const*,char**) ; 
 int libzfs_run_process (char*,char**,int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
nfs_disable_share_one(const char *sharepath, const char *host,
    const char *security, const char *access, void *cookie)
{
	int rc;
	char *linuxhost, *hostpath;
	char *argv[4];

	rc = get_linux_hostspec(host, &linuxhost);

	if (rc < 0)
		exit(1);

	hostpath = malloc(strlen(linuxhost) + 1 + strlen(sharepath) + 1);

	if (hostpath == NULL) {
		free(linuxhost);
		exit(1);
	}

	sprintf(hostpath, "%s:%s", linuxhost, sharepath);

	free(linuxhost);

#ifdef DEBUG
	fprintf(stderr, "unsharing %s\n", hostpath);
#endif

	argv[0] = "/usr/sbin/exportfs";
	argv[1] = "-u";
	argv[2] = hostpath;
	argv[3] = NULL;

	rc = libzfs_run_process(argv[0], argv, 0);

	free(hostpath);

	if (rc < 0)
		return (SA_SYSTEM_ERR);
	else
		return (SA_OK);
}