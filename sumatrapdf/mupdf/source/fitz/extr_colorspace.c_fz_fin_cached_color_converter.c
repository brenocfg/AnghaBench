#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {TYPE_2__* opaque; } ;
typedef  TYPE_1__ fz_color_converter ;
struct TYPE_6__ {int /*<<< orphan*/  base; int /*<<< orphan*/  hash; } ;
typedef  TYPE_2__ fz_cached_color_converter ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_color_converter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_hash_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_2__*) ; 

void fz_fin_cached_color_converter(fz_context *ctx, fz_color_converter *cc_)
{
	fz_cached_color_converter *cc;
	if (cc_ == NULL)
		return;
	cc = cc_->opaque;
	if (cc == NULL)
		return;
	cc_->opaque = NULL;
	fz_drop_hash_table(ctx, cc->hash);
	fz_drop_color_converter(ctx, &cc->base);
	fz_free(ctx, cc);
}