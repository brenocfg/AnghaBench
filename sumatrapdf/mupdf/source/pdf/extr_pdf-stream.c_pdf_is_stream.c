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
 int /*<<< orphan*/ * pdf_get_indirect_document (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_obj_num_is_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
pdf_is_stream(fz_context *ctx, pdf_obj *ref)
{
	pdf_document *doc = pdf_get_indirect_document(ctx, ref);
	if (doc)
		return pdf_obj_num_is_stream(ctx, doc, pdf_to_num(ctx, ref));
	return 0;
}