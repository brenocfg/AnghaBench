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
struct TYPE_3__ {int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ vdev_cmd_data_t ;
typedef  int /*<<< orphan*/  fullpath ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  X_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 char* strtok_r (char*,char*,char**) ; 
 int /*<<< orphan*/  vdev_run_cmd (TYPE_1__*,char*) ; 
 char* zpool_get_cmd_search_path () ; 

__attribute__((used)) static void
vdev_run_cmd_thread(void *cb_cmd_data)
{
	vdev_cmd_data_t *data = cb_cmd_data;
	char *cmd = NULL, *cmddup, *cmdrest;

	cmddup = strdup(data->cmd);
	if (cmddup == NULL)
		return;

	cmdrest = cmddup;
	while ((cmd = strtok_r(cmdrest, ",", &cmdrest))) {
		char *dir = NULL, *sp, *sprest;
		char fullpath[MAXPATHLEN];

		if (strchr(cmd, '/') != NULL)
			continue;

		sp = zpool_get_cmd_search_path();
		if (sp == NULL)
			continue;

		sprest = sp;
		while ((dir = strtok_r(sprest, ":", &sprest))) {
			if (snprintf(fullpath, sizeof (fullpath),
			    "%s/%s", dir, cmd) == -1)
				continue;

			if (access(fullpath, X_OK) == 0) {
				vdev_run_cmd(data, fullpath);
				break;
			}
		}
		free(sp);
	}
	free(cmddup);
}