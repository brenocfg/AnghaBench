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
struct TYPE_4__ {int bytecount; int* buf; int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ SUM_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  sha256_transform (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  write_swap32 (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sha256_final(SUM_CONTEXT *ctx)
{
	uint64_t bitcount = ctx->bytecount << 3;
	size_t pos = ((size_t)ctx->bytecount) & 0x3F;
	unsigned char *p;

	ctx->buf[pos++] = 0x80;

	/* Pad whatever data is left in the buffer */
	while (pos != (64 - 8)) {
		pos &= 0x3F;
		if (pos == 0)
			sha256_transform(ctx, ctx->buf);
		ctx->buf[pos++] = 0;
	}

	/* Append to the padding the total message's length in bits and transform */
	ctx->buf[63] = (unsigned char) bitcount;
	ctx->buf[62] = (unsigned char) (bitcount >> 8);
	ctx->buf[61] = (unsigned char) (bitcount >> 16);
	ctx->buf[60] = (unsigned char) (bitcount >> 24);
	ctx->buf[59] = (unsigned char) (bitcount >> 32);
	ctx->buf[58] = (unsigned char) (bitcount >> 40);
	ctx->buf[57] = (unsigned char) (bitcount >> 48);
	ctx->buf[56] = (unsigned char) (bitcount >> 56);

	sha256_transform(ctx, ctx->buf);

	p = ctx->buf;
#ifdef BIG_ENDIAN_HOST
#define X(a) do { *(uint32_t*)p = ctx->state[a]; p += 4; } while(0)
#else
#define X(a) do { write_swap32(p, ctx->state[a]); p += 4; } while(0);
#endif
	X(0);
	X(1);
	X(2);
	X(3);
	X(4);
	X(5);
	X(6);
	X(7);
#undef X
}