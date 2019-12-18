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
struct TYPE_3__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  stream; int /*<<< orphan*/ * doc; int /*<<< orphan*/ * page; int /*<<< orphan*/ * outline; int /*<<< orphan*/ * old_image; int /*<<< orphan*/ * new_image; int /*<<< orphan*/ * image; int /*<<< orphan*/ * docpath; int /*<<< orphan*/ * doctitle; int /*<<< orphan*/ * page_links; int /*<<< orphan*/ * page_text; int /*<<< orphan*/ * seps; int /*<<< orphan*/ * annotations_list; int /*<<< orphan*/ * page_list; } ;
typedef  TYPE_1__ pdfapp_t ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_display_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_document (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_link (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_outline (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_separations (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_stext_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_flush_warnings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void pdfapp_close(pdfapp_t *app)
{
	fz_drop_display_list(app->ctx, app->page_list);
	app->page_list = NULL;

	fz_drop_display_list(app->ctx, app->annotations_list);
	app->annotations_list = NULL;

	fz_drop_separations(app->ctx, app->seps);
	app->seps = NULL;

	fz_drop_stext_page(app->ctx, app->page_text);
	app->page_text = NULL;

	fz_drop_link(app->ctx, app->page_links);
	app->page_links = NULL;

	fz_free(app->ctx, app->doctitle);
	app->doctitle = NULL;

	fz_free(app->ctx, app->docpath);
	app->docpath = NULL;

	fz_drop_pixmap(app->ctx, app->image);
	app->image = NULL;

	fz_drop_pixmap(app->ctx, app->new_image);
	app->new_image = NULL;

	fz_drop_pixmap(app->ctx, app->old_image);
	app->old_image = NULL;

	fz_drop_outline(app->ctx, app->outline);
	app->outline = NULL;

	fz_drop_page(app->ctx, app->page);
	app->page = NULL;

	fz_drop_document(app->ctx, app->doc);
	app->doc = NULL;

#ifdef HAVE_CURL
	fz_drop_stream(app->ctx, app->stream);
#endif

	fz_flush_warnings(app->ctx);
}