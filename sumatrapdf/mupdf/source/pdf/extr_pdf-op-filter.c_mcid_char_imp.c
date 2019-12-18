#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pos; int /*<<< orphan*/ * utf8; } ;
struct TYPE_4__ {TYPE_2__ actualtext; TYPE_2__ alt; int /*<<< orphan*/ * mcid_obj; } ;
typedef  TYPE_1__ tag_record ;
typedef  int /*<<< orphan*/  pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  ActualText ; 
 int /*<<< orphan*/  Alt ; 
 int /*<<< orphan*/  E ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walk_string (int /*<<< orphan*/ *,int,int,TYPE_2__*) ; 

__attribute__((used)) static void
mcid_char_imp(fz_context *ctx, pdf_filter_processor *p, tag_record *tr, int uni, int remove)
{
	if (tr->mcid_obj == NULL)
		/* No object, or already deleted */
		return;

	if (remove)
	{
		/* Remove the expanded abbreviation, if there is one. */
		pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(E));
		/* Remove the structure title, if there is one. */
		pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(T));
	}

	/* Edit the Alt string */
	walk_string(ctx, uni, remove, &tr->alt);
	/* Edit the ActualText string */
	walk_string(ctx, uni, remove, &tr->actualtext);

	/* If we're removing a character, and either of the strings
	 * haven't matched up to what we were expecting, then just
	 * delete the whole string. */
	if (remove)
		remove = (tr->alt.pos == -1 || tr->actualtext.pos == -1);
	else if (tr->alt.pos >= 0 || tr->actualtext.pos >= 0)
	{
		/* The strings are making sense so far */
		remove = 0;
	}

	if (remove)
	{
		/* Anything else we have to err on the side of caution and
		 * delete everything that might leak info. */
		if (tr->actualtext.pos == -1)
			pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(ActualText));
		if (tr->alt.pos == -1)
			pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(Alt));
		pdf_drop_obj(ctx, tr->mcid_obj);
		tr->mcid_obj = NULL;
		fz_free(ctx, tr->alt.utf8);
		tr->alt.utf8 = NULL;
		fz_free(ctx, tr->actualtext.utf8);
		tr->actualtext.utf8 = NULL;
	}
}