#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dck_wkey; int /*<<< orphan*/  dck_holds; int /*<<< orphan*/  dck_key; } ;
typedef  TYPE_1__ dsl_crypto_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  dsl_wrapping_key_rele (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_crypt_key_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_crypto_key_free(dsl_crypto_key_t *dck)
{
	ASSERT(zfs_refcount_count(&dck->dck_holds) == 0);

	/* destroy the zio_crypt_key_t */
	zio_crypt_key_destroy(&dck->dck_key);

	/* free the refcount, wrapping key, and lock */
	zfs_refcount_destroy(&dck->dck_holds);
	if (dck->dck_wkey)
		dsl_wrapping_key_rele(dck->dck_wkey, dck);

	/* free the key */
	kmem_free(dck, sizeof (dsl_crypto_key_t));
}