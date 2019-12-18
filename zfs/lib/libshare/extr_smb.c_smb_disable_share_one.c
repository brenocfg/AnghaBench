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
 char* NET_CMD_ARG_HOST ; 
 char* NET_CMD_PATH ; 
 int SA_OK ; 
 int SA_SYSTEM_ERR ; 
 int libzfs_run_process (char*,char**,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
smb_disable_share_one(const char *sharename)
{
	int rc;
	char *argv[7];

	/* CMD: net -S NET_CMD_ARG_HOST usershare delete Test1 */
	argv[0] = NET_CMD_PATH;
	argv[1] = (char *)"-S";
	argv[2] = NET_CMD_ARG_HOST;
	argv[3] = (char *)"usershare";
	argv[4] = (char *)"delete";
	argv[5] = strdup(sharename);
	argv[6] = NULL;

	rc = libzfs_run_process(argv[0], argv, 0);
	if (rc < 0)
		return (SA_SYSTEM_ERR);
	else
		return (SA_OK);
}