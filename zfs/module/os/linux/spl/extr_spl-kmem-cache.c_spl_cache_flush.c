#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spl_kmem_magazine_t ;
struct TYPE_4__ {int /*<<< orphan*/  skc_lock; } ;
typedef  TYPE_1__ spl_kmem_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  __spl_cache_flush (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spl_cache_flush(spl_kmem_cache_t *skc, spl_kmem_magazine_t *skm, int flush)
{
	spin_lock(&skc->skc_lock);
	__spl_cache_flush(skc, skm, flush);
	spin_unlock(&skc->skc_lock);
}