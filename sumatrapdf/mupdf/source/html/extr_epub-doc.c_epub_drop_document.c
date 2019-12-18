#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int /*<<< orphan*/  most_recent_html; TYPE_2__* dc_creator; TYPE_2__* dc_title; int /*<<< orphan*/  outline; int /*<<< orphan*/  set; int /*<<< orphan*/  zip; int /*<<< orphan*/  accel; TYPE_2__* spine; } ;
typedef  TYPE_1__ epub_document ;
struct TYPE_6__ {struct TYPE_6__* path; struct TYPE_6__* next; } ;
typedef  TYPE_2__ epub_chapter ;

/* Variables and functions */
 int /*<<< orphan*/  epub_drop_accelerator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_archive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_html (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_html_font_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_outline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  fz_purge_stored_html (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
epub_drop_document(fz_context *ctx, fz_document *doc_)
{
	epub_document *doc = (epub_document*)doc_;
	epub_chapter *ch, *next;
	ch = doc->spine;
	while (ch)
	{
		next = ch->next;
		fz_free(ctx, ch->path);
		fz_free(ctx, ch);
		ch = next;
	}
	epub_drop_accelerator(ctx, doc->accel);
	fz_drop_archive(ctx, doc->zip);
	fz_drop_html_font_set(ctx, doc->set);
	fz_drop_outline(ctx, doc->outline);
	fz_free(ctx, doc->dc_title);
	fz_free(ctx, doc->dc_creator);
	fz_drop_html(ctx, doc->most_recent_html);
	fz_purge_stored_html(ctx, doc);
}