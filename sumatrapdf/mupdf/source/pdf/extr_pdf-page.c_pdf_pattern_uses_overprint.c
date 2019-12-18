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
 int /*<<< orphan*/  ExtGState ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Resources ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pdf_extgstate_uses_overprint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_resources_use_overprint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pdf_pattern_uses_overprint(fz_context *ctx, pdf_obj *dict)
{
	pdf_obj *obj;
	obj = pdf_dict_get(ctx, dict, PDF_NAME(Resources));
	if (pdf_resources_use_overprint(ctx, obj))
		return 1;
	obj = pdf_dict_get(ctx, dict, PDF_NAME(ExtGState));
	return pdf_extgstate_uses_overprint(ctx, obj);
}