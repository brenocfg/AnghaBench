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
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EXTENSION_NAME ; 
 char* GetConfigOptionByName (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_supported_pg_version (long) ; 
 long strtol (char*,int /*<<< orphan*/ *,int) ; 

void
ts_extension_check_server_version()
{
	/*
	 * This is a load-time check for the correct server version since the
	 * extension may be distributed as a binary
	 */
	char *server_version_num_guc = GetConfigOptionByName("server_version_num", NULL, false);
	long server_version_num = strtol(server_version_num_guc, NULL, 10);

	if (!is_supported_pg_version(server_version_num))
	{
		char *server_version_guc = GetConfigOptionByName("server_version", NULL, false);

		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("extension \"%s\" does not support postgres version %s",
						EXTENSION_NAME,
						server_version_guc)));
	}
}