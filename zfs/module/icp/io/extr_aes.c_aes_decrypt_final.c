#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* off_t ;
struct TYPE_12__ {size_t gcm_processed_data_len; size_t gcm_tag_len; } ;
typedef  TYPE_1__ gcm_ctx_t ;
typedef  int /*<<< orphan*/  ctr_ctx_t ;
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
struct TYPE_13__ {scalar_t__ cd_format; size_t cd_length; void* cd_offset; } ;
typedef  TYPE_2__ crypto_data_t ;
struct TYPE_14__ {TYPE_4__* cc_provider_private; } ;
typedef  TYPE_3__ crypto_ctx_t ;
typedef  int /*<<< orphan*/  ccm_ctx_t ;
struct TYPE_15__ {scalar_t__ ac_remainder_len; int ac_flags; size_t ac_data_len; size_t ac_processed_data_len; scalar_t__ ac_processed_mac_len; scalar_t__ ac_mac_len; } ;
typedef  TYPE_4__ aes_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_LEN ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int CCM_MODE ; 
 int CRYPTO_ARGUMENTS_BAD ; 
 int CRYPTO_BUFFER_TOO_SMALL ; 
 int CRYPTO_DATA_LEN_RANGE ; 
 scalar_t__ CRYPTO_DATA_RAW ; 
 scalar_t__ CRYPTO_DATA_UIO ; 
 int CRYPTO_ENCRYPTED_DATA_LEN_RANGE ; 
 int CRYPTO_SUCCESS ; 
 int CTR_MODE ; 
 int GCM_MODE ; 
 int GMAC_MODE ; 
 int /*<<< orphan*/  aes_copy_block ; 
 int /*<<< orphan*/  aes_encrypt_block ; 
 int /*<<< orphan*/  aes_free_context (TYPE_3__*) ; 
 int /*<<< orphan*/  aes_xor_block ; 
 int ccm_decrypt_final (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ctr_mode_final (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int gcm_decrypt_final (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aes_decrypt_final(crypto_ctx_t *ctx, crypto_data_t *data,
    crypto_req_handle_t req)
{
	aes_ctx_t *aes_ctx;
	int ret;
	off_t saved_offset;
	size_t saved_length;

	ASSERT(ctx->cc_provider_private != NULL);
	aes_ctx = ctx->cc_provider_private;

	if (data->cd_format != CRYPTO_DATA_RAW &&
	    data->cd_format != CRYPTO_DATA_UIO) {
		return (CRYPTO_ARGUMENTS_BAD);
	}

	/*
	 * There must be no unprocessed ciphertext.
	 * This happens if the length of the last ciphertext is
	 * not a multiple of the AES block length.
	 */
	if (aes_ctx->ac_remainder_len > 0) {
		if ((aes_ctx->ac_flags & CTR_MODE) == 0)
			return (CRYPTO_ENCRYPTED_DATA_LEN_RANGE);
		else {
			ret = ctr_mode_final((ctr_ctx_t *)aes_ctx, data,
			    aes_encrypt_block);
			if (ret == CRYPTO_DATA_LEN_RANGE)
				ret = CRYPTO_ENCRYPTED_DATA_LEN_RANGE;
			if (ret != CRYPTO_SUCCESS)
				return (ret);
		}
	}

	if (aes_ctx->ac_flags & CCM_MODE) {
		/*
		 * This is where all the plaintext is returned, make sure
		 * the plaintext buffer is big enough
		 */
		size_t pt_len = aes_ctx->ac_data_len;
		if (data->cd_length < pt_len) {
			data->cd_length = pt_len;
			return (CRYPTO_BUFFER_TOO_SMALL);
		}

		ASSERT(aes_ctx->ac_processed_data_len == pt_len);
		ASSERT(aes_ctx->ac_processed_mac_len == aes_ctx->ac_mac_len);
		saved_offset = data->cd_offset;
		saved_length = data->cd_length;
		ret = ccm_decrypt_final((ccm_ctx_t *)aes_ctx, data,
		    AES_BLOCK_LEN, aes_encrypt_block, aes_copy_block,
		    aes_xor_block);
		if (ret == CRYPTO_SUCCESS) {
			data->cd_length = data->cd_offset - saved_offset;
		} else {
			data->cd_length = saved_length;
		}

		data->cd_offset = saved_offset;
		if (ret != CRYPTO_SUCCESS) {
			return (ret);
		}
	} else if (aes_ctx->ac_flags & (GCM_MODE|GMAC_MODE)) {
		/*
		 * This is where all the plaintext is returned, make sure
		 * the plaintext buffer is big enough
		 */
		gcm_ctx_t *ctx = (gcm_ctx_t *)aes_ctx;
		size_t pt_len = ctx->gcm_processed_data_len - ctx->gcm_tag_len;

		if (data->cd_length < pt_len) {
			data->cd_length = pt_len;
			return (CRYPTO_BUFFER_TOO_SMALL);
		}

		saved_offset = data->cd_offset;
		saved_length = data->cd_length;
		ret = gcm_decrypt_final((gcm_ctx_t *)aes_ctx, data,
		    AES_BLOCK_LEN, aes_encrypt_block, aes_xor_block);
		if (ret == CRYPTO_SUCCESS) {
			data->cd_length = data->cd_offset - saved_offset;
		} else {
			data->cd_length = saved_length;
		}

		data->cd_offset = saved_offset;
		if (ret != CRYPTO_SUCCESS) {
			return (ret);
		}
	}


	if ((aes_ctx->ac_flags & (CTR_MODE|CCM_MODE|GCM_MODE|GMAC_MODE)) == 0) {
		data->cd_length = 0;
	}

	(void) aes_free_context(ctx);

	return (CRYPTO_SUCCESS);
}