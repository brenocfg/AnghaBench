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
struct TYPE_3__ {void* event_cb_data; int /*<<< orphan*/ * event_cb; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  pdf_doc_event_cb ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

void pdf_set_doc_event_callback(fz_context *ctx, pdf_document *doc, pdf_doc_event_cb *fn, void *data)
{
	doc->event_cb = fn;
	doc->event_cb_data = data;
}