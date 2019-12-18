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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  crypto_verify_ops_t ;
typedef  int /*<<< orphan*/  crypto_sign_ops_t ;
typedef  int /*<<< orphan*/  crypto_session_ops_t ;
typedef  int /*<<< orphan*/  crypto_random_number_ops_t ;
typedef  int /*<<< orphan*/  crypto_provider_management_ops_t ;
struct TYPE_4__ {int /*<<< orphan*/ * co_ctx_ops; int /*<<< orphan*/ * co_provider_ops; int /*<<< orphan*/ * co_key_ops; int /*<<< orphan*/ * co_object_ops; int /*<<< orphan*/ * co_session_ops; int /*<<< orphan*/ * co_random_ops; int /*<<< orphan*/ * co_dual_cipher_mac_ops; int /*<<< orphan*/ * co_dual_ops; int /*<<< orphan*/ * co_verify_ops; int /*<<< orphan*/ * co_sign_ops; int /*<<< orphan*/ * co_mac_ops; int /*<<< orphan*/ * co_cipher_ops; int /*<<< orphan*/ * co_digest_ops; int /*<<< orphan*/ * co_control_ops; } ;
typedef  TYPE_1__ crypto_ops_t ;
typedef  int /*<<< orphan*/  crypto_object_ops_t ;
typedef  int /*<<< orphan*/  crypto_mac_ops_t ;
typedef  int /*<<< orphan*/  crypto_key_ops_t ;
typedef  int /*<<< orphan*/  crypto_dual_ops_t ;
typedef  int /*<<< orphan*/  crypto_dual_cipher_mac_ops_t ;
typedef  int /*<<< orphan*/  crypto_digest_ops_t ;
typedef  int /*<<< orphan*/  crypto_ctx_ops_t ;
typedef  int /*<<< orphan*/  crypto_control_ops_t ;
typedef  int /*<<< orphan*/  crypto_cipher_ops_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 void* kmem_alloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
allocate_ops_v1(crypto_ops_t *src, crypto_ops_t *dst, uint_t *mech_list_count)
{
	if (src->co_control_ops != NULL)
		dst->co_control_ops = kmem_alloc(sizeof (crypto_control_ops_t),
		    KM_SLEEP);

	if (src->co_digest_ops != NULL)
		dst->co_digest_ops = kmem_alloc(sizeof (crypto_digest_ops_t),
		    KM_SLEEP);

	if (src->co_cipher_ops != NULL)
		dst->co_cipher_ops = kmem_alloc(sizeof (crypto_cipher_ops_t),
		    KM_SLEEP);

	if (src->co_mac_ops != NULL)
		dst->co_mac_ops = kmem_alloc(sizeof (crypto_mac_ops_t),
		    KM_SLEEP);

	if (src->co_sign_ops != NULL)
		dst->co_sign_ops = kmem_alloc(sizeof (crypto_sign_ops_t),
		    KM_SLEEP);

	if (src->co_verify_ops != NULL)
		dst->co_verify_ops = kmem_alloc(sizeof (crypto_verify_ops_t),
		    KM_SLEEP);

	if (src->co_dual_ops != NULL)
		dst->co_dual_ops = kmem_alloc(sizeof (crypto_dual_ops_t),
		    KM_SLEEP);

	if (src->co_dual_cipher_mac_ops != NULL)
		dst->co_dual_cipher_mac_ops = kmem_alloc(
		    sizeof (crypto_dual_cipher_mac_ops_t), KM_SLEEP);

	if (src->co_random_ops != NULL) {
		dst->co_random_ops = kmem_alloc(
		    sizeof (crypto_random_number_ops_t), KM_SLEEP);

		/*
		 * Allocate storage to store the array of supported mechanisms
		 * specified by provider. We allocate extra mechanism storage
		 * if the provider has random_ops since we keep an internal
		 * mechanism, SUN_RANDOM, in this case.
		 */
		(*mech_list_count)++;
	}

	if (src->co_session_ops != NULL)
		dst->co_session_ops = kmem_alloc(sizeof (crypto_session_ops_t),
		    KM_SLEEP);

	if (src->co_object_ops != NULL)
		dst->co_object_ops = kmem_alloc(sizeof (crypto_object_ops_t),
		    KM_SLEEP);

	if (src->co_key_ops != NULL)
		dst->co_key_ops = kmem_alloc(sizeof (crypto_key_ops_t),
		    KM_SLEEP);

	if (src->co_provider_ops != NULL)
		dst->co_provider_ops = kmem_alloc(
		    sizeof (crypto_provider_management_ops_t), KM_SLEEP);

	if (src->co_ctx_ops != NULL)
		dst->co_ctx_ops = kmem_alloc(sizeof (crypto_ctx_ops_t),
		    KM_SLEEP);
}