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
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_2__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  AA ; 
 int /*<<< orphan*/  F ; 
 int /*<<< orphan*/  JS ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int PDF_WIDGET_TX_FORMAT_DATE ; 
 int PDF_WIDGET_TX_FORMAT_NONE ; 
 int PDF_WIDGET_TX_FORMAT_NUMBER ; 
 int PDF_WIDGET_TX_FORMAT_SPECIAL ; 
 int PDF_WIDGET_TX_FORMAT_TIME ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * pdf_dict_getl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* pdf_load_stream_or_string_as_utf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strstr (char*,char*) ; 

int pdf_text_widget_format(fz_context *ctx, pdf_widget *tw)
{
	pdf_annot *annot = (pdf_annot *)tw;
	int type = PDF_WIDGET_TX_FORMAT_NONE;
	pdf_obj *js = pdf_dict_getl(ctx, annot->obj, PDF_NAME(AA), PDF_NAME(F), PDF_NAME(JS), NULL);
	if (js)
	{
		char *code = pdf_load_stream_or_string_as_utf8(ctx, js);
		if (strstr(code, "AFNumber_Format"))
			type = PDF_WIDGET_TX_FORMAT_NUMBER;
		else if (strstr(code, "AFSpecial_Format"))
			type = PDF_WIDGET_TX_FORMAT_SPECIAL;
		else if (strstr(code, "AFDate_FormatEx"))
			type = PDF_WIDGET_TX_FORMAT_DATE;
		else if (strstr(code, "AFTime_FormatEx"))
			type = PDF_WIDGET_TX_FORMAT_TIME;
		fz_free(ctx, code);
	}

	return type;
}