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
struct TYPE_4__ {int pd_prov_type; int /*<<< orphan*/  pd_lock; int /*<<< orphan*/  pd_remove_cv; int /*<<< orphan*/  pd_state; } ;
typedef  TYPE_1__ kcf_provider_desc_t ;

/* Variables and functions */
#define  CRYPTO_HW_PROVIDER 130 
#define  CRYPTO_LOGICAL_PROVIDER 129 
#define  CRYPTO_SW_PROVIDER 128 
 int /*<<< orphan*/  KCF_PROV_DISABLED ; 
 int /*<<< orphan*/  KCF_PROV_FREED ; 
 int /*<<< orphan*/  KCF_PROV_REMOVED ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcf_free_provider_desc (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
kcf_provider_zero_refcnt(kcf_provider_desc_t *desc)
{
	mutex_enter(&desc->pd_lock);
	switch (desc->pd_prov_type) {
	case CRYPTO_SW_PROVIDER:
		if (desc->pd_state == KCF_PROV_REMOVED ||
		    desc->pd_state == KCF_PROV_DISABLED) {
			desc->pd_state = KCF_PROV_FREED;
			cv_broadcast(&desc->pd_remove_cv);
			mutex_exit(&desc->pd_lock);
			break;
		}
		/* FALLTHRU */

	case CRYPTO_HW_PROVIDER:
	case CRYPTO_LOGICAL_PROVIDER:
		mutex_exit(&desc->pd_lock);
		kcf_free_provider_desc(desc);
	}
}