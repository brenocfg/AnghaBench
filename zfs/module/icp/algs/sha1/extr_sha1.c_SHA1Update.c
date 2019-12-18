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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  const* buf8; } ;
struct TYPE_7__ {int* count; TYPE_1__ buf_un; } ;
typedef  TYPE_2__ SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1_TRANSFORM (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SHA1_TRANSFORM_BLOCKS (TYPE_2__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

void
SHA1Update(SHA1_CTX *ctx, const void *inptr, size_t input_len)
{
	uint32_t i, buf_index, buf_len;
	const uint8_t *input = inptr;
#if defined(__amd64)
	uint32_t	block_count;
#endif	/* __amd64 */

	/* check for noop */
	if (input_len == 0)
		return;

	/* compute number of bytes mod 64 */
	buf_index = (ctx->count[1] >> 3) & 0x3F;

	/* update number of bits */
	if ((ctx->count[1] += (input_len << 3)) < (input_len << 3))
		ctx->count[0]++;

	ctx->count[0] += (input_len >> 29);

	buf_len = 64 - buf_index;

	/* transform as many times as possible */
	i = 0;
	if (input_len >= buf_len) {

		/*
		 * general optimization:
		 *
		 * only do initial bcopy() and SHA1Transform() if
		 * buf_index != 0.  if buf_index == 0, we're just
		 * wasting our time doing the bcopy() since there
		 * wasn't any data left over from a previous call to
		 * SHA1Update().
		 */

		if (buf_index) {
			bcopy(input, &ctx->buf_un.buf8[buf_index], buf_len);
			SHA1_TRANSFORM(ctx, ctx->buf_un.buf8);
			i = buf_len;
		}

#if !defined(__amd64)
		for (; i + 63 < input_len; i += 64)
			SHA1_TRANSFORM(ctx, &input[i]);
#else
		block_count = (input_len - i) >> 6;
		if (block_count > 0) {
			SHA1_TRANSFORM_BLOCKS(ctx, &input[i], block_count);
			i += block_count << 6;
		}
#endif	/* !__amd64 */

		/*
		 * general optimization:
		 *
		 * if i and input_len are the same, return now instead
		 * of calling bcopy(), since the bcopy() in this case
		 * will be an expensive nop.
		 */

		if (input_len == i)
			return;

		buf_index = 0;
	}

	/* buffer remaining input */
	bcopy(&input[i], &ctx->buf_un.buf8[buf_index], input_len - i);
}