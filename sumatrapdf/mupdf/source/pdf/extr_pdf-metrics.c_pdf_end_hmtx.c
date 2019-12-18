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
typedef  int /*<<< orphan*/  pdf_hmtx ;
struct TYPE_3__ {int size; int hmtx_cap; int /*<<< orphan*/  hmtx_len; int /*<<< orphan*/  hmtx; } ;
typedef  TYPE_1__ pdf_font_desc ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  cmph ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
pdf_end_hmtx(fz_context *ctx, pdf_font_desc *font)
{
	if (!font->hmtx)
		return;
	qsort(font->hmtx, font->hmtx_len, sizeof(pdf_hmtx), cmph);
	font->size += font->hmtx_cap * sizeof(pdf_hmtx);
}