#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_font_desc ;
struct TYPE_15__ {int /*<<< orphan*/  char_ty; int /*<<< orphan*/  char_tx; } ;
struct TYPE_16__ {TYPE_3__ tos; TYPE_6__* chain; TYPE_5__* gstate; } ;
typedef  TYPE_4__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_13__ {int /*<<< orphan*/ * font; } ;
struct TYPE_14__ {TYPE_1__ text; } ;
struct TYPE_17__ {TYPE_2__ pending; } ;
typedef  TYPE_5__ filter_gstate ;
struct TYPE_18__ {int /*<<< orphan*/  (* op_Tj ) (int /*<<< orphan*/ *,TYPE_6__*,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH_ALL ; 
 int /*<<< orphan*/  adjust_for_removed_space (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  adjust_text (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_flush (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_string_to_segment (int /*<<< orphan*/ *,TYPE_4__*,unsigned char*,int,int*,int*,int*) ; 
 int /*<<< orphan*/  flush_adjustment (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_6__*,char*,int) ; 

__attribute__((used)) static void
filter_show_string(fz_context *ctx, pdf_filter_processor *p, unsigned char *buf, int len)
{
	filter_gstate *gstate = p->gstate;
	pdf_font_desc *fontdesc = gstate->pending.text.font;
	int i, inc, removed_space;

	if (!fontdesc)
		return;

	i = 0;
	while (i < len)
	{
		int start = i;
		filter_string_to_segment(ctx, p, buf, len, &i, &inc, &removed_space);
		if (start != i)
		{
			/* We have *some* chars to send at least */
			filter_flush(ctx, p, FLUSH_ALL);
			flush_adjustment(ctx, p);
			if (p->chain->op_Tj)
				p->chain->op_Tj(ctx, p->chain, (char *)buf+start, i-start);
		}
		if (i != len)
		{
			adjust_text(ctx, p, p->tos.char_tx, p->tos.char_ty);
			i += inc;
		}
		if (removed_space)
			adjust_for_removed_space(ctx, p);
	}
}