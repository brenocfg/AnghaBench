#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,float) ; 
 float pdf_annot_border (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static float pdf_write_border_appearance(fz_context *ctx, pdf_annot *annot, fz_buffer *buf)
{
	float w = pdf_annot_border(ctx, annot);
	fz_append_printf(ctx, buf, "%g w\n", w);
	return w;
}