#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  indexParams; int /*<<< orphan*/ * excludeOpNames; scalar_t__ unique; } ;
typedef  TYPE_1__ IndexStmt ;
typedef  int /*<<< orphan*/  Hyperspace ;

/* Variables and functions */
 int /*<<< orphan*/  ts_indexing_verify_columns (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ts_indexing_verify_index(Hyperspace *hs, IndexStmt *stmt)
{
	if (stmt->unique || stmt->excludeOpNames != NULL)
		ts_indexing_verify_columns(hs, stmt->indexParams);
}