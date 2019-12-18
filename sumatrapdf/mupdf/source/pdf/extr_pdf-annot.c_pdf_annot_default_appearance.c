#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_5__ {TYPE_1__* page; int /*<<< orphan*/  obj; } ;
typedef  TYPE_2__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int /*<<< orphan*/  doc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AcroForm ; 
 int /*<<< orphan*/  DA ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Root ; 
 int /*<<< orphan*/ * pdf_dict_get_inheritable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_getl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_parse_default_appearance (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,float*,float*) ; 
 int /*<<< orphan*/  pdf_to_str_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pdf_annot_default_appearance(fz_context *ctx, pdf_annot *annot, const char **font, float *size, float color[3])
{
	pdf_obj *da = pdf_dict_get_inheritable(ctx, annot->obj, PDF_NAME(DA));
	if (!da)
	{
		pdf_obj *trailer = pdf_trailer(ctx, annot->page->doc);
		da = pdf_dict_getl(ctx, trailer, PDF_NAME(Root), PDF_NAME(AcroForm), PDF_NAME(DA), NULL);
	}
	pdf_parse_default_appearance(ctx, pdf_to_str_buf(ctx, da), font, size, color);
}