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
typedef  int /*<<< orphan*/  pdf_vmtx ;
struct TYPE_3__ {int size; int vmtx_cap; int /*<<< orphan*/  vmtx_len; int /*<<< orphan*/  vmtx; } ;
typedef  TYPE_1__ pdf_font_desc ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  cmpv ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
pdf_end_vmtx(fz_context *ctx, pdf_font_desc *font)
{
	if (!font->vmtx)
		return;
	qsort(font->vmtx, font->vmtx_len, sizeof(pdf_vmtx), cmpv);
	font->size += font->vmtx_cap * sizeof(pdf_vmtx);
}