#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_6__ {int /*<<< orphan*/  dcrka_nvl; scalar_t__ dcrka_do_key; int /*<<< orphan*/  dcrka_ostype; int /*<<< orphan*/  dcrka_dsobj; } ;
typedef  TYPE_1__ dsl_crypto_recv_key_arg_t ;
struct TYPE_7__ {int /*<<< orphan*/  tx_pool; } ;
typedef  TYPE_2__ dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_crypto_recv_raw_key_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_crypto_recv_raw_objset_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
dsl_crypto_recv_key_sync(void *arg, dmu_tx_t *tx)
{
	dsl_crypto_recv_key_arg_t *dcrka = arg;
	dsl_dataset_t *ds;

	VERIFY0(dsl_dataset_hold_obj(tx->tx_pool, dcrka->dcrka_dsobj,
	    FTAG, &ds));
	dsl_crypto_recv_raw_objset_sync(ds, dcrka->dcrka_ostype,
	    dcrka->dcrka_nvl, tx);
	if (dcrka->dcrka_do_key)
		dsl_crypto_recv_raw_key_sync(ds, dcrka->dcrka_nvl, tx);
	dsl_dataset_rele(ds, FTAG);
}