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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  CIDFontType0C ; 
 int /*<<< orphan*/  Font ; 
 int /*<<< orphan*/  FontDescriptor ; 
 int /*<<< orphan*/  Length1 ; 
 int /*<<< orphan*/  Length2 ; 
 int /*<<< orphan*/  Length3 ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Subtype ; 
 int /*<<< orphan*/  Type ; 
 int /*<<< orphan*/  Type1C ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_font_stream(fz_context *ctx, pdf_obj *obj)
{
	pdf_obj *o;
	if (o = pdf_dict_get(ctx, obj, PDF_NAME(Type)), pdf_name_eq(ctx, o, PDF_NAME(Font)))
		return 1;
	if (o = pdf_dict_get(ctx, obj, PDF_NAME(Type)), pdf_name_eq(ctx, o, PDF_NAME(FontDescriptor)))
		return 1;
	if (pdf_dict_get(ctx, obj, PDF_NAME(Length1)) != NULL)
		return 1;
	if (pdf_dict_get(ctx, obj, PDF_NAME(Length2)) != NULL)
		return 1;
	if (pdf_dict_get(ctx, obj, PDF_NAME(Length3)) != NULL)
		return 1;
	if (o = pdf_dict_get(ctx, obj, PDF_NAME(Subtype)), pdf_name_eq(ctx, o, PDF_NAME(Type1C)))
		return 1;
	if (o = pdf_dict_get(ctx, obj, PDF_NAME(Subtype)), pdf_name_eq(ctx, o, PDF_NAME(CIDFontType0C)))
		return 1;
	return 0;
}