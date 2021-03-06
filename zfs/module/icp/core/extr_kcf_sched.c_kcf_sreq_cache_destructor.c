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
struct TYPE_2__ {int /*<<< orphan*/  sn_cv; int /*<<< orphan*/  sn_lock; } ;
typedef  TYPE_1__ kcf_sreq_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
kcf_sreq_cache_destructor(void *buf, void *cdrarg)
{
	kcf_sreq_node_t *sreq = (kcf_sreq_node_t *)buf;

	mutex_destroy(&sreq->sn_lock);
	cv_destroy(&sreq->sn_cv);
}