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
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Resources ; 
 int /*<<< orphan*/  Transparency ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_getp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pdf_resources_use_blending (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pdf_xobject_uses_blending(fz_context *ctx, pdf_obj *dict)
{
	pdf_obj *obj = pdf_dict_get(ctx, dict, PDF_NAME(Resources));
	if (pdf_name_eq(ctx, pdf_dict_getp(ctx, dict, "Group/S"), PDF_NAME(Transparency)))
		return 1;
	return pdf_resources_use_blending(ctx, obj);
}