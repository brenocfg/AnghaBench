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
struct TYPE_4__ {int /*<<< orphan*/  number; TYPE_2__* doc; } ;
typedef  TYPE_1__ html_page ;
struct TYPE_5__ {int /*<<< orphan*/  html; } ;
typedef  TYPE_2__ html_document ;
typedef  int /*<<< orphan*/  fz_page ;
typedef  int /*<<< orphan*/  fz_link ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_load_html_links (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 

__attribute__((used)) static fz_link *
htdoc_load_links(fz_context *ctx, fz_page *page_)
{
	html_page *page = (html_page*)page_;
	html_document *doc = page->doc;
	return fz_load_html_links(ctx, doc->html, page->number, "", doc);
}