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
typedef  int /*<<< orphan*/  Hypertable ;
typedef  int /*<<< orphan*/  AlterTableCmd ;

/* Variables and functions */
 int /*<<< orphan*/  alter_hypertable_constraint ; 
 int /*<<< orphan*/  foreach_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
process_altertable_alter_constraint_end(Hypertable *ht, AlterTableCmd *cmd)
{
	foreach_chunk(ht, alter_hypertable_constraint, cmd);
}