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
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V ; 
 int /*<<< orphan*/ * find_head_of_field_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put_text_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pdf_field_mark_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_field_value(fz_context *ctx, pdf_document *doc, pdf_obj *obj, const char *text)
{
	pdf_obj *grp;

	if (!text)
		text = "";

	/* All fields of the same name should be updated, so
	 * set the value at the head of the group */
	grp = find_head_of_field_group(ctx, obj);
	if (grp)
		obj = grp;

	pdf_dict_put_text_string(ctx, obj, PDF_NAME(V), text);

	pdf_field_mark_dirty(ctx, obj);
}