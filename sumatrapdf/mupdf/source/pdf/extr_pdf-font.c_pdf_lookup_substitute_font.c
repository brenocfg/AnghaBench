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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 unsigned char const* fz_lookup_base14_font (int /*<<< orphan*/ *,char*,int*) ; 

const unsigned char *
pdf_lookup_substitute_font(fz_context *ctx, int mono, int serif, int bold, int italic, int *len)
{
	if (mono) {
		if (bold) {
			if (italic) return fz_lookup_base14_font(ctx, "Courier-BoldOblique", len);
			else return fz_lookup_base14_font(ctx, "Courier-Bold", len);
		} else {
			if (italic) return fz_lookup_base14_font(ctx, "Courier-Oblique", len);
			else return fz_lookup_base14_font(ctx, "Courier", len);
		}
	} else if (serif) {
		if (bold) {
			if (italic) return fz_lookup_base14_font(ctx, "Times-BoldItalic", len);
			else return fz_lookup_base14_font(ctx, "Times-Bold", len);
		} else {
			if (italic) return fz_lookup_base14_font(ctx, "Times-Italic", len);
			else return fz_lookup_base14_font(ctx, "Times-Roman", len);
		}
	} else {
		if (bold) {
			if (italic) return fz_lookup_base14_font(ctx, "Helvetica-BoldOblique", len);
			else return fz_lookup_base14_font(ctx, "Helvetica-Bold", len);
		} else {
			if (italic) return fz_lookup_base14_font(ctx, "Helvetica-Oblique", len);
			else return fz_lookup_base14_font(ctx, "Helvetica", len);
		}
	}
}