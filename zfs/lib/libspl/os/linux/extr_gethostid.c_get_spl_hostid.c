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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned long HOSTID_MASK ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,unsigned long*) ; 
 char* getenv (char*) ; 
 unsigned long strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long
get_spl_hostid(void)
{
	FILE *f;
	unsigned long hostid;
	char *env;

	/*
	 * Allow the hostid to be subverted for testing.
	 */
	env = getenv("ZFS_HOSTID");
	if (env) {
		hostid = strtoull(env, NULL, 0);
		return (hostid & HOSTID_MASK);
	}

	f = fopen("/sys/module/spl/parameters/spl_hostid", "r");
	if (!f)
		return (0);

	if (fscanf(f, "%lu", &hostid) != 1)
		hostid = 0;

	fclose(f);

	return (hostid & HOSTID_MASK);
}