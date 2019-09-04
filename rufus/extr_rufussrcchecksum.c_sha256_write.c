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
struct TYPE_4__ {int bytecount; unsigned char* buf; } ;
typedef  TYPE_1__ SUM_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  PREFETCH64 (unsigned char const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  sha256_transform (TYPE_1__*,unsigned char const*) ; 

__attribute__((used)) static void sha256_write(SUM_CONTEXT *ctx, const unsigned char *buf, size_t len)
{
	size_t num = ctx->bytecount & 0x3f;

	/* Update bytecount */
	ctx->bytecount += len;

	/* Handle any leading odd-sized chunks */
	if (num) {
		unsigned char *p = ctx->buf + num;

		num = 64 - num;
		if (len < num) {
			memcpy(p, buf, len);
			return;
		}
		memcpy(p, buf, num);
		sha256_transform(ctx, ctx->buf);
		buf += num;
		len -= num;
	}

	/* Process data in 64-byte chunks */
	while (len >= 64) {
		PREFETCH64(buf + 64);
		sha256_transform(ctx, buf);
		buf += 64;
		len -= 64;
	}

	/* Handle any remaining bytes of data. */
	memcpy(ctx->buf, buf, len);
}