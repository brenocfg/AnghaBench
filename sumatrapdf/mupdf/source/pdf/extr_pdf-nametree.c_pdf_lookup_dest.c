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
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  Dests ; 
 int /*<<< orphan*/  Names ; 
 int /*<<< orphan*/ * PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Root ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_is_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_lookup_name_imp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_to_str_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

pdf_obj *
pdf_lookup_dest(fz_context *ctx, pdf_document *doc, pdf_obj *needle)
{
	pdf_obj *root = pdf_dict_get(ctx, pdf_trailer(ctx, doc), PDF_NAME(Root));
	pdf_obj *dests = pdf_dict_get(ctx, root, PDF_NAME(Dests));
	pdf_obj *names = pdf_dict_get(ctx, root, PDF_NAME(Names));
	pdf_obj *dest = NULL;

	/* PDF 1.1 has destinations in a dictionary */
	if (dests)
	{
		if (pdf_is_name(ctx, needle))
			return pdf_dict_get(ctx, dests, needle);
		else
			return pdf_dict_gets(ctx, dests, pdf_to_str_buf(ctx, needle));
	}

	/* PDF 1.2 has destinations in a name tree */
	if (names && !dest)
	{
		pdf_obj *tree = pdf_dict_get(ctx, names, PDF_NAME(Dests));
		return pdf_lookup_name_imp(ctx, tree, needle);
	}

	return NULL;
}