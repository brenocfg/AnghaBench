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
 int /*<<< orphan*/  UnregisterSubXactCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnregisterXactCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_invalidate_subxact_end ; 
 int /*<<< orphan*/  cache_invalidate_xact_end ; 

void
_cache_invalidate_fini(void)
{
	UnregisterXactCallback(cache_invalidate_xact_end, NULL);
	UnregisterSubXactCallback(cache_invalidate_subxact_end, NULL);
	/* No way to unregister relcache callback */
}