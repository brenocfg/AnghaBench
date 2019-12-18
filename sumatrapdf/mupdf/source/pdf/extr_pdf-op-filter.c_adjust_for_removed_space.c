#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* gstate; } ;
typedef  TYPE_3__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_7__ {float word_space; float scale; } ;
struct TYPE_8__ {TYPE_1__ text; } ;
struct TYPE_10__ {TYPE_2__ pending; } ;
typedef  TYPE_4__ filter_gstate ;

/* Variables and functions */
 int /*<<< orphan*/  adjust_text (int /*<<< orphan*/ *,TYPE_3__*,float,float) ; 

__attribute__((used)) static void
adjust_for_removed_space(fz_context *ctx, pdf_filter_processor *p)
{
	filter_gstate *gstate = p->gstate;
	float adj = gstate->pending.text.word_space;
	adjust_text(ctx, p, adj * gstate->pending.text.scale, adj);
}