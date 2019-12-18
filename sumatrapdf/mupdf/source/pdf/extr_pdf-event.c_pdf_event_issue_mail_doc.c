#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/  mail_doc; TYPE_1__ base; } ;
typedef  TYPE_2__ pdf_mail_doc_event_internal ;
typedef  int /*<<< orphan*/  pdf_mail_doc_event ;
struct TYPE_8__ {int /*<<< orphan*/  event_cb_data; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ pdf_document ;
typedef  int /*<<< orphan*/  pdf_doc_event ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  PDF_DOCUMENT_EVENT_MAIL_DOC ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void pdf_event_issue_mail_doc(fz_context *ctx, pdf_document *doc, pdf_mail_doc_event *event)
{
	if (doc->event_cb)
	{
		pdf_mail_doc_event_internal e;

		e.base.type = PDF_DOCUMENT_EVENT_MAIL_DOC;
		e.mail_doc = *event;

		doc->event_cb(ctx, doc, (pdf_doc_event *)&e, doc->event_cb_data);
	}
}