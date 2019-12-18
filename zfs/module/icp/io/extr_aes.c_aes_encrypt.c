#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gcm_ctx_t ;
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
struct TYPE_15__ {int cd_length; size_t cd_offset; } ;
typedef  TYPE_1__ crypto_data_t ;
struct TYPE_16__ {TYPE_3__* cc_provider_private; } ;
typedef  TYPE_2__ crypto_ctx_t ;
typedef  int /*<<< orphan*/  ccm_ctx_t ;
struct TYPE_17__ {int ac_flags; size_t ac_tag_len; scalar_t__ ac_remainder_len; int /*<<< orphan*/  ac_mac_len; } ;
typedef  TYPE_3__ aes_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  AES_ARG_INPLACE (TYPE_1__*,TYPE_1__*) ; 
 int AES_BLOCK_LEN ; 
 int /*<<< orphan*/  ASSERT (int) ; 
#define  CCM_MODE 130 
 int CRYPTO_ARGUMENTS_BAD ; 
 int CRYPTO_BUFFER_TOO_SMALL ; 
 int CRYPTO_DATA_LEN_RANGE ; 
 int CRYPTO_FAILED ; 
 int CRYPTO_SUCCESS ; 
 int CTR_MODE ; 
#define  GCM_MODE 129 
#define  GMAC_MODE 128 
 int /*<<< orphan*/  aes_copy_block ; 
 int /*<<< orphan*/  aes_encrypt_block ; 
 int aes_encrypt_update (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aes_free_context (TYPE_2__*) ; 
 int /*<<< orphan*/  aes_xor_block ; 
 int ccm_encrypt_final (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gcm_encrypt_final (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aes_encrypt(crypto_ctx_t *ctx, crypto_data_t *plaintext,
    crypto_data_t *ciphertext, crypto_req_handle_t req)
{
	int ret = CRYPTO_FAILED;

	aes_ctx_t *aes_ctx;
	size_t saved_length, saved_offset, length_needed;

	ASSERT(ctx->cc_provider_private != NULL);
	aes_ctx = ctx->cc_provider_private;

	/*
	 * For block ciphers, plaintext must be a multiple of AES block size.
	 * This test is only valid for ciphers whose blocksize is a power of 2.
	 */
	if (((aes_ctx->ac_flags & (CTR_MODE|CCM_MODE|GCM_MODE|GMAC_MODE))
	    == 0) && (plaintext->cd_length & (AES_BLOCK_LEN - 1)) != 0)
		return (CRYPTO_DATA_LEN_RANGE);

	AES_ARG_INPLACE(plaintext, ciphertext);

	/*
	 * We need to just return the length needed to store the output.
	 * We should not destroy the context for the following case.
	 */
	switch (aes_ctx->ac_flags & (CCM_MODE|GCM_MODE|GMAC_MODE)) {
	case CCM_MODE:
		length_needed = plaintext->cd_length + aes_ctx->ac_mac_len;
		break;
	case GCM_MODE:
		length_needed = plaintext->cd_length + aes_ctx->ac_tag_len;
		break;
	case GMAC_MODE:
		if (plaintext->cd_length != 0)
			return (CRYPTO_ARGUMENTS_BAD);

		length_needed = aes_ctx->ac_tag_len;
		break;
	default:
		length_needed = plaintext->cd_length;
	}

	if (ciphertext->cd_length < length_needed) {
		ciphertext->cd_length = length_needed;
		return (CRYPTO_BUFFER_TOO_SMALL);
	}

	saved_length = ciphertext->cd_length;
	saved_offset = ciphertext->cd_offset;

	/*
	 * Do an update on the specified input data.
	 */
	ret = aes_encrypt_update(ctx, plaintext, ciphertext, req);
	if (ret != CRYPTO_SUCCESS) {
		return (ret);
	}

	/*
	 * For CCM mode, aes_ccm_encrypt_final() will take care of any
	 * left-over unprocessed data, and compute the MAC
	 */
	if (aes_ctx->ac_flags & CCM_MODE) {
		/*
		 * ccm_encrypt_final() will compute the MAC and append
		 * it to existing ciphertext. So, need to adjust the left over
		 * length value accordingly
		 */

		/* order of following 2 lines MUST not be reversed */
		ciphertext->cd_offset = ciphertext->cd_length;
		ciphertext->cd_length = saved_length - ciphertext->cd_length;
		ret = ccm_encrypt_final((ccm_ctx_t *)aes_ctx, ciphertext,
		    AES_BLOCK_LEN, aes_encrypt_block, aes_xor_block);
		if (ret != CRYPTO_SUCCESS) {
			return (ret);
		}

		if (plaintext != ciphertext) {
			ciphertext->cd_length =
			    ciphertext->cd_offset - saved_offset;
		}
		ciphertext->cd_offset = saved_offset;
	} else if (aes_ctx->ac_flags & (GCM_MODE|GMAC_MODE)) {
		/*
		 * gcm_encrypt_final() will compute the MAC and append
		 * it to existing ciphertext. So, need to adjust the left over
		 * length value accordingly
		 */

		/* order of following 2 lines MUST not be reversed */
		ciphertext->cd_offset = ciphertext->cd_length;
		ciphertext->cd_length = saved_length - ciphertext->cd_length;
		ret = gcm_encrypt_final((gcm_ctx_t *)aes_ctx, ciphertext,
		    AES_BLOCK_LEN, aes_encrypt_block, aes_copy_block,
		    aes_xor_block);
		if (ret != CRYPTO_SUCCESS) {
			return (ret);
		}

		if (plaintext != ciphertext) {
			ciphertext->cd_length =
			    ciphertext->cd_offset - saved_offset;
		}
		ciphertext->cd_offset = saved_offset;
	}

	ASSERT(aes_ctx->ac_remainder_len == 0);
	(void) aes_free_context(ctx);

	return (ret);
}