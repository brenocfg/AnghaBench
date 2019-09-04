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
typedef  scalar_t__ int64 ;

/* Variables and functions */
 scalar_t__ BLCKSZ ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GUC_UNIT_BLOCKS ; 
 char* GetConfigOption (char*,int,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fixed_memory_cache_size ; 
 int /*<<< orphan*/  parse_int (char const*,int*,int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int64
get_memory_cache_size(void)
{
	const char *val;
	const char *hintmsg;
	int shared_buffers;
	int64 memory_bytes;

	if (fixed_memory_cache_size > 0)
		return fixed_memory_cache_size;

	val = GetConfigOption("shared_buffers", false, false);

	if (NULL == val)
		elog(ERROR, "missing configuration for 'shared_buffers'");

	if (!parse_int(val, &shared_buffers, GUC_UNIT_BLOCKS, &hintmsg))
		elog(ERROR, "could not parse 'shared_buffers' setting: %s", hintmsg);

	memory_bytes = shared_buffers;

	/* Value is in blocks, so convert to bytes */
	memory_bytes *= BLCKSZ;

	return memory_bytes;
}