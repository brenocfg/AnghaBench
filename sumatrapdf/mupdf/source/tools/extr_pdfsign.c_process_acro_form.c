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
 int /*<<< orphan*/  AcroForm ; 
 int /*<<< orphan*/  Fields ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Root ; 
 int /*<<< orphan*/  pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_field_hierarchy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_acro_form(fz_context *ctx, pdf_document *doc)
{
	pdf_obj *trailer = pdf_trailer(ctx, doc);
	pdf_obj *root = pdf_dict_get(ctx, trailer, PDF_NAME(Root));
	pdf_obj *acroform = pdf_dict_get(ctx, root, PDF_NAME(AcroForm));
	pdf_obj *fields = pdf_dict_get(ctx, acroform, PDF_NAME(Fields));
	int i, n = pdf_array_len(ctx, fields);
	for (i = 0; i < n; ++i)
		process_field_hierarchy(ctx, doc, pdf_array_get(ctx, fields, i));
}