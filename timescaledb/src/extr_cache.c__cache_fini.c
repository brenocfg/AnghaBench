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
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  UnregisterSubXactCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnregisterXactCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_subxact_abort ; 
 int /*<<< orphan*/  cache_xact_end ; 
 int /*<<< orphan*/  pinned_caches ; 
 int /*<<< orphan*/ * pinned_caches_mctx ; 

void
_cache_fini(void)
{
	MemoryContextDelete(pinned_caches_mctx);
	pinned_caches_mctx = NULL;
	pinned_caches = NIL;
	UnregisterXactCallback(cache_xact_end, NULL);
	UnregisterSubXactCallback(cache_subxact_abort, NULL);
}