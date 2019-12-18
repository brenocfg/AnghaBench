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
typedef  int /*<<< orphan*/  bm ;
typedef  int /*<<< orphan*/  CommandPtr ;
typedef  int /*<<< orphan*/  ArgvInfoPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenCmd (int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PrintHosts () ; 
 scalar_t__ RunBookmarkEditor (char*,int) ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int /*<<< orphan*/  printf (char*) ; 

void
HostsCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	const char *av[3];
	char bm[128];

	ARGSUSED(gUnusedArg);
	/* Skip visual mode if "-l". */
	if ((argc == 1) && (RunBookmarkEditor(bm, sizeof(bm)) == 0)) {
		if (bm[0] != '\0') {
			av[0] = "open";
			av[1] = bm;
			av[2] = NULL;
			OpenCmd(2, av, (CommandPtr) 0, (ArgvInfoPtr) 0);
		}
		return;
	}
	if (PrintHosts() <= 0) {
		(void) printf("You haven't bookmarked any FTP sites.\n");
		(void) printf("Before closing a site, you can use the \"bookmark\" command to save the current\nhost and directory for next time.\n");
	} else {
		(void) printf("\nTo use a bookmark, use the \"open\" command with the name of the bookmark.\n");
	}
}