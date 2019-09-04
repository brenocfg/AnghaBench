#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int bytecount; unsigned char* buf; int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ SUM_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  md5_transform (TYPE_1__*,unsigned char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void md5_final(SUM_CONTEXT *ctx)
{
	size_t count = ((size_t)ctx->bytecount) & 0x3F;
	uint64_t bitcount = ctx->bytecount << 3;
	unsigned char *p;

	/* Set the first char of padding to 0x80.
	 * This is safe since there is always at least one byte free
	 */
	p = ctx->buf + count;
	*p++ = 0x80;

	/* Bytes of padding needed to make 64 bytes */
	count = 64 - 1 - count;

	/* Pad out to 56 mod 64 */
	if (count < 8) {
		/* Two lots of padding: Pad the first block to 64 bytes */
		memset(p, 0, count);
		md5_transform(ctx, ctx->buf);

		/* Now fill the next block with 56 bytes */
		memset(ctx->buf, 0, 56);
	} else {
		/* Pad block to 56 bytes */
		memset(p, 0, count - 8);
	}

	/* append the 64 bit count (little endian) */
	ctx->buf[56] = (unsigned char) bitcount;
	ctx->buf[57] = (unsigned char) (bitcount >> 8);
	ctx->buf[58] = (unsigned char) (bitcount >> 16);
	ctx->buf[59] = (unsigned char) (bitcount >> 24);
	ctx->buf[60] = (unsigned char) (bitcount >> 32);
	ctx->buf[61] = (unsigned char) (bitcount >> 40);
	ctx->buf[62] = (unsigned char) (bitcount >> 48);
	ctx->buf[63] = (unsigned char) (bitcount >> 56);

	md5_transform(ctx, ctx->buf);

	p = ctx->buf;
#ifdef BIG_ENDIAN_HOST
#define X(a) do { write_swap32(p, ctx->state[a]); p += 4; } while(0);
#else
#define X(a) do { *(uint32_t*)p = ctx->state[a]; p += 4; } while(0)
#endif
	X(0);
	X(1);
	X(2);
	X(3);
#undef X
}