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
typedef  int ulong_t ;
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uchar_t ;
struct TYPE_3__ {int ccm_mac_len; int ccm_data_len; int ccm_counter_mask; scalar_t__ ccm_cb; } ;
typedef  TYPE_1__ ccm_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int htonll (int) ; 

__attribute__((used)) static void
ccm_format_initial_blocks(uchar_t *nonce, ulong_t nonceSize,
    ulong_t authDataSize, uint8_t *b0, ccm_ctx_t *aes_ctx)
{
	uint64_t payloadSize;
	uint8_t t, q, have_adata = 0;
	size_t limit;
	int i, j, k;
	uint64_t mask = 0;
	uint8_t *cb;

	q = (uint8_t)((15 - nonceSize) & 0xFF);
	t = (uint8_t)((aes_ctx->ccm_mac_len) & 0xFF);

	/* Construct the first octet of b0 */
	if (authDataSize > 0) {
		have_adata = 1;
	}
	b0[0] = (have_adata << 6) | (((t - 2)  / 2) << 3) | (q - 1);

	/* copy the nonce value into b0 */
	bcopy(nonce, &(b0[1]), nonceSize);

	/* store the length of the payload into b0 */
	bzero(&(b0[1+nonceSize]), q);

	payloadSize = aes_ctx->ccm_data_len;
	limit = 8 < q ? 8 : q;

	for (i = 0, j = 0, k = 15; i < limit; i++, j += 8, k--) {
		b0[k] = (uint8_t)((payloadSize >> j) & 0xFF);
	}

	/* format the counter block */

	cb = (uint8_t *)aes_ctx->ccm_cb;

	cb[0] = 0x07 & (q-1); /* first byte */

	/* copy the nonce value into the counter block */
	bcopy(nonce, &(cb[1]), nonceSize);

	bzero(&(cb[1+nonceSize]), q);

	/* Create the mask for the counter field based on the size of nonce */
	q <<= 3;
	while (q-- > 0) {
		mask |= (1ULL << q);
	}

#ifdef _LITTLE_ENDIAN
	mask = htonll(mask);
#endif
	aes_ctx->ccm_counter_mask = mask;

	/*
	 * During calculation, we start using counter block 1, we will
	 * set it up right here.
	 * We can just set the last byte to have the value 1, because
	 * even with the biggest nonce of 13, the last byte of the
	 * counter block will be used for the counter value.
	 */
	cb[15] = 0x01;
}