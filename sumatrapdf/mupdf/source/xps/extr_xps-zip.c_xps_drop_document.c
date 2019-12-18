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
struct TYPE_5__ {struct TYPE_5__* name; int /*<<< orphan*/  font; struct TYPE_5__* next; } ;
typedef  TYPE_1__ xps_font_cache ;
struct TYPE_6__ {TYPE_1__* start_part; TYPE_1__* font_table; scalar_t__ zip; } ;
typedef  TYPE_2__ xps_document ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_archive (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fz_drop_font (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  xps_drop_page_list (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
xps_drop_document(fz_context *ctx, fz_document *doc_)
{
	xps_document *doc = (xps_document*)doc_;
	xps_font_cache *font, *next;

	if (doc->zip)
		fz_drop_archive(ctx, doc->zip);

	font = doc->font_table;
	while (font)
	{
		next = font->next;
		fz_drop_font(ctx, font->font);
		fz_free(ctx, font->name);
		fz_free(ctx, font);
		font = next;
	}

	xps_drop_page_list(ctx, doc);

	fz_free(ctx, doc->start_part);
}