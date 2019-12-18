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
 int /*<<< orphan*/  Parent ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * pdf_resolve_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static pdf_obj *
lpr_inherit(fz_context *ctx, pdf_obj *node, char *text, int depth)
{
	do
	{
		pdf_obj *o = pdf_dict_gets(ctx, node, text);

		if (o)
			return pdf_resolve_indirect(ctx, o);
		node = pdf_dict_get(ctx, node, PDF_NAME(Parent));
		depth--;
	}
	while (depth >= 0 && node);

	return NULL;
}