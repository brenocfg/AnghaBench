#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* use_list; int start; int* renumber_map; int* rev_renumber_map; int /*<<< orphan*/  page_object_lists; } ;
typedef  TYPE_1__ pdf_write_state ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int USE_PARAMS ; 
 int /*<<< orphan*/  add_linearization_objs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int* fz_calloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_sort (int*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  order_ge ; 
 int /*<<< orphan*/  page_objects_list_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_objects_list_renumber (TYPE_1__*) ; 
 int /*<<< orphan*/  page_objects_list_sort_and_dedupe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_localise_page_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_xref_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  renumberobjs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
linearize(fz_context *ctx, pdf_document *doc, pdf_write_state *opts)
{
	int i;
	int n = pdf_xref_len(ctx, doc) + 2;
	int *reorder;
	int *rev_renumber_map;

	opts->page_object_lists = page_objects_list_create(ctx);

	/* Ensure that every page has local references of its resources */
	/* FIXME: We could 'thin' the resources according to what is actually
	 * required for each page, but this would require us to run the page
	 * content streams. */
	pdf_localise_page_resources(ctx, doc);

	/* Walk the objects for each page, marking which ones are used, where */
	memset(opts->use_list, 0, n * sizeof(int));
	mark_trailer(ctx, doc, opts, pdf_trailer(ctx, doc));

	/* Add new objects required for linearization */
	add_linearization_objs(ctx, doc, opts);

#ifdef DEBUG_WRITING
	fprintf(stderr, "Usage calculated:\n");
	for (i=0; i < pdf_xref_len(ctx, doc); i++)
	{
		fprintf(stderr, "%d: use=%d\n", i, opts->use_list[i]);
	}
#endif

	/* Allocate/init the structures used for renumbering the objects */
	reorder = fz_calloc(ctx, n, sizeof(int));
	rev_renumber_map = fz_calloc(ctx, n, sizeof(int));
	for (i = 0; i < n; i++)
	{
		reorder[i] = i;
	}

	/* Heap sort the reordering */
	heap_sort(reorder+1, n-1, opts->use_list, &order_ge);

#ifdef DEBUG_WRITING
	fprintf(stderr, "Reordered:\n");
	for (i=1; i < pdf_xref_len(ctx, doc); i++)
	{
		fprintf(stderr, "%d: use=%d\n", i, opts->use_list[reorder[i]]);
	}
#endif

	/* Find the split point */
	for (i = 1; (opts->use_list[reorder[i]] & USE_PARAMS) == 0; i++) {}
	opts->start = i;

	/* Roll the reordering into the renumber_map */
	for (i = 0; i < n; i++)
	{
		opts->renumber_map[reorder[i]] = i;
		rev_renumber_map[i] = opts->rev_renumber_map[reorder[i]];
	}
	fz_free(ctx, opts->rev_renumber_map);
	opts->rev_renumber_map = rev_renumber_map;
	fz_free(ctx, reorder);

	/* Apply the renumber_map */
	page_objects_list_renumber(opts);
	renumberobjs(ctx, doc, opts);

	page_objects_list_sort_and_dedupe(ctx, opts->page_object_lists);
}