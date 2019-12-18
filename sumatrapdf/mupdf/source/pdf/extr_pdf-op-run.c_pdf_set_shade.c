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
struct TYPE_7__ {int /*<<< orphan*/  gparent; } ;
typedef  TYPE_1__ pdf_run_processor ;
struct TYPE_8__ {int /*<<< orphan*/  gstate_num; int /*<<< orphan*/  shade; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ pdf_material ;
struct TYPE_9__ {TYPE_2__ stroke; TYPE_2__ fill; } ;
typedef  TYPE_3__ pdf_gstate ;
typedef  int /*<<< orphan*/  fz_shade ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int PDF_FILL ; 
 int /*<<< orphan*/  PDF_MAT_SHADE ; 
 int /*<<< orphan*/  fz_drop_shade (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_keep_shade (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* pdf_flush_text (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
pdf_set_shade(fz_context *ctx, pdf_run_processor *pr, int what, fz_shade *shade)
{
	pdf_gstate *gs;
	pdf_material *mat;

	gs = pdf_flush_text(ctx, pr);

	mat = what == PDF_FILL ? &gs->fill : &gs->stroke;

	fz_drop_shade(ctx, mat->shade);

	mat->kind = PDF_MAT_SHADE;
	mat->shade = fz_keep_shade(ctx, shade);

	mat->gstate_num = pr->gparent;
}