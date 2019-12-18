#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  scalar_t__ sha1_mech_type_t ;
typedef  int /*<<< orphan*/  sha1_hmac_ctx_t ;
typedef  int /*<<< orphan*/  sha1_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/ * cc_provider_private; } ;
typedef  TYPE_1__ crypto_ctx_t ;
struct TYPE_6__ {scalar_t__ sc_mech_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CRYPTO_SUCCESS ; 
 TYPE_3__* PROV_SHA1_CTX (TYPE_1__*) ; 
 scalar_t__ SHA1_HMAC_GEN_MECH_INFO_TYPE ; 
 scalar_t__ SHA1_HMAC_MECH_INFO_TYPE ; 
 scalar_t__ SHA1_MECH_INFO_TYPE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
sha1_free_context(crypto_ctx_t *ctx)
{
	uint_t ctx_len;
	sha1_mech_type_t mech_type;

	if (ctx->cc_provider_private == NULL)
		return (CRYPTO_SUCCESS);

	/*
	 * We have to free either SHA1 or SHA1-HMAC contexts, which
	 * have different lengths.
	 */

	mech_type = PROV_SHA1_CTX(ctx)->sc_mech_type;
	if (mech_type == SHA1_MECH_INFO_TYPE)
		ctx_len = sizeof (sha1_ctx_t);
	else {
		ASSERT(mech_type == SHA1_HMAC_MECH_INFO_TYPE ||
		    mech_type == SHA1_HMAC_GEN_MECH_INFO_TYPE);
		ctx_len = sizeof (sha1_hmac_ctx_t);
	}

	bzero(ctx->cc_provider_private, ctx_len);
	kmem_free(ctx->cc_provider_private, ctx_len);
	ctx->cc_provider_private = NULL;

	return (CRYPTO_SUCCESS);
}