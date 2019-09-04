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
struct TYPE_3__ {scalar_t__ contype; } ;
typedef  TYPE_1__* Form_pg_constraint ;

/* Variables and functions */
 scalar_t__ CONSTRAINT_CHECK ; 

__attribute__((used)) static bool
chunk_constraint_need_on_chunk(Form_pg_constraint conform)
{
	if (conform->contype == CONSTRAINT_CHECK)
	{
		/*
		 * check and not null constraints handled by regular inheritance (from
		 * docs): All check constraints and not-null constraints on a parent
		 * table are automatically inherited by its children, unless
		 * explicitly specified otherwise with NO INHERIT clauses. Other types
		 * of constraints (unique, primary key, and foreign key constraints)
		 * are not inherited."
		 */
		return false;
	}
	return true;
}