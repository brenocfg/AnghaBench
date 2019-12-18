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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  bgw_log_insert_relation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_namespace_oid (char*,int) ; 
 int /*<<< orphan*/  get_relname_relid (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bgw_log_insert(char *msg)
{
	Relation rel;
	Oid log_oid = get_relname_relid("bgw_log", get_namespace_oid("public", false));

	rel = heap_open(log_oid, RowExclusiveLock);
	bgw_log_insert_relation(rel, msg);
	heap_close(rel, RowExclusiveLock);
}