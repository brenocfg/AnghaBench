#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_processor ;
struct TYPE_13__ {TYPE_6__* font_name; int /*<<< orphan*/  doc; int /*<<< orphan*/  structarray; scalar_t__ current_tags; scalar_t__ pending_tags; TYPE_6__* gstate; } ;
typedef  TYPE_5__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_11__ {int /*<<< orphan*/  font; } ;
struct TYPE_12__ {TYPE_3__ text; } ;
struct TYPE_9__ {int /*<<< orphan*/  font; } ;
struct TYPE_10__ {TYPE_1__ text; } ;
struct TYPE_14__ {TYPE_4__ sent; TYPE_2__ pending; struct TYPE_14__* next; } ;
typedef  TYPE_6__ filter_gstate ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  pdf_drop_document (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_drop_font (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop_tag (int /*<<< orphan*/ *,TYPE_5__*,scalar_t__*) ; 

__attribute__((used)) static void
pdf_drop_filter_processor(fz_context *ctx, pdf_processor *proc)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;
	filter_gstate *gs = p->gstate;
	while (gs)
	{
		filter_gstate *next = gs->next;
		pdf_drop_font(ctx, gs->pending.text.font);
		pdf_drop_font(ctx, gs->sent.text.font);
		fz_free(ctx, gs);
		gs = next;
	}
	while (p->pending_tags)
		pop_tag(ctx, p, &p->pending_tags);
	while (p->current_tags)
		pop_tag(ctx, p, &p->current_tags);
	pdf_drop_obj(ctx, p->structarray);
	pdf_drop_document(ctx, p->doc);
	fz_free(ctx, p->font_name);
}