#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int bits; } ;
struct TYPE_11__ {TYPE_3__ aa; } ;
typedef  TYPE_1__ fz_rasterizer ;
struct TYPE_12__ {TYPE_3__ aa; } ;
typedef  TYPE_2__ fz_context ;
typedef  TYPE_3__ fz_aa_context ;

/* Variables and functions */
 int AA_BITS ; 
 int /*<<< orphan*/  FZ_EDGEBUFFER_ANY_PART_OF_PIXEL ; 
 int /*<<< orphan*/  FZ_EDGEBUFFER_CENTER_OF_PIXEL ; 
 TYPE_1__* fz_new_edgebuffer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* fz_new_gel (TYPE_2__*) ; 

fz_rasterizer *fz_new_rasterizer(fz_context *ctx, const fz_aa_context *aa)
{
	fz_rasterizer *r;
	int bits;

#ifdef AA_BITS
	bits = AA_BITS;
#else
	if (aa == NULL)
		aa = &ctx->aa;
	bits = aa->bits;
#endif
	if (bits == 10)
		r = fz_new_edgebuffer(ctx, FZ_EDGEBUFFER_ANY_PART_OF_PIXEL);
	else if (bits == 9)
		r = fz_new_edgebuffer(ctx, FZ_EDGEBUFFER_CENTER_OF_PIXEL);
	else
		r = fz_new_gel(ctx);
#ifndef AA_BITS
	r->aa = *aa;
#endif

	return r;
}