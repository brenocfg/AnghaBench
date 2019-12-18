#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_3__ {int /*<<< orphan*/  pagecount; int /*<<< orphan*/ * doc; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ globals ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  Encrypt ; 
 int /*<<< orphan*/  Info ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_print_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pdf_resolve_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_version (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
showglobalinfo(fz_context *ctx, globals *glo)
{
	pdf_obj *obj;
	fz_output *out = glo->out;
	pdf_document *doc = glo->doc;
	int version = pdf_version(ctx, doc);

	fz_write_printf(ctx, out, "\nPDF-%d.%d\n", version / 10, version % 10);

	obj = pdf_dict_get(ctx, pdf_trailer(ctx, doc), PDF_NAME(Info));
	if (obj)
	{
		fz_write_printf(ctx, out, "Info object (%d 0 R):\n", pdf_to_num(ctx, obj));
		pdf_print_obj(ctx, out, pdf_resolve_indirect(ctx, obj), 1, 1);
	}

	obj = pdf_dict_get(ctx, pdf_trailer(ctx, doc), PDF_NAME(Encrypt));
	if (obj)
	{
		fz_write_printf(ctx, out, "\nEncryption object (%d 0 R):\n", pdf_to_num(ctx, obj));
		pdf_print_obj(ctx, out, pdf_resolve_indirect(ctx, obj), 1, 1);
	}

	fz_write_printf(ctx, out, "\nPages: %d\n\n", glo->pagecount);
}