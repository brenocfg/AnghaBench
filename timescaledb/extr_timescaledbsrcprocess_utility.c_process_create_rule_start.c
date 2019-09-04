#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ parsetree; } ;
struct TYPE_4__ {int /*<<< orphan*/  relation; } ;
typedef  TYPE_1__ RuleStmt ;
typedef  TYPE_2__ ProcessUtilityArgs ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ ts_hypertable_relid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_create_rule_start(ProcessUtilityArgs *args)
{
	RuleStmt *stmt = (RuleStmt *) args->parsetree;

	if (ts_hypertable_relid(stmt->relation) == InvalidOid)
		return;

	ereport(ERROR,
			(errcode(ERRCODE_FEATURE_NOT_SUPPORTED), errmsg("hypertables do not support rules")));
}