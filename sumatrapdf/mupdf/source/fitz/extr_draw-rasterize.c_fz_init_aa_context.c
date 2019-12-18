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
struct TYPE_4__ {int hscale; int vscale; int scale; int bits; int text_bits; } ;
struct TYPE_5__ {TYPE_1__ aa; } ;
typedef  TYPE_2__ fz_context ;

/* Variables and functions */

void fz_init_aa_context(fz_context *ctx)
{
#ifndef AA_BITS
	ctx->aa.hscale = 17;
	ctx->aa.vscale = 15;
	ctx->aa.scale = 256;
	ctx->aa.bits = 8;
	ctx->aa.text_bits = 8;
#endif
}