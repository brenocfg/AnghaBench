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
fletcher_4_superscalar_fini(fletcher_4_ctx_t *ctx, zio_cksum_t *zcp)
{
	uint64_t A, B, C, D;
	A = ctx->superscalar[0].v[0] + ctx->superscalar[0].v[1];
	B = 2 * ctx->superscalar[1].v[0] + 2 * ctx->superscalar[1].v[1] -
	    ctx->superscalar[0].v[1];
	C = 4 * ctx->superscalar[2].v[0] - ctx->superscalar[1].v[0] +
	    4 * ctx->superscalar[2].v[1] - 3 * ctx->superscalar[1].v[1];
	D = 8 * ctx->superscalar[3].v[0] - 4 * ctx->superscalar[2].v[0] +
	    8 * ctx->superscalar[3].v[1] - 8 * ctx->superscalar[2].v[1] +
	    ctx->superscalar[1].v[1];
	ZIO_SET_CHECKSUM(zcp, A, B, C, D);
}