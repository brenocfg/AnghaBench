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
struct TYPE_2__ {int /*<<< orphan*/  sn_lock; int /*<<< orphan*/  sn_cv; int /*<<< orphan*/  sn_type; } ;
typedef  TYPE_1__ kcf_sreq_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_SYNCH ; 
 int /*<<< orphan*/  CV_DEFAULT ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kcf_sreq_cache_constructor(void *buf, void *cdrarg, int kmflags)
{
	kcf_sreq_node_t *sreq = (kcf_sreq_node_t *)buf;

	sreq->sn_type = CRYPTO_SYNCH;
	cv_init(&sreq->sn_cv, NULL, CV_DEFAULT, NULL);
	mutex_init(&sreq->sn_lock, NULL, MUTEX_DEFAULT, NULL);

	return (0);
}