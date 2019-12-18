#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hcxt; } ;
struct TYPE_6__ {scalar_t__ refcount; TYPE_1__ hctl; int /*<<< orphan*/  htab; int /*<<< orphan*/  (* pre_destroy_hook ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ Cache ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
cache_destroy(Cache *cache)
{
	if (cache->refcount > 0)
	{
		/* will be destroyed later */
		return;
	}

	if (cache->pre_destroy_hook != NULL)
		cache->pre_destroy_hook(cache);

	hash_destroy(cache->htab);
	MemoryContextDelete(cache->hctl.hcxt);
}