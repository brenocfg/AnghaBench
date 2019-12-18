#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int width; int height; int lineSkip; int /*<<< orphan*/  memptr; } ;
struct TYPE_9__ {int width; int height; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_8__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_10__ {TYPE_2__ renderArea; TYPE_1__ origin; } ;
typedef  TYPE_3__ MuOfficeRenderArea ;
typedef  int /*<<< orphan*/  MuOfficeRender ;
typedef  int /*<<< orphan*/  MuOfficePage ;
typedef  int /*<<< orphan*/  MuOfficeLib ;
typedef  int /*<<< orphan*/  MuOfficeDoc ;
typedef  TYPE_4__ MuOfficeBitmap ;
typedef  int MuError ;

/* Variables and functions */
 int /*<<< orphan*/  CreateSemaphore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  MuOfficeDoc_destroy (int /*<<< orphan*/ *) ; 
 int MuOfficeDoc_getNumPages (int /*<<< orphan*/ *,int*) ; 
 int MuOfficeDoc_getPage (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ **) ; 
 int MuOfficeLib_loadDocument (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MuOfficePage_destroy (int /*<<< orphan*/ *) ; 
 int MuOfficePage_getSize (int /*<<< orphan*/ *,float*,float*) ; 
 int MuOfficePage_render (int /*<<< orphan*/ *,float,TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MuOfficeRender_destroy (int /*<<< orphan*/ *) ; 
 int MuOfficeRender_waitUntilComplete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loaded ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  save_png (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
test_sync(MuOfficeLib *mu)
{
	MuOfficeDoc *doc;
	MuError err;
	int count;
	MuOfficePage *page;
	float w, h;
	MuOfficeBitmap bitmap;
	MuOfficeRenderArea area;
	MuOfficeRender *render;

	loaded = CreateSemaphore(NULL, 0, 1, NULL);

	err = MuOfficeLib_loadDocument(mu,
					"../MyTests/pdf_reference17.pdf",
					NULL,
					NULL,
					NULL,
					&doc);

	/* Test number of pages */
	err = MuOfficeDoc_getNumPages(doc, &count);
	if (err)
	{
		fprintf(stderr, "Failed to count pages: error=%d\n", err);
		return EXIT_FAILURE;
	}
	fprintf(stderr, "%d Pages in document\n", count);

	/* Get a page */
	err = MuOfficeDoc_getPage(doc, 1, NULL, (void *)4321, &page);
	if (err)
	{
		fprintf(stderr, "Failed to get page: error=%d\n", err);
		return EXIT_FAILURE;
	}

	/* Get size of page */
	err = MuOfficePage_getSize(page, &w, &h);
	if (err)
	{
		fprintf(stderr, "Failed to get page size: error=%d\n", err);
		return EXIT_FAILURE;
	}
	fprintf(stderr, "Page size = %g x %g\n", w, h);

	/* Allocate ourselves a bitmap */
	bitmap.width = (int)(w * 1.5f + 0.5f);
	bitmap.height = (int)(h * 1.5f + 0.5f);
	bitmap.lineSkip = bitmap.width * 4;
	bitmap.memptr = malloc(bitmap.lineSkip * bitmap.height);

	/* Set the area to render the whole bitmap */
	area.origin.x = 0;
	area.origin.y = 0;
	area.renderArea.x = 0;
	area.renderArea.y = 0;
	area.renderArea.width = bitmap.width;
	area.renderArea.height = bitmap.height;

	/* Render into the bitmap */
	err = MuOfficePage_render(page, 1.5f, &bitmap, &area, NULL, NULL, &render);
	if (err)
	{
		fprintf(stderr, "Page render failed: error=%d\n", err);
		return EXIT_FAILURE;
	}

	err = MuOfficeRender_waitUntilComplete(render);
	if (err)
	{
		fprintf(stderr, "Page render failed to complete: error=%d\n", err);
		return EXIT_FAILURE;
	}

	/* Kill the render */
	MuOfficeRender_destroy(render);

	/* Output the bitmap */
	save_png(&bitmap, "out1.png");
	free(bitmap.memptr);

	MuOfficePage_destroy(page);

	MuOfficeDoc_destroy(doc);

	return EXIT_SUCCESS;
}