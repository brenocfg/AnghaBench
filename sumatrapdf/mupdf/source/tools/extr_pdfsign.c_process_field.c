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
 int /*<<< orphan*/  FT ; 
 scalar_t__ PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sig ; 
 scalar_t__ clear ; 
 int /*<<< orphan*/  clear_signature (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ list ; 
 int /*<<< orphan*/  list_signature (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_dict_get_inheritable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sign ; 
 int /*<<< orphan*/  sign_signature (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ verify ; 
 int /*<<< orphan*/  verify_signature (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_field(fz_context *ctx, pdf_document *doc, pdf_obj *field)
{
	if (pdf_dict_get_inheritable(ctx, field, PDF_NAME(FT)) != PDF_NAME(Sig))
		fz_warn(ctx, "%d is not a signature, skipping", pdf_to_num(ctx, field));
	else
	{
		if (list)
			list_signature(ctx, doc, field);
		if (verify)
			verify_signature(ctx, doc, field);
		if (clear)
			clear_signature(ctx, doc, field);
		if (sign)
			sign_signature(ctx, doc, field);
	}
}