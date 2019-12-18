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
struct data {int pagenumber; int /*<<< orphan*/ * list; int /*<<< orphan*/ * pix; int /*<<< orphan*/  bbox; int /*<<< orphan*/ * ctx; } ;
typedef  struct data pthread_t ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_pixmap ;
typedef  int /*<<< orphan*/  fz_page ;
struct TYPE_3__ {int /*<<< orphan*/  unlock; int /*<<< orphan*/  lock; int /*<<< orphan*/ * user; } ;
typedef  TYPE_1__ fz_locks_context ;
typedef  int /*<<< orphan*/  fz_irect ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_display_list ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int FZ_LOCK_MAX ; 
 int /*<<< orphan*/  FZ_STORE_UNLIMITED ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct data*) ; 
 int /*<<< orphan*/  fz_bound_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_clear_pixmap_with_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_close_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fz_count_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_device_rgb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_display_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_document (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_identity ; 
 int /*<<< orphan*/ * fz_load_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * fz_new_context (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fz_new_display_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_new_list_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_new_pixmap_with_bbox (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fz_open_document (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fz_register_document_handlers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_round_rect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_run_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_save_pixmap_as_png (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lock_mutex ; 
 struct data* malloc (int) ; 
 scalar_t__ pthread_create (struct data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct data*) ; 
 scalar_t__ pthread_join (struct data,void**) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  renderer ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlock_mutex ; 

int main(int argc, char **argv)
{
	char *filename = argc >= 2 ? argv[1] : "";
	pthread_t *thread = NULL;
	fz_locks_context locks;
	pthread_mutex_t mutex[FZ_LOCK_MAX];
	fz_context *ctx;
	fz_document *doc;
	int threads;
	int i;

	// Initialize FZ_LOCK_MAX number of non-recursive mutexes.

	for (i = 0; i < FZ_LOCK_MAX; i++)
	{
		if (pthread_mutex_init(&mutex[i], NULL) != 0)
			fail("pthread_mutex_init()");
	}

	// Initialize the locking structure with function pointers to
	// the locking functions and to the user data. In this case
	// the user data is a pointer to the array of mutexes so the
	// locking functions can find the relevant lock to change when
	// they are called. This way we avoid global variables.

	locks.user = mutex;
	locks.lock = lock_mutex;
	locks.unlock = unlock_mutex;

	// This is the main threads context function, so supply the
	// locking structure. This context will be used to parse all
	// the pages from the document.

	ctx = fz_new_context(NULL, &locks, FZ_STORE_UNLIMITED);

	// Register default file types.

	fz_register_document_handlers(ctx);

	// Open the PDF, XPS or CBZ document. Note, this binds doc to ctx.
	// You must only ever use doc with ctx - never a clone of it!

	doc = fz_open_document(ctx, filename);

	// Retrieve the number of pages, which translates to the
	// number of threads used for rendering pages.

	threads = fz_count_pages(ctx, doc);
	fprintf(stderr, "spawning %d threads, one per page...\n", threads);

	thread = malloc(threads * sizeof (pthread_t));

	for (i = 0; i < threads; i++)
	{
		fz_page *page;
		fz_rect bbox;
		fz_irect rbox;
		fz_display_list *list;
		fz_device *dev;
		fz_pixmap *pix;
		struct data *data;

		// Load the relevant page for each thread. Note, that this
		// cannot be done on the worker threads, as each use of doc
		// uses ctx, and only one thread can be using ctx at a time.

		page = fz_load_page(ctx, doc, i);

		// Compute the bounding box for each page.

		fz_bound_page(ctx, page, &bbox);

		// Create a display list that will hold the drawing
		// commands for the page. Once we have the display list
		// this can safely be used on any other thread as it is
		// not bound to a given context.

		list = fz_new_display_list(ctx, &bbox);

		// Run the loaded page through a display list device
		// to populate the page's display list.

		dev = fz_new_list_device(ctx, list);
		fz_run_page(ctx, page, dev, &fz_identity, NULL);
		fz_close_device(ctx, dev);
		fz_drop_device(ctx, dev);

		// The page is no longer needed, all drawing commands
		// are now in the display list.

		fz_drop_page(ctx, page);

		// Create a white pixmap using the correct dimensions.

		pix = fz_new_pixmap_with_bbox(ctx, fz_device_rgb(ctx), fz_round_rect(&rbox, &bbox), NULL, 0);
		fz_clear_pixmap_with_value(ctx, pix, 0xff);

		// Populate the data structure to be sent to the
		// rendering thread for this page.

		data = malloc(sizeof (struct data));

		data->pagenumber = i + 1;
		data->ctx = ctx;
		data->list = list;
		data->bbox = bbox;
		data->pix = pix;

		// Create the thread and pass it the data structure.

		if (pthread_create(&thread[i], NULL, renderer, data) != 0)
			fail("pthread_create()");
	}

	// Now each thread is rendering pages, so wait for each thread
	// to complete its rendering.

	fprintf(stderr, "joining %d threads...\n", threads);
	for (i = threads - 1; i >= 0; i--)
	{
		char filename[42];
		struct data *data;

		if (pthread_join(thread[i], (void **) &data) != 0)
			fail("pthread_join");

		sprintf(filename, "out%04d.png", i);
		fprintf(stderr, "\tSaving %s...\n", filename);

		// Write the rendered image to a PNG file

		fz_save_pixmap_as_png(ctx, data->pix, filename);

		// Free the thread's pixmap and display list since
		// they were allocated by the main thread above.

		fz_drop_pixmap(ctx, data->pix);
		fz_drop_display_list(ctx, data->list);

		// Free the data structured passed back and forth
		// between the main thread and rendering thread.

		free(data);
	}

	fprintf(stderr, "finally!\n");
	fflush(NULL);

	free(thread);

	// Finally the document is closed and the main thread's
	// context is freed.

	fz_drop_document(ctx, doc);
	fz_drop_context(ctx);

	return 0;
}