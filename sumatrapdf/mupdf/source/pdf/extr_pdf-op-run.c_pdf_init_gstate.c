#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int alpha; int gstate_num; void* color_params; int /*<<< orphan*/ * shade; int /*<<< orphan*/ * pattern; scalar_t__* v; void* colorspace; void* kind; } ;
struct TYPE_7__ {int alpha; int gstate_num; void* color_params; int /*<<< orphan*/ * shade; int /*<<< orphan*/ * pattern; scalar_t__* v; void* colorspace; void* kind; } ;
struct TYPE_6__ {int scale; int size; scalar_t__ rise; scalar_t__ render; int /*<<< orphan*/ * font; scalar_t__ leading; scalar_t__ word_space; scalar_t__ char_space; } ;
struct TYPE_9__ {TYPE_3__ stroke; TYPE_2__ fill; scalar_t__ luminosity; int /*<<< orphan*/  softmask_ctm; int /*<<< orphan*/ * softmask_resources; int /*<<< orphan*/ * softmask; scalar_t__ blendmode; TYPE_1__ text; int /*<<< orphan*/  stroke_state; scalar_t__ clip_depth; int /*<<< orphan*/  ctm; } ;
typedef  TYPE_4__ pdf_gstate ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 void* PDF_MAT_COLOR ; 
 void* fz_default_color_params ; 
 int /*<<< orphan*/  fz_device_gray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_identity ; 
 void* fz_keep_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_new_stroke_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pdf_init_gstate(fz_context *ctx, pdf_gstate *gs, fz_matrix ctm)
{
	gs->ctm = ctm;
	gs->clip_depth = 0;

	gs->stroke_state = fz_new_stroke_state(ctx);

	gs->stroke.kind = PDF_MAT_COLOR;
	gs->stroke.colorspace = fz_keep_colorspace(ctx, fz_device_gray(ctx));
	gs->stroke.v[0] = 0;
	gs->stroke.pattern = NULL;
	gs->stroke.shade = NULL;
	gs->stroke.alpha = 1;
	gs->stroke.gstate_num = -1;

	gs->fill.kind = PDF_MAT_COLOR;
	gs->fill.colorspace = fz_keep_colorspace(ctx, fz_device_gray(ctx));
	gs->fill.v[0] = 0;
	gs->fill.pattern = NULL;
	gs->fill.shade = NULL;
	gs->fill.alpha = 1;
	gs->fill.gstate_num = -1;

	gs->text.char_space = 0;
	gs->text.word_space = 0;
	gs->text.scale = 1;
	gs->text.leading = 0;
	gs->text.font = NULL;
	gs->text.size = -1;
	gs->text.render = 0;
	gs->text.rise = 0;

	gs->blendmode = 0;
	gs->softmask = NULL;
	gs->softmask_resources = NULL;
	gs->softmask_ctm = fz_identity;
	gs->luminosity = 0;

	gs->fill.color_params = fz_default_color_params;
	gs->stroke.color_params = fz_default_color_params;
}