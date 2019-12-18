#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* tm; } ;
struct TYPE_9__ {int gtop; TYPE_1__ tos; TYPE_4__* gstate; } ;
typedef  TYPE_3__ pdf_run_processor ;
struct TYPE_8__ {float scale; TYPE_5__* font; } ;
struct TYPE_10__ {TYPE_2__ text; } ;
typedef  TYPE_4__ pdf_gstate ;
struct TYPE_11__ {scalar_t__ wmode; } ;
typedef  TYPE_5__ pdf_font_desc ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 void* fz_pre_translate (void*,float,float) ; 

__attribute__((used)) static void
pdf_show_space(fz_context *ctx, pdf_run_processor *pr, float tadj)
{
	pdf_gstate *gstate = pr->gstate + pr->gtop;
	pdf_font_desc *fontdesc = gstate->text.font;

	if (fontdesc->wmode == 0)
		pr->tos.tm = fz_pre_translate(pr->tos.tm, tadj * gstate->text.scale, 0);
	else
		pr->tos.tm = fz_pre_translate(pr->tos.tm, 0, tadj);
}