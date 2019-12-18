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
 int /*<<< orphan*/  DEFAULT_ROLE_READ_ALL_SETTINGS ; 
 int /*<<< orphan*/  EXTENSION_NAME ; 
 int /*<<< orphan*/  FATAL ; 
 char* GetConfigOptionByName (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_member_of_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ superuser () ; 

__attribute__((used)) static void
extension_load_without_preload()
{
	/* cannot use GUC variable here since extension not yet loaded */
	char *allow_install_without_preload =
		GetConfigOptionByName("timescaledb.allow_install_without_preload", NULL, true);

	if (allow_install_without_preload == NULL || strcmp(allow_install_without_preload, "on") != 0)
	{
		/*
		 * These are FATAL because otherwise the loader ends up in a weird
		 * half-loaded state after an ERROR
		 */
		/* Only privileged users can get the value of `config file` */

#if PG96
		if (superuser())
#else
		if (is_member_of_role(GetUserId(), DEFAULT_ROLE_READ_ALL_SETTINGS))
#endif
		{
			char *config_file = GetConfigOptionByName("config_file", NULL, false);

			ereport(FATAL,
					(errmsg("extension \"%s\" must be preloaded", EXTENSION_NAME),
					 errhint("Please preload the timescaledb library via "
							 "shared_preload_libraries.\n\n"
							 "This can be done by editing the config file at: %1$s\n"
							 "and adding 'timescaledb' to the list in the shared_preload_libraries "
							 "config.\n"
							 "	# Modify postgresql.conf:\n	shared_preload_libraries = "
							 "'timescaledb'\n\n"
							 "Another way to do this, if not preloading other libraries, is with "
							 "the command:\n"
							 "	echo \"shared_preload_libraries = 'timescaledb'\" >> %1$s \n\n"
							 "(Will require a database restart.)\n\n"
							 "If you REALLY know what you are doing and would like to load the "
							 "library without preloading, you can disable this check with: \n"
							 "	SET timescaledb.allow_install_without_preload = 'on';",
							 config_file)));
		}
		else
		{
			ereport(FATAL,
					(errmsg("extension \"%s\" must be preloaded", EXTENSION_NAME),
					 errhint(
						 "Please preload the timescaledb library via shared_preload_libraries.\n\n"
						 "This can be done by editing the postgres config file \n"
						 "and adding 'timescaledb' to the list in the shared_preload_libraries "
						 "config.\n"
						 "	# Modify postgresql.conf:\n	shared_preload_libraries = "
						 "'timescaledb'\n\n"
						 "Another way to do this, if not preloading other libraries, is with the "
						 "command:\n"
						 "	echo \"shared_preload_libraries = 'timescaledb'\" >> "
						 "/path/to/config/file \n\n"
						 "(Will require a database restart.)\n\n"
						 "If you REALLY know what you are doing and would like to load the library "
						 "without preloading, you can disable this check with: \n"
						 "	SET timescaledb.allow_install_without_preload = 'on';")));
		}

		return;
	}
}