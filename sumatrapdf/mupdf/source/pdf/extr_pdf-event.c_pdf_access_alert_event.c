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
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ pdf_doc_event ;
struct TYPE_5__ {int /*<<< orphan*/  alert; } ;
typedef  TYPE_2__ pdf_alert_event_internal ;
typedef  int /*<<< orphan*/  pdf_alert_event ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ PDF_DOCUMENT_EVENT_ALERT ; 

pdf_alert_event *pdf_access_alert_event(fz_context *ctx, pdf_doc_event *event)
{
	pdf_alert_event *alert = NULL;

	if (event->type == PDF_DOCUMENT_EVENT_ALERT)
		alert = &((pdf_alert_event_internal *)event)->alert;

	return alert;
}