#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int as_numbuckets; int /*<<< orphan*/  as_lock; TYPE_2__* as_buckets; } ;
typedef  TYPE_1__ aggsum_t ;
typedef  int /*<<< orphan*/  aggsum_bucket_t ;
struct TYPE_5__ {int /*<<< orphan*/  asc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void
aggsum_fini(aggsum_t *as)
{
	for (int i = 0; i < as->as_numbuckets; i++)
		mutex_destroy(&as->as_buckets[i].asc_lock);
	kmem_free(as->as_buckets, as->as_numbuckets * sizeof (aggsum_bucket_t));
	mutex_destroy(&as->as_lock);
}