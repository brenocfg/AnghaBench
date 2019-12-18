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
typedef  void* Oid ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 void* chunk_oid ; 
 void* index_oid ; 
 int /*<<< orphan*/  reorder_chunk (void*,void*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dummy_reorder_func(Oid tableOid, Oid indexOid, bool verbose, Oid wait_id,
				   Oid destination_tablespace, Oid index_tablespace)
{
	chunk_oid = tableOid;
	index_oid = indexOid;
	reorder_chunk(tableOid, indexOid, true, wait_id, InvalidOid, InvalidOid);
}