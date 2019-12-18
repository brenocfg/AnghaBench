#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  skc_obj_size; } ;
typedef  TYPE_1__ kmem_cache_t ;

/* Variables and functions */

uint64_t
spl_kmem_cache_entry_size(kmem_cache_t *cache)
{
	return (cache->skc_obj_size);
}