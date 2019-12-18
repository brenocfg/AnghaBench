#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char const* url; int new_frame; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct TYPE_9__ {TYPE_2__ launch_url; TYPE_1__ base; } ;
typedef  TYPE_3__ pdf_launch_url_event_internal ;
struct TYPE_10__ {int /*<<< orphan*/  event_cb_data; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ pdf_document ;
typedef  int /*<<< orphan*/  pdf_doc_event ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  PDF_DOCUMENT_EVENT_LAUNCH_URL ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void pdf_event_issue_launch_url(fz_context *ctx, pdf_document *doc, const char *url, int new_frame)
{
	if (doc->event_cb)
	{
		pdf_launch_url_event_internal e;

		e.base.type = PDF_DOCUMENT_EVENT_LAUNCH_URL;
		e.launch_url.url = url;
		e.launch_url.new_frame = new_frame;
		doc->event_cb(ctx, doc, (pdf_doc_event *)&e, doc->event_cb_data);
	}
}