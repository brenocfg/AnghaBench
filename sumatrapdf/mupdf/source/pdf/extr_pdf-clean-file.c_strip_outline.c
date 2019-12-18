#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  Dest ; 
 int /*<<< orphan*/  Next ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Prev ; 
 int /*<<< orphan*/  dest_is_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strip_outlines (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int strip_outline(fz_context *ctx, pdf_document *doc, pdf_obj *outlines, int page_count, int *page_object_nums, pdf_obj *names_list, pdf_obj **pfirst, pdf_obj **plast)
{
	pdf_obj *prev = NULL;
	pdf_obj *first = NULL;
	pdf_obj *current;
	int count = 0;

	for (current = outlines; current != NULL; )
	{
		int nc;

		/* Strip any children to start with. This takes care of
		 * First/Last/Count for us. */
		nc = strip_outlines(ctx, doc, current, page_count, page_object_nums, names_list);

		if (!dest_is_valid(ctx, current, page_count, page_object_nums, names_list))
		{
			if (nc == 0)
			{
				/* Outline with invalid dest and no children. Drop it by
				 * pulling the next one in here. */
				pdf_obj *next = pdf_dict_get(ctx, current, PDF_NAME(Next));
				if (next == NULL)
				{
					/* There is no next one to pull in */
					if (prev != NULL)
						pdf_dict_del(ctx, prev, PDF_NAME(Next));
				}
				else if (prev != NULL)
				{
					pdf_dict_put(ctx, prev, PDF_NAME(Next), next);
					pdf_dict_put(ctx, next, PDF_NAME(Prev), prev);
				}
				else
				{
					pdf_dict_del(ctx, next, PDF_NAME(Prev));
				}
				current = next;
			}
			else
			{
				/* Outline with invalid dest, but children. Just drop the dest. */
				pdf_dict_del(ctx, current, PDF_NAME(Dest));
				pdf_dict_del(ctx, current, PDF_NAME(A));
				current = pdf_dict_get(ctx, current, PDF_NAME(Next));
			}
		}
		else
		{
			/* Keep this one */
			if (first == NULL)
				first = current;
			prev = current;
			current = pdf_dict_get(ctx, current, PDF_NAME(Next));
			count++;
		}
	}

	*pfirst = first;
	*plast = prev;

	return count;
}