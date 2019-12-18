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
struct TYPE_6__ {int /*<<< orphan*/  ck_length; TYPE_2__* ck_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  wk_refcnt; TYPE_1__ wk_key; } ;
typedef  TYPE_2__ dsl_wrapping_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int CRYPTO_BITS2BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  zfs_refcount_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_wrapping_key_free(dsl_wrapping_key_t *wkey)
{
	ASSERT0(zfs_refcount_count(&wkey->wk_refcnt));

	if (wkey->wk_key.ck_data) {
		bzero(wkey->wk_key.ck_data,
		    CRYPTO_BITS2BYTES(wkey->wk_key.ck_length));
		kmem_free(wkey->wk_key.ck_data,
		    CRYPTO_BITS2BYTES(wkey->wk_key.ck_length));
	}

	zfs_refcount_destroy(&wkey->wk_refcnt);
	kmem_free(wkey, sizeof (dsl_wrapping_key_t));
}