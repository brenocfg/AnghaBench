#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_OBJECT_END ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int dmu_free_long_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dmu_object_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_hold_bonus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_hold_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_mark_netfree (int /*<<< orphan*/ *) ; 

int
dmu_free_long_object(objset_t *os, uint64_t object)
{
	dmu_tx_t *tx;
	int err;

	err = dmu_free_long_range(os, object, 0, DMU_OBJECT_END);
	if (err != 0)
		return (err);

	tx = dmu_tx_create(os);
	dmu_tx_hold_bonus(tx, object);
	dmu_tx_hold_free(tx, object, 0, DMU_OBJECT_END);
	dmu_tx_mark_netfree(tx);
	err = dmu_tx_assign(tx, TXG_WAIT);
	if (err == 0) {
		if (err == 0)
			err = dmu_object_free(os, object, tx);

		dmu_tx_commit(tx);
	} else {
		dmu_tx_abort(tx);
	}

	return (err);
}