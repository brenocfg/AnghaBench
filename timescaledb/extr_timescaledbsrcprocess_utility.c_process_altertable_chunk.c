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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  int /*<<< orphan*/  AlterTableCmd ;

/* Variables and functions */
 int /*<<< orphan*/  AlterTableInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
process_altertable_chunk(Hypertable *ht, Oid chunk_relid, void *arg)
{
	AlterTableCmd *cmd = arg;

	AlterTableInternal(chunk_relid, list_make1(cmd), false);
}