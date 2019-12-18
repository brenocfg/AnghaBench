#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ an_refcnt; int /*<<< orphan*/  an_turn_cv; int /*<<< orphan*/  an_done; int /*<<< orphan*/  an_lock; } ;
typedef  TYPE_1__ kcf_areq_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
kcf_areq_cache_destructor(void *buf, void *cdrarg)
{
	kcf_areq_node_t *areq = (kcf_areq_node_t *)buf;

	ASSERT(areq->an_refcnt == 0);
	mutex_destroy(&areq->an_lock);
	cv_destroy(&areq->an_done);
	cv_destroy(&areq->an_turn_cv);
}