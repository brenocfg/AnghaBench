#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  const* buf8; } ;
struct TYPE_9__ {int* c32; int* c64; } ;
struct TYPE_11__ {scalar_t__ algotype; TYPE_2__ buf_un; TYPE_1__ count; } ;
typedef  TYPE_3__ SHA2_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA256Transform (TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SHA256TransformBlocks (TYPE_3__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ SHA256_HMAC_GEN_MECH_INFO_TYPE ; 
 int /*<<< orphan*/  SHA512Transform (TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SHA512TransformBlocks (TYPE_3__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

void
SHA2Update(SHA2_CTX *ctx, const void *inptr, size_t input_len)
{
	uint32_t	i, buf_index, buf_len, buf_limit;
	const uint8_t	*input = inptr;
	uint32_t	algotype = ctx->algotype;

	/* check for noop */
	if (input_len == 0)
		return;

	if (algotype <= SHA256_HMAC_GEN_MECH_INFO_TYPE) {
		buf_limit = 64;

		/* compute number of bytes mod 64 */
		buf_index = (ctx->count.c32[1] >> 3) & 0x3F;

		/* update number of bits */
		if ((ctx->count.c32[1] += (input_len << 3)) < (input_len << 3))
			ctx->count.c32[0]++;

		ctx->count.c32[0] += (input_len >> 29);

	} else {
		buf_limit = 128;

		/* compute number of bytes mod 128 */
		buf_index = (ctx->count.c64[1] >> 3) & 0x7F;

		/* update number of bits */
		if ((ctx->count.c64[1] += (input_len << 3)) < (input_len << 3))
			ctx->count.c64[0]++;

		ctx->count.c64[0] += (input_len >> 29);
	}

	buf_len = buf_limit - buf_index;

	/* transform as many times as possible */
	i = 0;
	if (input_len >= buf_len) {

		/*
		 * general optimization:
		 *
		 * only do initial bcopy() and SHA2Transform() if
		 * buf_index != 0.  if buf_index == 0, we're just
		 * wasting our time doing the bcopy() since there
		 * wasn't any data left over from a previous call to
		 * SHA2Update().
		 */
		if (buf_index) {
			bcopy(input, &ctx->buf_un.buf8[buf_index], buf_len);
			if (algotype <= SHA256_HMAC_GEN_MECH_INFO_TYPE)
				SHA256Transform(ctx, ctx->buf_un.buf8);
			else
				SHA512Transform(ctx, ctx->buf_un.buf8);

			i = buf_len;
		}

#if !defined(__amd64) || !defined(_KERNEL)
		if (algotype <= SHA256_HMAC_GEN_MECH_INFO_TYPE) {
			for (; i + buf_limit - 1 < input_len; i += buf_limit) {
				SHA256Transform(ctx, &input[i]);
			}
		} else {
			for (; i + buf_limit - 1 < input_len; i += buf_limit) {
				SHA512Transform(ctx, &input[i]);
			}
		}

#else
		uint32_t block_count;
		if (algotype <= SHA256_HMAC_GEN_MECH_INFO_TYPE) {
			block_count = (input_len - i) >> 6;
			if (block_count > 0) {
				SHA256TransformBlocks(ctx, &input[i],
				    block_count);
				i += block_count << 6;
			}
		} else {
			block_count = (input_len - i) >> 7;
			if (block_count > 0) {
				SHA512TransformBlocks(ctx, &input[i],
				    block_count);
				i += block_count << 7;
			}
		}
#endif	/* !__amd64 || !_KERNEL */

		/*
		 * general optimization:
		 *
		 * if i and input_len are the same, return now instead
		 * of calling bcopy(), since the bcopy() in this case
		 * will be an expensive noop.
		 */

		if (input_len == i)
			return;

		buf_index = 0;
	}

	/* buffer remaining input */
	bcopy(&input[i], &ctx->buf_un.buf8[buf_index], input_len - i);
}