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
typedef  int /*<<< orphan*/  CommandPtr ;
typedef  int /*<<< orphan*/  ArgvInfoPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RunBatch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SpoolCheck () ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  gConn ; 
 char* gOurDirectoryPath ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
BGStartCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	int i, n;

	ARGSUSED(gUnusedArg);
	if (SpoolCheck() < 0)
		return;

	if ((argc < 2) || ((n = atoi(argv[1])) < 2)) {
		RunBatch(0, &gConn);
		(void) printf("Background process started.\n");
#if defined(WIN32) || defined(_WINDOWS)
#else
		(void) printf("Watch the \"%s/batchlog\" file to see how it is progressing.\n", gOurDirectoryPath);
#endif
	} else {
		for (i=0; i<n; i++)
			RunBatch(0, &gConn);
		(void) printf("Background processes started.\n");
#if defined(WIN32) || defined(_WINDOWS)
#else
		(void) printf("Watch the \"%s/batchlog\" file to see how it is progressing.\n", gOurDirectoryPath);
#endif
	}
}