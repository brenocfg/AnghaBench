#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int zo_verbose; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXNAMELEN ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* spa_config_path ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*,char*,char*) ; 
 char* strstr (char*,char*) ; 
 char* umem_alloc (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (char*,int const) ; 
 scalar_t__ ztest_dump_core ; 
 int /*<<< orphan*/  ztest_get_zdb_bin (char*,int const) ; 
 TYPE_1__ ztest_opts ; 

__attribute__((used)) static void
ztest_run_zdb(char *pool)
{
	int status;
	char *bin;
	char *zdb;
	char *zbuf;
	const int len = MAXPATHLEN + MAXNAMELEN + 20;
	FILE *fp;

	bin = umem_alloc(len, UMEM_NOFAIL);
	zdb = umem_alloc(len, UMEM_NOFAIL);
	zbuf = umem_alloc(1024, UMEM_NOFAIL);

	ztest_get_zdb_bin(bin, len);

	(void) sprintf(zdb,
	    "%s -bcc%s%s -G -d -Y -U %s %s",
	    bin,
	    ztest_opts.zo_verbose >= 3 ? "s" : "",
	    ztest_opts.zo_verbose >= 4 ? "v" : "",
	    spa_config_path,
	    pool);

	if (ztest_opts.zo_verbose >= 5)
		(void) printf("Executing %s\n", strstr(zdb, "zdb "));

	fp = popen(zdb, "r");

	while (fgets(zbuf, 1024, fp) != NULL)
		if (ztest_opts.zo_verbose >= 3)
			(void) printf("%s", zbuf);

	status = pclose(fp);

	if (status == 0)
		goto out;

	ztest_dump_core = 0;
	if (WIFEXITED(status))
		fatal(0, "'%s' exit code %d", zdb, WEXITSTATUS(status));
	else
		fatal(0, "'%s' died with signal %d", zdb, WTERMSIG(status));
out:
	umem_free(bin, len);
	umem_free(zdb, len);
	umem_free(zbuf, 1024);
}