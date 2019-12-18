#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_page ;
typedef  int /*<<< orphan*/  fz_link ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {int /*<<< orphan*/  number; int /*<<< orphan*/  html; TYPE_2__* ch; int /*<<< orphan*/ * doc; } ;
typedef  TYPE_1__ epub_page ;
typedef  int /*<<< orphan*/  epub_document ;
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ epub_chapter ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_load_html_links (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static fz_link *
epub_load_links(fz_context *ctx, fz_page *page_)
{
	epub_page *page = (epub_page*)page_;
	epub_document *doc = page->doc;
	epub_chapter *ch = page->ch;

	return fz_load_html_links(ctx, page->html, page->number, ch->path, doc);
}