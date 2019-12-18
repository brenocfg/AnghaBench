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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_7__ {TYPE_1__* tx_pool; } ;
typedef  TYPE_2__ dmu_tx_t ;
struct TYPE_6__ {int /*<<< orphan*/ * dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSL_CRYPTO_KEY_REFCOUNT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_destroy (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  zap_increment (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  zap_lookup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int*) ; 

void
dsl_crypto_key_destroy_sync(uint64_t dckobj, dmu_tx_t *tx)
{
	objset_t *mos = tx->tx_pool->dp_meta_objset;
	uint64_t refcnt;

	/* Decrement the refcount, destroy if this is the last reference */
	VERIFY0(zap_lookup(mos, dckobj, DSL_CRYPTO_KEY_REFCOUNT,
	    sizeof (uint64_t), 1, &refcnt));

	if (refcnt != 1) {
		VERIFY0(zap_increment(mos, dckobj, DSL_CRYPTO_KEY_REFCOUNT,
		    -1, tx));
	} else {
		VERIFY0(zap_destroy(mos, dckobj, tx));
	}
}