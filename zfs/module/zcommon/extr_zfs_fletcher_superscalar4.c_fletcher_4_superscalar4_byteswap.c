#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {TYPE_1__* superscalar; } ;
typedef  TYPE_2__ fletcher_4_ctx_t ;
struct TYPE_4__ {int* v; } ;

/* Variables and functions */
 int BSWAP_32 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
fletcher_4_superscalar4_byteswap(fletcher_4_ctx_t *ctx,
    const void *buf, uint64_t size)
{
	const uint32_t *ip = buf;
	const uint32_t *ipend = ip + (size / sizeof (uint32_t));
	uint64_t a, b, c, d;
	uint64_t a2, b2, c2, d2;
	uint64_t a3, b3, c3, d3;
	uint64_t a4, b4, c4, d4;

	a = ctx->superscalar[0].v[0];
	b = ctx->superscalar[1].v[0];
	c = ctx->superscalar[2].v[0];
	d = ctx->superscalar[3].v[0];
	a2 = ctx->superscalar[0].v[1];
	b2 = ctx->superscalar[1].v[1];
	c2 = ctx->superscalar[2].v[1];
	d2 = ctx->superscalar[3].v[1];
	a3 = ctx->superscalar[0].v[2];
	b3 = ctx->superscalar[1].v[2];
	c3 = ctx->superscalar[2].v[2];
	d3 = ctx->superscalar[3].v[2];
	a4 = ctx->superscalar[0].v[3];
	b4 = ctx->superscalar[1].v[3];
	c4 = ctx->superscalar[2].v[3];
	d4 = ctx->superscalar[3].v[3];

	for (; ip < ipend; ip += 4) {
		a += BSWAP_32(ip[0]);
		a2 += BSWAP_32(ip[1]);
		a3 += BSWAP_32(ip[2]);
		a4 += BSWAP_32(ip[3]);
		b += a;
		b2 += a2;
		b3 += a3;
		b4 += a4;
		c += b;
		c2 += b2;
		c3 += b3;
		c4 += b4;
		d += c;
		d2 += c2;
		d3 += c3;
		d4 += c4;
	}

	ctx->superscalar[0].v[0] = a;
	ctx->superscalar[1].v[0] = b;
	ctx->superscalar[2].v[0] = c;
	ctx->superscalar[3].v[0] = d;
	ctx->superscalar[0].v[1] = a2;
	ctx->superscalar[1].v[1] = b2;
	ctx->superscalar[2].v[1] = c2;
	ctx->superscalar[3].v[1] = d2;
	ctx->superscalar[0].v[2] = a3;
	ctx->superscalar[1].v[2] = b3;
	ctx->superscalar[2].v[2] = c3;
	ctx->superscalar[3].v[2] = d3;
	ctx->superscalar[0].v[3] = a4;
	ctx->superscalar[1].v[3] = b4;
	ctx->superscalar[2].v[3] = c4;
	ctx->superscalar[3].v[3] = d4;
}