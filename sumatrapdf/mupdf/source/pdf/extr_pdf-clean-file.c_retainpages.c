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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_3__ {int /*<<< orphan*/ * doc; } ;
typedef  TYPE_1__ globals ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  Annots ; 
 int /*<<< orphan*/  Count ; 
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  Dests ; 
 int /*<<< orphan*/  Kids ; 
 int /*<<< orphan*/  Link ; 
 int /*<<< orphan*/  Names ; 
 int /*<<< orphan*/  OCProperties ; 
 int /*<<< orphan*/  Outlines ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pages ; 
 int /*<<< orphan*/  Root ; 
 int /*<<< orphan*/  Subtype ; 
 int /*<<< orphan*/  Type ; 
 int /*<<< orphan*/  dest_is_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ dest_is_valid_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 int* fz_calloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,int*) ; 
 char* fz_parse_page_range (int /*<<< orphan*/ *,char const*,int*,int*,int) ; 
 int /*<<< orphan*/  pdf_array_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_array_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_array_push_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_count_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_dict_get_val (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_dict_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_load_name_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_lookup_page_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_new_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_new_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_new_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_new_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_to_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_update_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  retainpage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strip_outlines (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void retainpages(fz_context *ctx, globals *glo, int argc, char **argv)
{
	pdf_obj *oldroot, *root, *pages, *kids, *countobj, *olddests;
	pdf_document *doc = glo->doc;
	int argidx = 0;
	pdf_obj *names_list = NULL;
	pdf_obj *outlines;
	pdf_obj *ocproperties;
	int pagecount;
	int i;
	int *page_object_nums;

	/* Keep only pages/type and (reduced) dest entries to avoid
	 * references to unretained pages */
	oldroot = pdf_dict_get(ctx, pdf_trailer(ctx, doc), PDF_NAME(Root));
	pages = pdf_dict_get(ctx, oldroot, PDF_NAME(Pages));
	olddests = pdf_load_name_tree(ctx, doc, PDF_NAME(Dests));
	outlines = pdf_dict_get(ctx, oldroot, PDF_NAME(Outlines));
	ocproperties = pdf_dict_get(ctx, oldroot, PDF_NAME(OCProperties));

	root = pdf_new_dict(ctx, doc, 3);
	pdf_dict_put(ctx, root, PDF_NAME(Type), pdf_dict_get(ctx, oldroot, PDF_NAME(Type)));
	pdf_dict_put(ctx, root, PDF_NAME(Pages), pdf_dict_get(ctx, oldroot, PDF_NAME(Pages)));
	if (outlines)
		pdf_dict_put(ctx, root, PDF_NAME(Outlines), outlines);
	if (ocproperties)
		pdf_dict_put(ctx, root, PDF_NAME(OCProperties), ocproperties);

	pdf_update_object(ctx, doc, pdf_to_num(ctx, oldroot), root);

	/* Create a new kids array with only the pages we want to keep */
	kids = pdf_new_array(ctx, doc, 1);

	/* Retain pages specified */
	while (argc - argidx)
	{
		int page, spage, epage;
		const char *pagelist = argv[argidx];

		pagecount = pdf_count_pages(ctx, doc);

		while ((pagelist = fz_parse_page_range(ctx, pagelist, &spage, &epage, pagecount)))
		{
			if (spage < epage)
				for (page = spage; page <= epage; ++page)
					retainpage(ctx, doc, pages, kids, page);
			else
				for (page = spage; page >= epage; --page)
					retainpage(ctx, doc, pages, kids, page);
		}

		argidx++;
	}

	/* Update page count and kids array */
	countobj = pdf_new_int(ctx, pdf_array_len(ctx, kids));
	pdf_dict_put_drop(ctx, pages, PDF_NAME(Count), countobj);
	pdf_dict_put_drop(ctx, pages, PDF_NAME(Kids), kids);

	pagecount = pdf_count_pages(ctx, doc);
	page_object_nums = fz_calloc(ctx, pagecount, sizeof(*page_object_nums));
	for (i = 0; i < pagecount; i++)
	{
		pdf_obj *pageref = pdf_lookup_page_obj(ctx, doc, i);
		page_object_nums[i] = pdf_to_num(ctx, pageref);
	}

	/* If we had an old Dests tree (now reformed as an olddests
	 * dictionary), keep any entries in there that point to
	 * valid pages. This may mean we keep more than we need, but
	 * it's safe at least. */
	if (olddests)
	{
		pdf_obj *names = pdf_new_dict(ctx, doc, 1);
		pdf_obj *dests = pdf_new_dict(ctx, doc, 1);
		int len = pdf_dict_len(ctx, olddests);

		names_list = pdf_new_array(ctx, doc, 32);

		for (i = 0; i < len; i++)
		{
			pdf_obj *key = pdf_dict_get_key(ctx, olddests, i);
			pdf_obj *val = pdf_dict_get_val(ctx, olddests, i);
			pdf_obj *dest = pdf_dict_get(ctx, val, PDF_NAME(D));

			dest = pdf_array_get(ctx, dest ? dest : val, 0);
			if (dest_is_valid_page(ctx, dest, page_object_nums, pagecount))
			{
				pdf_obj *key_str = pdf_new_string(ctx, pdf_to_name(ctx, key), strlen(pdf_to_name(ctx, key)));
				pdf_array_push_drop(ctx, names_list, key_str);
				pdf_array_push(ctx, names_list, val);
			}
		}

		pdf_dict_put(ctx, dests, PDF_NAME(Names), names_list);
		pdf_dict_put(ctx, names, PDF_NAME(Dests), dests);
		pdf_dict_put(ctx, root, PDF_NAME(Names), names);

		pdf_drop_obj(ctx, names);
		pdf_drop_obj(ctx, dests);
		pdf_drop_obj(ctx, olddests);
	}

	/* Edit each pages /Annot list to remove any links that point to nowhere. */
	for (i = 0; i < pagecount; i++)
	{
		pdf_obj *pageref = pdf_lookup_page_obj(ctx, doc, i);

		pdf_obj *annots = pdf_dict_get(ctx, pageref, PDF_NAME(Annots));

		int len = pdf_array_len(ctx, annots);
		int j;

		for (j = 0; j < len; j++)
		{
			pdf_obj *o = pdf_array_get(ctx, annots, j);

			if (!pdf_name_eq(ctx, pdf_dict_get(ctx, o, PDF_NAME(Subtype)), PDF_NAME(Link)))
				continue;

			if (!dest_is_valid(ctx, o, pagecount, page_object_nums, names_list))
			{
				/* Remove this annotation */
				pdf_array_delete(ctx, annots, j);
				len--;
				j--;
			}
		}
	}

	if (strip_outlines(ctx, doc, outlines, pagecount, page_object_nums, names_list) == 0)
	{
		pdf_dict_del(ctx, root, PDF_NAME(Outlines));
	}

	fz_free(ctx, page_object_nums);
	pdf_drop_obj(ctx, names_list);
	pdf_drop_obj(ctx, root);
}