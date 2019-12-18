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
struct TYPE_4__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  DA ; 
 int /*<<< orphan*/  DS ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RC ; 
 int /*<<< orphan*/  pdf_dict_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dirty_annot (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_print_default_appearance (int /*<<< orphan*/ *,char*,int,char const*,float,float const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void
pdf_set_annot_default_appearance(fz_context *ctx, pdf_annot *annot, const char *font, float size, const float color[3])
{
	char buf[100];

	pdf_print_default_appearance(ctx, buf, sizeof buf, font, size, color);

	pdf_dict_put_string(ctx, annot->obj, PDF_NAME(DA), buf, strlen(buf));

	pdf_dict_del(ctx, annot->obj, PDF_NAME(DS)); /* not supported */
	pdf_dict_del(ctx, annot->obj, PDF_NAME(RC)); /* not supported */

	pdf_dirty_annot(ctx, annot);
}