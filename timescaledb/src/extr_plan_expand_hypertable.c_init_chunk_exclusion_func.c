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
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHUNK_EXCL_FUNC_NAME ; 
 int /*<<< orphan*/  INTERNAL_SCHEMA_NAME ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ LookupFuncName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ chunk_exclusion_func ; 
 int /*<<< orphan*/  lengthof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunks_arg_types ; 

__attribute__((used)) static void
init_chunk_exclusion_func()
{
	if (chunk_exclusion_func == InvalidOid)
	{
		List *l = list_make2(makeString(INTERNAL_SCHEMA_NAME), makeString(CHUNK_EXCL_FUNC_NAME));
		chunk_exclusion_func =
			LookupFuncName(l, lengthof(ts_chunks_arg_types), ts_chunks_arg_types, false);
	}
	Assert(chunk_exclusion_func != InvalidOid);
}