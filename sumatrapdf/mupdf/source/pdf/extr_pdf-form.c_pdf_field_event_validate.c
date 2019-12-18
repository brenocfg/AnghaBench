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
typedef  int /*<<< orphan*/  pdf_js ;
struct TYPE_4__ {int /*<<< orphan*/ * js; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * pdf_dict_getp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pdf_execute_js_action (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_js_event_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int) ; 
 int pdf_js_event_result (int /*<<< orphan*/ *) ; 

int pdf_field_event_validate(fz_context *ctx, pdf_document *doc, pdf_obj *field, const char *value)
{
	pdf_js *js = doc->js;
	if (js)
	{
		pdf_obj *action = pdf_dict_getp(ctx, field, "AA/V/JS");
		if (action)
		{
			pdf_js_event_init(js, field, value, 1);
			pdf_execute_js_action(ctx, doc, field, "AA/V/JS", action);
			return pdf_js_event_result(js);
		}
	}
	return 1;
}