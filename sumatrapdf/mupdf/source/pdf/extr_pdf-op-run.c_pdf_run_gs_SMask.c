#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_run_processor ;
typedef  int /*<<< orphan*/  pdf_processor ;
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_3__ {float* softmask_bc; int luminosity; int /*<<< orphan*/ * softmask_resources; int /*<<< orphan*/ * softmask; int /*<<< orphan*/  ctm; int /*<<< orphan*/  softmask_ctm; } ;
typedef  TYPE_1__ pdf_gstate ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int fz_colorspace_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* pdf_flush_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* pdf_keep_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_xobject_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pdf_run_gs_SMask(fz_context *ctx, pdf_processor *proc, pdf_obj *smask, pdf_obj *page_resources, float *bc, int luminosity)
{
	pdf_run_processor *pr = (pdf_run_processor *)proc;
	pdf_gstate *gstate = pdf_flush_text(ctx, pr);
	int i;

	if (gstate->softmask)
	{
		pdf_drop_obj(ctx, gstate->softmask);
		gstate->softmask = NULL;
		pdf_drop_obj(ctx, gstate->softmask_resources);
		gstate->softmask_resources = NULL;
	}

	if (smask)
	{
		fz_colorspace *cs = pdf_xobject_colorspace(ctx, smask);
		int cs_n = 1;
		if (cs)
			cs_n = fz_colorspace_n(ctx, cs);
		gstate->softmask_ctm = gstate->ctm;
		gstate->softmask = pdf_keep_obj(ctx, smask);
		gstate->softmask_resources = pdf_keep_obj(ctx, page_resources);
		for (i = 0; i < cs_n; ++i)
			gstate->softmask_bc[i] = bc[i];
		gstate->luminosity = luminosity;
		fz_drop_colorspace(ctx, cs);
	}
}