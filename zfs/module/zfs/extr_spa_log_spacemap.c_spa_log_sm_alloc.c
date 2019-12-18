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
typedef  void* uint64_t ;
struct TYPE_4__ {void* sls_txg; void* sls_sm_obj; } ;
typedef  TYPE_1__ spa_log_sm_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static spa_log_sm_t *
spa_log_sm_alloc(uint64_t sm_obj, uint64_t txg)
{
	spa_log_sm_t *sls = kmem_zalloc(sizeof (*sls), KM_SLEEP);
	sls->sls_sm_obj = sm_obj;
	sls->sls_txg = txg;
	return (sls);
}