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
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  pinned_caches ; 
 int /*<<< orphan*/ * pinned_caches_mctx ; 

__attribute__((used)) static void
cache_reset_pinned_caches(void)
{
	if (NULL != pinned_caches_mctx)
		MemoryContextDelete(pinned_caches_mctx);

	pinned_caches_mctx =
		AllocSetContextCreate(CacheMemoryContext, "Cache pins", ALLOCSET_DEFAULT_SIZES);

	pinned_caches = NIL;
}