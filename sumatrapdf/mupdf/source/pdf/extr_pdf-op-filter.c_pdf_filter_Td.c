#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_processor ;
struct TYPE_2__ {int Tm_pending; int /*<<< orphan*/  tos; scalar_t__ Tm_adjust; } ;
typedef  TYPE_1__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_tos_translate (int /*<<< orphan*/ *,float,float) ; 

__attribute__((used)) static void
pdf_filter_Td(fz_context *ctx, pdf_processor *proc, float tx, float ty)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;
	p->Tm_adjust = 0;
	pdf_tos_translate(&p->tos, tx, ty);
	p->Tm_pending = 1;
}