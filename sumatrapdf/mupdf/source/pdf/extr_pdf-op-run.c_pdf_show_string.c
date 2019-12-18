#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int gtop; TYPE_3__* gstate; } ;
typedef  TYPE_2__ pdf_run_processor ;
struct TYPE_6__ {int /*<<< orphan*/ * font; } ;
struct TYPE_8__ {TYPE_1__ text; } ;
typedef  TYPE_3__ pdf_gstate ;
typedef  int /*<<< orphan*/  pdf_font_desc ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  show_string (int /*<<< orphan*/ *,TYPE_2__*,unsigned char*,int) ; 

__attribute__((used)) static void
pdf_show_string(fz_context *ctx, pdf_run_processor *pr, unsigned char *buf, int len)
{
	pdf_gstate *gstate = pr->gstate + pr->gtop;
	pdf_font_desc *fontdesc = gstate->text.font;

	if (!fontdesc)
	{
		fz_warn(ctx, "cannot draw text since font and size not set");
		return;
	}

	show_string(ctx, pr, buf, len);
}