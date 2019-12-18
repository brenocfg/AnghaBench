#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int skm_avail; scalar_t__ skm_magic; int /*<<< orphan*/ * skm_objs; } ;
typedef  TYPE_1__ spl_kmem_magazine_t ;
struct TYPE_7__ {scalar_t__ skc_magic; } ;
typedef  TYPE_2__ spl_kmem_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int MIN (int,int) ; 
 scalar_t__ SKC_MAGIC ; 
 scalar_t__ SKM_MAGIC ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spl_cache_shrink (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__spl_cache_flush(spl_kmem_cache_t *skc, spl_kmem_magazine_t *skm, int flush)
{
	int i, count = MIN(flush, skm->skm_avail);

	ASSERT(skc->skc_magic == SKC_MAGIC);
	ASSERT(skm->skm_magic == SKM_MAGIC);

	for (i = 0; i < count; i++)
		spl_cache_shrink(skc, skm->skm_objs[i]);

	skm->skm_avail -= count;
	memmove(skm->skm_objs, &(skm->skm_objs[count]),
	    sizeof (void *) * skm->skm_avail);
}