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
struct TYPE_2__ {int /*<<< orphan*/  extname; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ AlterExtensionStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EXTENSION_NAME ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ loaded ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
should_load_on_alter_extension(Node *utility_stmt)
{
	AlterExtensionStmt *stmt = (AlterExtensionStmt *) utility_stmt;

	if (strcmp(stmt->extname, EXTENSION_NAME) != 0)
		return true;

	/* disallow loading two .so from different versions */
	if (loaded)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("extension \"%s\" cannot be updated after the old version has already been "
						"loaded",
						stmt->extname),
				 errhint("Start a new session and execute ALTER EXTENSION as the first command. "
						 "Make sure to pass the \"-X\" flag to psql.")));
	/* do not load the current (old) version's .so */
	return false;
}