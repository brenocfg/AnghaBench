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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_font_desc ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  CIDFontType0 ; 
 int /*<<< orphan*/  CIDFontType2 ; 
 int /*<<< orphan*/  DescendantFonts ; 
 int /*<<< orphan*/  Encoding ; 
 int /*<<< orphan*/  FZ_ERROR_SYNTAX ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Subtype ; 
 int /*<<< orphan*/  ToUnicode ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * load_cid_font (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_is_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pdf_font_desc *
pdf_load_type0_font(fz_context *ctx, pdf_document *doc, pdf_obj *dict)
{
	pdf_obj *dfonts;
	pdf_obj *dfont;
	pdf_obj *subtype;
	pdf_obj *encoding;
	pdf_obj *to_unicode;

	dfonts = pdf_dict_get(ctx, dict, PDF_NAME(DescendantFonts));
	if (!dfonts)
		fz_throw(ctx, FZ_ERROR_SYNTAX, "cid font is missing descendant fonts");

	dfont = pdf_array_get(ctx, dfonts, 0);

	subtype = pdf_dict_get(ctx, dfont, PDF_NAME(Subtype));
	encoding = pdf_dict_get(ctx, dict, PDF_NAME(Encoding));
	to_unicode = pdf_dict_get(ctx, dict, PDF_NAME(ToUnicode));

	if (pdf_is_name(ctx, subtype) && pdf_name_eq(ctx, subtype, PDF_NAME(CIDFontType0)))
		return load_cid_font(ctx, doc, dfont, encoding, to_unicode);
	if (pdf_is_name(ctx, subtype) && pdf_name_eq(ctx, subtype, PDF_NAME(CIDFontType2)))
		return load_cid_font(ctx, doc, dfont, encoding, to_unicode);
	fz_throw(ctx, FZ_ERROR_SYNTAX, "unknown cid font type");
}