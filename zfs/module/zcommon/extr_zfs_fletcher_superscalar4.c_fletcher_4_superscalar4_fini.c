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
typedef  int /*<<< orphan*/  zio_cksum_t ;
typedef  int uint64_t ;
struct TYPE_5__ {TYPE_1__* superscalar; } ;
typedef  TYPE_2__ fletcher_4_ctx_t ;
struct TYPE_4__ {int* v; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIO_SET_CHECKSUM (int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static void
fletcher_4_superscalar4_fini(fletcher_4_ctx_t *ctx, zio_cksum_t *zcp)
{
	uint64_t A, B, C, D;

	A = ctx->superscalar[0].v[0] + ctx->superscalar[0].v[1] +
	    ctx->superscalar[0].v[2] + ctx->superscalar[0].v[3];
	B = 0 - ctx->superscalar[0].v[1] - 2 * ctx->superscalar[0].v[2] -
	    3 * ctx->superscalar[0].v[3] + 4 * ctx->superscalar[1].v[0] +
	    4 * ctx->superscalar[1].v[1] + 4 * ctx->superscalar[1].v[2] +
	    4 * ctx->superscalar[1].v[3];

	C = ctx->superscalar[0].v[2] + 3 * ctx->superscalar[0].v[3] -
	    6 * ctx->superscalar[1].v[0] - 10 * ctx->superscalar[1].v[1] -
	    14 * ctx->superscalar[1].v[2] - 18 * ctx->superscalar[1].v[3] +
	    16 * ctx->superscalar[2].v[0] + 16 * ctx->superscalar[2].v[1] +
	    16 * ctx->superscalar[2].v[2] + 16 * ctx->superscalar[2].v[3];

	D = 0 - ctx->superscalar[0].v[3] + 4 * ctx->superscalar[1].v[0] +
	    10 * ctx->superscalar[1].v[1] + 20 * ctx->superscalar[1].v[2] +
	    34 * ctx->superscalar[1].v[3] - 48 * ctx->superscalar[2].v[0] -
	    64 * ctx->superscalar[2].v[1] - 80 * ctx->superscalar[2].v[2] -
	    96 * ctx->superscalar[2].v[3] + 64 * ctx->superscalar[3].v[0] +
	    64 * ctx->superscalar[3].v[1] + 64 * ctx->superscalar[3].v[2] +
	    64 * ctx->superscalar[3].v[3];

	ZIO_SET_CHECKSUM(zcp, A, B, C, D);
}