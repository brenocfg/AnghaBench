#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ wmode; } ;
typedef  TYPE_4__ pdf_font_desc ;
struct TYPE_8__ {void* tm; } ;
struct TYPE_12__ {TYPE_1__ tos; TYPE_6__* gstate; } ;
typedef  TYPE_5__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_9__ {float scale; TYPE_4__* font; } ;
struct TYPE_10__ {TYPE_2__ text; } ;
struct TYPE_13__ {TYPE_3__ pending; } ;
typedef  TYPE_6__ filter_gstate ;

/* Variables and functions */
 void* fz_pre_translate (void*,float,float) ; 

__attribute__((used)) static void
filter_show_space(fz_context *ctx, pdf_filter_processor *p, float tadj)
{
	filter_gstate *gstate = p->gstate;
	pdf_font_desc *fontdesc = gstate->pending.text.font;

	if (fontdesc->wmode == 0)
		p->tos.tm = fz_pre_translate(p->tos.tm, tadj * gstate->pending.text.scale, 0);
	else
		p->tos.tm = fz_pre_translate(p->tos.tm, 0, tadj);
}