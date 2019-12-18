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
typedef  int /*<<< orphan*/  crypto_spi_ctx_template_t ;
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
typedef  int /*<<< orphan*/  crypto_mechanism_t ;
struct TYPE_6__ {scalar_t__ ck_format; } ;
typedef  TYPE_1__ crypto_key_t ;
struct TYPE_7__ {int /*<<< orphan*/ * cc_provider_private; } ;
typedef  TYPE_2__ crypto_ctx_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  aes_ctx_t ;

/* Variables and functions */
 scalar_t__ CRYPTO_KEY_RAW ; 
 int CRYPTO_KEY_TYPE_INCONSISTENT ; 
 int CRYPTO_SUCCESS ; 
 int aes_check_mech_param (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int aes_common_init_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_mode_ctx (int /*<<< orphan*/ *) ; 
 int crypto_kmflag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aes_common_init(crypto_ctx_t *ctx, crypto_mechanism_t *mechanism,
    crypto_key_t *key, crypto_spi_ctx_template_t template,
    crypto_req_handle_t req, boolean_t is_encrypt_init)
{
	aes_ctx_t *aes_ctx;
	int rv;
	int kmflag;

	/*
	 * Only keys by value are supported by this module.
	 */
	if (key->ck_format != CRYPTO_KEY_RAW) {
		return (CRYPTO_KEY_TYPE_INCONSISTENT);
	}

	kmflag = crypto_kmflag(req);
	if ((rv = aes_check_mech_param(mechanism, &aes_ctx, kmflag))
	    != CRYPTO_SUCCESS)
		return (rv);

	rv = aes_common_init_ctx(aes_ctx, template, mechanism, key, kmflag,
	    is_encrypt_init);
	if (rv != CRYPTO_SUCCESS) {
		crypto_free_mode_ctx(aes_ctx);
		return (rv);
	}

	ctx->cc_provider_private = aes_ctx;

	return (CRYPTO_SUCCESS);
}