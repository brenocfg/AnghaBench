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
 int /*<<< orphan*/  RegisterSubXactCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegisterXactCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_reset_pinned_caches () ; 
 int /*<<< orphan*/  cache_subxact_abort ; 
 int /*<<< orphan*/  cache_xact_end ; 

void
_cache_init(void)
{
	cache_reset_pinned_caches();
	RegisterXactCallback(cache_xact_end, NULL);
	RegisterSubXactCallback(cache_subxact_abort, NULL);
}