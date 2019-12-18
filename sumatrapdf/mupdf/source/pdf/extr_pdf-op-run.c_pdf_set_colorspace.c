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
struct TYPE_7__ {int gtop; TYPE_3__* gstate; } ;
typedef  TYPE_1__ pdf_run_processor ;
struct TYPE_8__ {int* v; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ pdf_material ;
struct TYPE_9__ {TYPE_2__ stroke; TYPE_2__ fill; } ;
typedef  TYPE_3__ pdf_gstate ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int PDF_FILL ; 
 int /*<<< orphan*/  PDF_MAT_COLOR ; 
 int fz_colorspace_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_keep_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* pdf_flush_text (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ pdf_is_tint_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pdf_set_colorspace(fz_context *ctx, pdf_run_processor *pr, int what, fz_colorspace *colorspace)
{
	pdf_gstate *gstate = pr->gstate + pr->gtop;
	pdf_material *mat;
	int n = fz_colorspace_n(ctx, colorspace);

	gstate = pdf_flush_text(ctx, pr);

	mat = what == PDF_FILL ? &gstate->fill : &gstate->stroke;

	fz_drop_colorspace(ctx, mat->colorspace);

	mat->kind = PDF_MAT_COLOR;
	mat->colorspace = fz_keep_colorspace(ctx, colorspace);

	mat->v[0] = 0;
	mat->v[1] = 0;
	mat->v[2] = 0;
	mat->v[3] = 1;

	if (pdf_is_tint_colorspace(ctx, colorspace))
	{
		int i;
		for (i = 0; i < n; i++)
			mat->v[i] = 1.0f;
	}
}