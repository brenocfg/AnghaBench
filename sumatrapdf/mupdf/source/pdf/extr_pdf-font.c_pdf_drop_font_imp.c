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
struct TYPE_3__ {struct TYPE_3__* vmtx; struct TYPE_3__* hmtx; struct TYPE_3__* cid_to_ucs; struct TYPE_3__* cid_to_gid; int /*<<< orphan*/  to_unicode; int /*<<< orphan*/  to_ttf_cmap; int /*<<< orphan*/  encoding; int /*<<< orphan*/  font; } ;
typedef  TYPE_1__ pdf_font_desc ;
typedef  int /*<<< orphan*/  fz_storable ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_font (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_drop_cmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pdf_drop_font_imp(fz_context *ctx, fz_storable *fontdesc_)
{
	pdf_font_desc *fontdesc = (pdf_font_desc *)fontdesc_;

	fz_drop_font(ctx, fontdesc->font);
	pdf_drop_cmap(ctx, fontdesc->encoding);
	pdf_drop_cmap(ctx, fontdesc->to_ttf_cmap);
	pdf_drop_cmap(ctx, fontdesc->to_unicode);
	fz_free(ctx, fontdesc->cid_to_gid);
	fz_free(ctx, fontdesc->cid_to_ucs);
	fz_free(ctx, fontdesc->hmtx);
	fz_free(ctx, fontdesc->vmtx);
	fz_free(ctx, fontdesc);
}