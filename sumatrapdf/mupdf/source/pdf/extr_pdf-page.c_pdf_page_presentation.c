#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * obj; } ;
typedef  TYPE_1__ pdf_page ;
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_7__ {int duration; int vertical; int outwards; int /*<<< orphan*/  type; int /*<<< orphan*/  direction; } ;
typedef  TYPE_2__ fz_transition ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  Blinds ; 
 int /*<<< orphan*/  Box ; 
 int /*<<< orphan*/  Cover ; 
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  Di ; 
 int /*<<< orphan*/  Dissolve ; 
 int /*<<< orphan*/  Dm ; 
 int /*<<< orphan*/  Dur ; 
 int /*<<< orphan*/  FZ_TRANSITION_BLINDS ; 
 int /*<<< orphan*/  FZ_TRANSITION_BOX ; 
 int /*<<< orphan*/  FZ_TRANSITION_COVER ; 
 int /*<<< orphan*/  FZ_TRANSITION_DISSOLVE ; 
 int /*<<< orphan*/  FZ_TRANSITION_FADE ; 
 int /*<<< orphan*/  FZ_TRANSITION_FLY ; 
 int /*<<< orphan*/  FZ_TRANSITION_GLITTER ; 
 int /*<<< orphan*/  FZ_TRANSITION_NONE ; 
 int /*<<< orphan*/  FZ_TRANSITION_PUSH ; 
 int /*<<< orphan*/  FZ_TRANSITION_SPLIT ; 
 int /*<<< orphan*/  FZ_TRANSITION_UNCOVER ; 
 int /*<<< orphan*/  FZ_TRANSITION_WIPE ; 
 int /*<<< orphan*/  Fade ; 
 int /*<<< orphan*/  Fly ; 
 int /*<<< orphan*/  Glitter ; 
 int /*<<< orphan*/  H ; 
 int /*<<< orphan*/  I ; 
 int /*<<< orphan*/  M ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Push ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  Split ; 
 int /*<<< orphan*/  Trans ; 
 int /*<<< orphan*/  Uncover ; 
 int /*<<< orphan*/  Wipe ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 float pdf_dict_get_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pdf_to_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

fz_transition *
pdf_page_presentation(fz_context *ctx, pdf_page *page, fz_transition *transition, float *duration)
{
	pdf_obj *obj, *transdict;

	*duration = pdf_dict_get_real(ctx, page->obj, PDF_NAME(Dur));

	transdict = pdf_dict_get(ctx, page->obj, PDF_NAME(Trans));
	if (!transdict)
		return NULL;

	obj = pdf_dict_get(ctx, transdict, PDF_NAME(D));

	transition->duration = (obj ? pdf_to_real(ctx, obj) : 1);

	transition->vertical = !pdf_name_eq(ctx, pdf_dict_get(ctx, transdict, PDF_NAME(Dm)), PDF_NAME(H));
	transition->outwards = !pdf_name_eq(ctx, pdf_dict_get(ctx, transdict, PDF_NAME(M)), PDF_NAME(I));
	/* FIXME: If 'Di' is None, it should be handled differently, but
	 * this only affects Fly, and we don't implement that currently. */
	transition->direction = (pdf_dict_get_int(ctx, transdict, PDF_NAME(Di)));
	/* FIXME: Read SS for Fly when we implement it */
	/* FIXME: Read B for Fly when we implement it */

	obj = pdf_dict_get(ctx, transdict, PDF_NAME(S));
	if (pdf_name_eq(ctx, obj, PDF_NAME(Split)))
		transition->type = FZ_TRANSITION_SPLIT;
	else if (pdf_name_eq(ctx, obj, PDF_NAME(Blinds)))
		transition->type = FZ_TRANSITION_BLINDS;
	else if (pdf_name_eq(ctx, obj, PDF_NAME(Box)))
		transition->type = FZ_TRANSITION_BOX;
	else if (pdf_name_eq(ctx, obj, PDF_NAME(Wipe)))
		transition->type = FZ_TRANSITION_WIPE;
	else if (pdf_name_eq(ctx, obj, PDF_NAME(Dissolve)))
		transition->type = FZ_TRANSITION_DISSOLVE;
	else if (pdf_name_eq(ctx, obj, PDF_NAME(Glitter)))
		transition->type = FZ_TRANSITION_GLITTER;
	else if (pdf_name_eq(ctx, obj, PDF_NAME(Fly)))
		transition->type = FZ_TRANSITION_FLY;
	else if (pdf_name_eq(ctx, obj, PDF_NAME(Push)))
		transition->type = FZ_TRANSITION_PUSH;
	else if (pdf_name_eq(ctx, obj, PDF_NAME(Cover)))
		transition->type = FZ_TRANSITION_COVER;
	else if (pdf_name_eq(ctx, obj, PDF_NAME(Uncover)))
		transition->type = FZ_TRANSITION_UNCOVER;
	else if (pdf_name_eq(ctx, obj, PDF_NAME(Fade)))
		transition->type = FZ_TRANSITION_FADE;
	else
		transition->type = FZ_TRANSITION_NONE;

	return transition;
}