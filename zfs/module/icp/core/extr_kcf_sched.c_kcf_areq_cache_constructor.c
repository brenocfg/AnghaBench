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
struct TYPE_2__ {int /*<<< orphan*/  an_turn_cv; int /*<<< orphan*/  an_done; int /*<<< orphan*/  an_lock; scalar_t__ an_refcnt; int /*<<< orphan*/  an_type; } ;
typedef  TYPE_1__ kcf_areq_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ASYNCH ; 
 int /*<<< orphan*/  CV_DEFAULT ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kcf_areq_cache_constructor(void *buf, void *cdrarg, int kmflags)
{
	kcf_areq_node_t *areq = (kcf_areq_node_t *)buf;

	areq->an_type = CRYPTO_ASYNCH;
	areq->an_refcnt = 0;
	mutex_init(&areq->an_lock, NULL, MUTEX_DEFAULT, NULL);
	cv_init(&areq->an_done, NULL, CV_DEFAULT, NULL);
	cv_init(&areq->an_turn_cv, NULL, CV_DEFAULT, NULL);

	return (0);
}