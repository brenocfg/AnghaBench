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
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int pdf_create_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_get_bound_document (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_keep_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_new_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_update_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

pdf_obj *
pdf_add_object(fz_context *ctx, pdf_document *doc, pdf_obj *obj)
{
	pdf_document *orig_doc;
	int num;

	orig_doc = pdf_get_bound_document(ctx, obj);
	if (orig_doc && orig_doc != doc)
		fz_throw(ctx, FZ_ERROR_GENERIC, "tried to add an object belonging to a different document");
	if (pdf_is_indirect(ctx, obj))
		return pdf_keep_obj(ctx, obj);
	num = pdf_create_object(ctx, doc);
	pdf_update_object(ctx, doc, num, obj);
	return pdf_new_indirect(ctx, doc, num, 0);
}