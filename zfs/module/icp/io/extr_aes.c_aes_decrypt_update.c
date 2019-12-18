#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  void* off_t ;
typedef  int /*<<< orphan*/  gcm_ctx_t ;
typedef  int /*<<< orphan*/  ctr_ctx_t ;
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
struct TYPE_16__ {size_t cd_length; void* cd_offset; int cd_format; } ;
typedef  TYPE_1__ crypto_data_t ;
struct TYPE_17__ {TYPE_3__* cc_provider_private; } ;
typedef  TYPE_2__ crypto_ctx_t ;
struct TYPE_18__ {int ac_flags; size_t ac_remainder_len; } ;
typedef  TYPE_3__ aes_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  AES_ARG_INPLACE (TYPE_1__*,TYPE_1__*) ; 
 int AES_BLOCK_LEN ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int CCM_MODE ; 
 int CRYPTO_ARGUMENTS_BAD ; 
 int CRYPTO_BUFFER_TOO_SMALL ; 
 int CRYPTO_DATA_LEN_RANGE ; 
#define  CRYPTO_DATA_RAW 129 
#define  CRYPTO_DATA_UIO 128 
 int CRYPTO_ENCRYPTED_DATA_LEN_RANGE ; 
 int CRYPTO_SUCCESS ; 
 int CTR_MODE ; 
 int GCM_MODE ; 
 int GMAC_MODE ; 
 int /*<<< orphan*/  aes_copy_block64 ; 
 int /*<<< orphan*/  aes_decrypt_contiguous_blocks ; 
 int /*<<< orphan*/  aes_encrypt_block ; 
 int /*<<< orphan*/  crypto_kmflag (int /*<<< orphan*/ ) ; 
 int crypto_update_iov (TYPE_3__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_update_uio (TYPE_3__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ctr_mode_final (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcm_set_kmflag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aes_decrypt_update(crypto_ctx_t *ctx, crypto_data_t *ciphertext,
    crypto_data_t *plaintext, crypto_req_handle_t req)
{
	off_t saved_offset;
	size_t saved_length, out_len;
	int ret = CRYPTO_SUCCESS;
	aes_ctx_t *aes_ctx;

	ASSERT(ctx->cc_provider_private != NULL);
	aes_ctx = ctx->cc_provider_private;

	AES_ARG_INPLACE(ciphertext, plaintext);

	/*
	 * Compute number of bytes that will hold the plaintext.
	 * This is not necessary for CCM, GCM, and GMAC since these
	 * mechanisms never return plaintext for update operations.
	 */
	if ((aes_ctx->ac_flags & (CCM_MODE|GCM_MODE|GMAC_MODE)) == 0) {
		out_len = aes_ctx->ac_remainder_len;
		out_len += ciphertext->cd_length;
		out_len &= ~(AES_BLOCK_LEN - 1);

		/* return length needed to store the output */
		if (plaintext->cd_length < out_len) {
			plaintext->cd_length = out_len;
			return (CRYPTO_BUFFER_TOO_SMALL);
		}
	}

	saved_offset = plaintext->cd_offset;
	saved_length = plaintext->cd_length;

	if (aes_ctx->ac_flags & (GCM_MODE|GMAC_MODE))
		gcm_set_kmflag((gcm_ctx_t *)aes_ctx, crypto_kmflag(req));

	/*
	 * Do the AES update on the specified input data.
	 */
	switch (ciphertext->cd_format) {
	case CRYPTO_DATA_RAW:
		ret = crypto_update_iov(ctx->cc_provider_private,
		    ciphertext, plaintext, aes_decrypt_contiguous_blocks,
		    aes_copy_block64);
		break;
	case CRYPTO_DATA_UIO:
		ret = crypto_update_uio(ctx->cc_provider_private,
		    ciphertext, plaintext, aes_decrypt_contiguous_blocks,
		    aes_copy_block64);
		break;
	default:
		ret = CRYPTO_ARGUMENTS_BAD;
	}

	/*
	 * Since AES counter mode is a stream cipher, we call
	 * ctr_mode_final() to pick up any remaining bytes.
	 * It is an internal function that does not destroy
	 * the context like *normal* final routines.
	 */
	if ((aes_ctx->ac_flags & CTR_MODE) && (aes_ctx->ac_remainder_len > 0)) {
		ret = ctr_mode_final((ctr_ctx_t *)aes_ctx, plaintext,
		    aes_encrypt_block);
		if (ret == CRYPTO_DATA_LEN_RANGE)
			ret = CRYPTO_ENCRYPTED_DATA_LEN_RANGE;
	}

	if (ret == CRYPTO_SUCCESS) {
		if (ciphertext != plaintext)
			plaintext->cd_length =
			    plaintext->cd_offset - saved_offset;
	} else {
		plaintext->cd_length = saved_length;
	}
	plaintext->cd_offset = saved_offset;


	return (ret);
}