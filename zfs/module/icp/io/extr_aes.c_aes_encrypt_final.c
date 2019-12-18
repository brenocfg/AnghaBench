#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gcm_ctx_t ;
typedef  int /*<<< orphan*/  ctr_ctx_t ;
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
struct TYPE_10__ {scalar_t__ cd_format; size_t cd_offset; size_t cd_length; } ;
typedef  TYPE_1__ crypto_data_t ;
struct TYPE_11__ {TYPE_3__* cc_provider_private; } ;
typedef  TYPE_2__ crypto_ctx_t ;
typedef  int /*<<< orphan*/  ccm_ctx_t ;
struct TYPE_12__ {int ac_flags; scalar_t__ ac_remainder_len; } ;
typedef  TYPE_3__ aes_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_LEN ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int CCM_MODE ; 
 int CRYPTO_ARGUMENTS_BAD ; 
 int CRYPTO_DATA_LEN_RANGE ; 
 scalar_t__ CRYPTO_DATA_RAW ; 
 scalar_t__ CRYPTO_DATA_UIO ; 
 int CRYPTO_SUCCESS ; 
 int CTR_MODE ; 
 int GCM_MODE ; 
 int GMAC_MODE ; 
 int /*<<< orphan*/  aes_copy_block ; 
 int /*<<< orphan*/  aes_encrypt_block ; 
 int /*<<< orphan*/  aes_free_context (TYPE_2__*) ; 
 int /*<<< orphan*/  aes_xor_block ; 
 int ccm_encrypt_final (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ctr_mode_final (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int gcm_encrypt_final (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aes_encrypt_final(crypto_ctx_t *ctx, crypto_data_t *data,
    crypto_req_handle_t req)
{
	aes_ctx_t *aes_ctx;
	int ret;

	ASSERT(ctx->cc_provider_private != NULL);
	aes_ctx = ctx->cc_provider_private;

	if (data->cd_format != CRYPTO_DATA_RAW &&
	    data->cd_format != CRYPTO_DATA_UIO) {
		return (CRYPTO_ARGUMENTS_BAD);
	}

	if (aes_ctx->ac_flags & CTR_MODE) {
		if (aes_ctx->ac_remainder_len > 0) {
			ret = ctr_mode_final((ctr_ctx_t *)aes_ctx, data,
			    aes_encrypt_block);
			if (ret != CRYPTO_SUCCESS)
				return (ret);
		}
	} else if (aes_ctx->ac_flags & CCM_MODE) {
		ret = ccm_encrypt_final((ccm_ctx_t *)aes_ctx, data,
		    AES_BLOCK_LEN, aes_encrypt_block, aes_xor_block);
		if (ret != CRYPTO_SUCCESS) {
			return (ret);
		}
	} else if (aes_ctx->ac_flags & (GCM_MODE|GMAC_MODE)) {
		size_t saved_offset = data->cd_offset;

		ret = gcm_encrypt_final((gcm_ctx_t *)aes_ctx, data,
		    AES_BLOCK_LEN, aes_encrypt_block, aes_copy_block,
		    aes_xor_block);
		if (ret != CRYPTO_SUCCESS) {
			return (ret);
		}
		data->cd_length = data->cd_offset - saved_offset;
		data->cd_offset = saved_offset;
	} else {
		/*
		 * There must be no unprocessed plaintext.
		 * This happens if the length of the last data is
		 * not a multiple of the AES block length.
		 */
		if (aes_ctx->ac_remainder_len > 0) {
			return (CRYPTO_DATA_LEN_RANGE);
		}
		data->cd_length = 0;
	}

	(void) aes_free_context(ctx);

	return (CRYPTO_SUCCESS);
}