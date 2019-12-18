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
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (int,char*,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getexecname () ; 
 int /*<<< orphan*/ * realpath (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 char* strstr (char*,char*) ; 
 scalar_t__ ztest_check_path (char*) ; 
 scalar_t__ ztest_dump_core ; 

__attribute__((used)) static void
ztest_get_zdb_bin(char *bin, int len)
{
	char *zdb_path;
	/*
	 * Try to use ZDB_PATH and in-tree zdb path. If not successful, just
	 * let popen to search through PATH.
	 */
	if ((zdb_path = getenv("ZDB_PATH"))) {
		strlcpy(bin, zdb_path, len); /* In env */
		if (!ztest_check_path(bin)) {
			ztest_dump_core = 0;
			fatal(1, "invalid ZDB_PATH '%s'", bin);
		}
		return;
	}

	VERIFY(realpath(getexecname(), bin) != NULL);
	if (strstr(bin, "/ztest/")) {
		strstr(bin, "/ztest/")[0] = '\0'; /* In-tree */
		strcat(bin, "/zdb/zdb");
		if (ztest_check_path(bin))
			return;
	}
	strcpy(bin, "zdb");
}