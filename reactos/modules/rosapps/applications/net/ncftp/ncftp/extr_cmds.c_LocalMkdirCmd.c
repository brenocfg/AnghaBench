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
 scalar_t__ MkDirs (char const*,int) ; 
 int /*<<< orphan*/  Sys (int const,char const** const,int /*<<< orphan*/  const,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int /*<<< orphan*/  perror (char const*) ; 

void
LocalMkdirCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
#if defined(WIN32) || defined(_WINDOWS)
	const char *arg;
	int i;

	for (i = 1; i < argc; i++) {
		arg = argv[i];
		if (MkDirs(arg, 00755) < 0) {
			perror(arg);
		}
	}
#else
	ARGSUSED(gUnusedArg);
	Sys(argc, argv, aip, "/bin/mkdir", 0);
#endif
}