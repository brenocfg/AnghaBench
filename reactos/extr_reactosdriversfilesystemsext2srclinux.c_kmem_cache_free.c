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
struct TYPE_3__ {int /*<<< orphan*/  la; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ kmem_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

void kmem_cache_free(kmem_cache_t *kc, void *p)
{
    if (p) {
        atomic_dec(&kc->count);
        ExFreeToNPagedLookasideList(&(kc->la), p);
    }
}