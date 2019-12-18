#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int hmtx_len; int hmtx_cap; TYPE_3__* hmtx; } ;
typedef  TYPE_1__ pdf_font_desc ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {int lo; int hi; int w; } ;

/* Variables and functions */
 TYPE_3__* fz_realloc_array (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_hmtx ; 

void
pdf_add_hmtx(fz_context *ctx, pdf_font_desc *font, int lo, int hi, int w)
{
	if (font->hmtx_len + 1 >= font->hmtx_cap)
	{
		int new_cap = font->hmtx_cap + 16;
		font->hmtx = fz_realloc_array(ctx, font->hmtx, new_cap, pdf_hmtx);
		font->hmtx_cap = new_cap;
	}

	font->hmtx[font->hmtx_len].lo = lo;
	font->hmtx[font->hmtx_len].hi = hi;
	font->hmtx[font->hmtx_len].w = w;
	font->hmtx_len++;
}