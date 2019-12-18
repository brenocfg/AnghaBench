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
typedef  char uint8_t ;
struct TYPE_3__ {size_t gcm_pt_buf_len; char* gcm_pt_buf; size_t gcm_processed_data_len; scalar_t__ gcm_remainder_len; int /*<<< orphan*/  gcm_kmflag; } ;
typedef  TYPE_1__ gcm_ctx_t ;
typedef  int /*<<< orphan*/  crypto_data_t ;

/* Variables and functions */
 int CRYPTO_HOST_MEMORY ; 
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 char* vmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_free (char*,size_t) ; 

int
gcm_mode_decrypt_contiguous_blocks(gcm_ctx_t *ctx, char *data, size_t length,
    crypto_data_t *out, size_t block_size,
    int (*encrypt_block)(const void *, const uint8_t *, uint8_t *),
    void (*copy_block)(uint8_t *, uint8_t *),
    void (*xor_block)(uint8_t *, uint8_t *))
{
	size_t new_len;
	uint8_t *new;

	/*
	 * Copy contiguous ciphertext input blocks to plaintext buffer.
	 * Ciphertext will be decrypted in the final.
	 */
	if (length > 0) {
		new_len = ctx->gcm_pt_buf_len + length;
		new = vmem_alloc(new_len, ctx->gcm_kmflag);
		bcopy(ctx->gcm_pt_buf, new, ctx->gcm_pt_buf_len);
		vmem_free(ctx->gcm_pt_buf, ctx->gcm_pt_buf_len);
		if (new == NULL)
			return (CRYPTO_HOST_MEMORY);

		ctx->gcm_pt_buf = new;
		ctx->gcm_pt_buf_len = new_len;
		bcopy(data, &ctx->gcm_pt_buf[ctx->gcm_processed_data_len],
		    length);
		ctx->gcm_processed_data_len += length;
	}

	ctx->gcm_remainder_len = 0;
	return (CRYPTO_SUCCESS);
}