#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_storable ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_9__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  profile; } ;
struct TYPE_8__ {TYPE_5__** colorant; int /*<<< orphan*/  tint; int /*<<< orphan*/  (* drop ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  base; } ;
struct TYPE_7__ {TYPE_5__* lookup; int /*<<< orphan*/  base; } ;
struct TYPE_10__ {TYPE_3__ icc; TYPE_2__ separation; TYPE_1__ indexed; } ;
struct TYPE_11__ {scalar_t__ type; int flags; struct TYPE_11__* name; TYPE_4__ u; } ;
typedef  TYPE_5__ fz_colorspace ;

/* Variables and functions */
 scalar_t__ FZ_COLORSPACE_INDEXED ; 
 int FZ_COLORSPACE_IS_ICC ; 
 scalar_t__ FZ_COLORSPACE_SEPARATION ; 
 int FZ_MAX_COLORS ; 
 int /*<<< orphan*/  fz_drop_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_icc_profile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
fz_drop_colorspace_imp(fz_context *ctx, fz_storable *cs_)
{
	fz_colorspace *cs = (fz_colorspace *)cs_;
	int i;

	if (cs->type == FZ_COLORSPACE_INDEXED)
	{
		fz_drop_colorspace(ctx, cs->u.indexed.base);
		fz_free(ctx, cs->u.indexed.lookup);
	}
	if (cs->type == FZ_COLORSPACE_SEPARATION)
	{
		fz_drop_colorspace(ctx, cs->u.separation.base);
		cs->u.separation.drop(ctx, cs->u.separation.tint);
		for (i = 0; i < FZ_MAX_COLORS; i++)
			fz_free(ctx, cs->u.separation.colorant[i]);
	}
#if FZ_ENABLE_ICC
	if (cs->flags & FZ_COLORSPACE_IS_ICC)
	{
		fz_drop_icc_profile(ctx, cs->u.icc.profile);
		fz_drop_buffer(ctx, cs->u.icc.buffer);
	}
#endif

	fz_free(ctx, cs->name);
	fz_free(ctx, cs);
}