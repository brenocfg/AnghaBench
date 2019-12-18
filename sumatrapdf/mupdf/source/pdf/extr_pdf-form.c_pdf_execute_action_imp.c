#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_5__ {scalar_t__ js; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  Fields ; 
 int /*<<< orphan*/  Flags ; 
 int /*<<< orphan*/  JS ; 
 int /*<<< orphan*/  JavaScript ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetForm ; 
 int /*<<< orphan*/ * S ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pdf_dict_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_execute_js_action (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_reset_form (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void pdf_execute_action_imp(fz_context *ctx, pdf_document *doc, pdf_obj *target, const char *path, pdf_obj *action)
{
	pdf_obj *S = pdf_dict_get(ctx, action, PDF_NAME(S));
	if (pdf_name_eq(ctx, S, PDF_NAME(JavaScript)))
	{
		if (doc->js)
			pdf_execute_js_action(ctx, doc, target, path, pdf_dict_get(ctx, action, PDF_NAME(JS)));
	}
	if (pdf_name_eq(ctx, S, PDF_NAME(ResetForm)))
	{
		pdf_obj *fields = pdf_dict_get(ctx, action, PDF_NAME(Fields));
		int flags = pdf_dict_get_int(ctx, action, PDF_NAME(Flags));
		pdf_reset_form(ctx, doc, fields, flags & 1);
	}
}