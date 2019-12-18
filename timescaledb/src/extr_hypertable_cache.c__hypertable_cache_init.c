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
 int /*<<< orphan*/  CreateCacheMemoryContext () ; 
 int /*<<< orphan*/  hypertable_cache_create () ; 
 int /*<<< orphan*/  hypertable_cache_current ; 

void
_hypertable_cache_init(void)
{
	CreateCacheMemoryContext();
	hypertable_cache_current = hypertable_cache_create();
}