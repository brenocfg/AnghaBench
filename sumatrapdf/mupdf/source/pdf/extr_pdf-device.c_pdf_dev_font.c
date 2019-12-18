#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ ** cid_fonts; } ;
typedef  TYPE_1__ pdf_device ;
struct TYPE_9__ {size_t font; float font_size; int /*<<< orphan*/  buf; } ;
typedef  TYPE_2__ gstate ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_10__ {scalar_t__ ft_substitute; } ;

/* Variables and functions */
 TYPE_2__* CURRENT_GSTATE (TYPE_1__*) ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t,float) ; 
 TYPE_5__* fz_font_flags (int /*<<< orphan*/ *) ; 
 scalar_t__ fz_font_t3_procs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float fz_matrix_expansion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 size_t pdf_dev_add_font_res (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_font_writing_supported (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pdf_dev_font(fz_context *ctx, pdf_device *pdev, fz_font *font, fz_matrix trm)
{
	gstate *gs = CURRENT_GSTATE(pdev);
	float font_size = fz_matrix_expansion(trm);

	/* If the font is unchanged, nothing to do */
	if (gs->font >= 0 && pdev->cid_fonts[gs->font] == font && gs->font_size == font_size)
		return;

	if (fz_font_t3_procs(ctx, font))
		fz_throw(ctx, FZ_ERROR_GENERIC, "pdf device does not support type 3 fonts");
	if (fz_font_flags(font)->ft_substitute)
		fz_throw(ctx, FZ_ERROR_GENERIC, "pdf device does not support substitute fonts");
	if (!pdf_font_writing_supported(font))
		fz_throw(ctx, FZ_ERROR_GENERIC, "pdf device does not support font types found in this file");

	gs->font = pdf_dev_add_font_res(ctx, pdev, font);
	gs->font_size = font_size;

	fz_append_printf(ctx, gs->buf, "/F%d %g Tf\n", gs->font, gs->font_size);
}