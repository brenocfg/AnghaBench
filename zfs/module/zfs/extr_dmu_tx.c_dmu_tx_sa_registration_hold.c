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
struct TYPE_5__ {int sa_num_attrs; TYPE_1__* sa_attr_table; scalar_t__ sa_reg_attr_obj; int /*<<< orphan*/  sa_need_attr_registration; } ;
typedef  TYPE_2__ sa_os_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_4__ {int /*<<< orphan*/  sa_name; int /*<<< orphan*/  sa_registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ DMU_NEW_OBJECT ; 
 int /*<<< orphan*/  dmu_tx_hold_zap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dmu_tx_sa_registration_hold(sa_os_t *sa, dmu_tx_t *tx)
{
	if (!sa->sa_need_attr_registration)
		return;

	for (int i = 0; i != sa->sa_num_attrs; i++) {
		if (!sa->sa_attr_table[i].sa_registered) {
			if (sa->sa_reg_attr_obj)
				dmu_tx_hold_zap(tx, sa->sa_reg_attr_obj,
				    B_TRUE, sa->sa_attr_table[i].sa_name);
			else
				dmu_tx_hold_zap(tx, DMU_NEW_OBJECT,
				    B_TRUE, sa->sa_attr_table[i].sa_name);
		}
	}
}