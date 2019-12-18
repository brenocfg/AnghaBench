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
typedef  int /*<<< orphan*/  pdf_processor ;
struct TYPE_9__ {TYPE_3__* gstate; } ;
typedef  TYPE_4__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {float leading; } ;
struct TYPE_7__ {TYPE_1__ text; } ;
struct TYPE_8__ {TYPE_2__ pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  filter_flush (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pdf_filter_TL(fz_context *ctx, pdf_processor *proc, float leading)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;
	filter_flush(ctx, p, 0);
	p->gstate->pending.text.leading = leading;
}