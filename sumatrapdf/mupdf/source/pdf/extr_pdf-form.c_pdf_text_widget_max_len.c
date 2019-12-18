#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_widget ;
struct TYPE_2__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  MaxLen ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_get_inheritable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pdf_to_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int pdf_text_widget_max_len(fz_context *ctx, pdf_widget *tw)
{
	pdf_annot *annot = (pdf_annot *)tw;
	return pdf_to_int(ctx, pdf_dict_get_inheritable(ctx, annot->obj, PDF_NAME(MaxLen)));
}