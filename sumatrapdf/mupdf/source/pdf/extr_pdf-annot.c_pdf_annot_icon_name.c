#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_4__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FileAttachment ; 
 int /*<<< orphan*/  Name ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sound ; 
 int /*<<< orphan*/  Stamp ; 
 int /*<<< orphan*/  Subtype ; 
 int /*<<< orphan*/  Text ; 
 int /*<<< orphan*/  check_allowed_subtypes (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icon_name_subtypes ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char const* pdf_to_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

const char *
pdf_annot_icon_name(fz_context *ctx, pdf_annot *annot)
{
	pdf_obj *name;
	check_allowed_subtypes(ctx, annot, PDF_NAME(Name), icon_name_subtypes);
	name = pdf_dict_get(ctx, annot->obj, PDF_NAME(Name));
	if (!name)
	{
		pdf_obj *subtype = pdf_dict_get(ctx, annot->obj, PDF_NAME(Subtype));
		if (pdf_name_eq(ctx, subtype, PDF_NAME(Text)))
			return "Note";
		if (pdf_name_eq(ctx, subtype, PDF_NAME(Stamp)))
			return "Draft";
		if (pdf_name_eq(ctx, subtype, PDF_NAME(FileAttachment)))
			return "PushPin";
		if (pdf_name_eq(ctx, subtype, PDF_NAME(Sound)))
			return "Speaker";
	}
	return pdf_to_name(ctx, name);
}