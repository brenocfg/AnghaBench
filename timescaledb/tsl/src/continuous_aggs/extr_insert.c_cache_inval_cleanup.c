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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * continuous_aggs_cache_inval_htab ; 
 int /*<<< orphan*/ * continuous_aggs_trigger_mctx ; 
 int /*<<< orphan*/  hash_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cache_inval_cleanup(void)
{
	Assert(continuous_aggs_cache_inval_htab != NULL);
	hash_destroy(continuous_aggs_cache_inval_htab);
	MemoryContextDelete(continuous_aggs_trigger_mctx);

	continuous_aggs_cache_inval_htab = NULL;
	continuous_aggs_trigger_mctx = NULL;
}