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
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHUNK_EXCL_FUNC_NAME ; 
 int /*<<< orphan*/  INTERNAL_SCHEMA_NAME ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ chunk_exclusion_func ; 
 scalar_t__ get_function_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lengthof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunks_arg_types ; 

__attribute__((used)) static void
init_chunk_exclusion_func()
{
	if (chunk_exclusion_func == InvalidOid)
		chunk_exclusion_func = get_function_oid(CHUNK_EXCL_FUNC_NAME,
												INTERNAL_SCHEMA_NAME,
												lengthof(ts_chunks_arg_types),
												ts_chunks_arg_types);
	Assert(chunk_exclusion_func != InvalidOid);
}