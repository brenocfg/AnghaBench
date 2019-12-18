#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sk_dk_lock; int /*<<< orphan*/  sk_km_lock; int /*<<< orphan*/  sk_wkeys_lock; int /*<<< orphan*/  sk_dsl_keys; int /*<<< orphan*/  sk_key_mappings; int /*<<< orphan*/  sk_wkeys; } ;
typedef  TYPE_1__ spa_keystore_t ;
typedef  int /*<<< orphan*/  dsl_wrapping_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  avl_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_wrapping_key_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 

void
spa_keystore_fini(spa_keystore_t *sk)
{
	dsl_wrapping_key_t *wkey;
	void *cookie = NULL;

	ASSERT(avl_is_empty(&sk->sk_dsl_keys));
	ASSERT(avl_is_empty(&sk->sk_key_mappings));

	while ((wkey = avl_destroy_nodes(&sk->sk_wkeys, &cookie)) != NULL)
		dsl_wrapping_key_free(wkey);

	avl_destroy(&sk->sk_wkeys);
	avl_destroy(&sk->sk_key_mappings);
	avl_destroy(&sk->sk_dsl_keys);
	rw_destroy(&sk->sk_wkeys_lock);
	rw_destroy(&sk->sk_km_lock);
	rw_destroy(&sk->sk_dk_lock);
}