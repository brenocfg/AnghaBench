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
struct TYPE_2__ {int /*<<< orphan*/  outline; int /*<<< orphan*/  set; int /*<<< orphan*/  html; int /*<<< orphan*/  zip; } ;
typedef  TYPE_1__ html_document ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_archive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_html (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_html_font_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_outline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
htdoc_drop_document(fz_context *ctx, fz_document *doc_)
{
	html_document *doc = (html_document*)doc_;
	fz_drop_archive(ctx, doc->zip);
	fz_drop_html(ctx, doc->html);
	fz_drop_html_font_set(ctx, doc->set);
	fz_drop_outline(ctx, doc->outline);
}