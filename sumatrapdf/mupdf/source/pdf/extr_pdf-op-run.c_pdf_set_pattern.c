#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  gparent; } ;
typedef  TYPE_1__ pdf_run_processor ;
typedef  int /*<<< orphan*/  pdf_pattern ;
struct TYPE_9__ {int /*<<< orphan*/  gstate_num; int /*<<< orphan*/ * pattern; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ pdf_material ;
struct TYPE_10__ {TYPE_2__ stroke; TYPE_2__ fill; } ;
typedef  TYPE_3__ pdf_gstate ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int PDF_FILL ; 
 int /*<<< orphan*/  PDF_MAT_PATTERN ; 
 int /*<<< orphan*/  pdf_drop_pattern (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* pdf_flush_text (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * pdf_keep_pattern (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_set_color (int /*<<< orphan*/ *,TYPE_1__*,int,float*) ; 

__attribute__((used)) static void
pdf_set_pattern(fz_context *ctx, pdf_run_processor *pr, int what, pdf_pattern *pat, float *v)
{
	pdf_gstate *gs;
	pdf_material *mat;

	gs = pdf_flush_text(ctx, pr);

	mat = what == PDF_FILL ? &gs->fill : &gs->stroke;

	pdf_drop_pattern(ctx, mat->pattern);
	mat->pattern = NULL;

	mat->kind = PDF_MAT_PATTERN;
	if (pat)
		mat->pattern = pdf_keep_pattern(ctx, pat);

	if (v)
		pdf_set_color(ctx, pr, what, v);

	mat->gstate_num = pr->gparent;
}