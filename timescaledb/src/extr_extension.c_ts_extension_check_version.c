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
 int /*<<< orphan*/  EXTENSION_NAME ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  IsNormalProcessingMode () ; 
 int /*<<< orphan*/  IsTransactionState () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  extension_exists () ; 
 int /*<<< orphan*/  extension_load_without_preload () ; 
 int /*<<< orphan*/  extension_loader_present () ; 
 char* extension_version () ; 
 int /*<<< orphan*/  process_shared_preload_libraries_in_progress ; 
 scalar_t__ strcmp (char*,char const*) ; 

void
ts_extension_check_version(const char *so_version)
{
	char *sql_version;

	if (!IsNormalProcessingMode() || !IsTransactionState() || !extension_exists())
		return;
	sql_version = extension_version();

	if (strcmp(sql_version, so_version) != 0)
	{
		/*
		 * Throw a FATAL error here so that clients will be forced to reconnect
		 * when they have the wrong extension version loaded.
		 */
		ereport(FATAL,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("extension \"%s\" version mismatch: shared library version %s; SQL version "
						"%s",
						EXTENSION_NAME,
						so_version,
						sql_version)));
	}

	if (!process_shared_preload_libraries_in_progress && !extension_loader_present())
	{
		extension_load_without_preload();
	}
}