#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int y; int w; } ;
struct TYPE_5__ {TYPE_1__ dvmtx; } ;
typedef  TYPE_2__ pdf_font_desc ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

void
pdf_set_default_vmtx(fz_context *ctx, pdf_font_desc *font, int y, int w)
{
	font->dvmtx.y = y;
	font->dvmtx.w = w;
}