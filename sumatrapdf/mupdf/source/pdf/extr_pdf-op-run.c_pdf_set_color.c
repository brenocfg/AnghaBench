#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int gtop; int /*<<< orphan*/  gparent; TYPE_3__* gstate; } ;
typedef  TYPE_1__ pdf_run_processor ;
struct TYPE_8__ {int kind; int /*<<< orphan*/  gstate_num; int /*<<< orphan*/  v; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_2__ pdf_material ;
struct TYPE_9__ {TYPE_2__ stroke; TYPE_2__ fill; } ;
typedef  TYPE_3__ pdf_gstate ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int PDF_FILL ; 
#define  PDF_MAT_COLOR 129 
#define  PDF_MAT_PATTERN 128 
 int /*<<< orphan*/  fz_clamp_color (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__* pdf_flush_text (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
pdf_set_color(fz_context *ctx, pdf_run_processor *pr, int what, float *v)
{
	pdf_gstate *gstate = pr->gstate + pr->gtop;
	pdf_material *mat;

	gstate = pdf_flush_text(ctx, pr);

	mat = what == PDF_FILL ? &gstate->fill : &gstate->stroke;

	switch (mat->kind)
	{
	case PDF_MAT_PATTERN:
	case PDF_MAT_COLOR:
		fz_clamp_color(ctx, mat->colorspace, v, mat->v);
		break;
	default:
		fz_warn(ctx, "color incompatible with material");
	}

	mat->gstate_num = pr->gparent;
}