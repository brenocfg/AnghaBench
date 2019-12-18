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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Parent ; 
 int /*<<< orphan*/  T ; 
 char* fz_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* pdf_dict_get_text_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *get_field_name(fz_context *ctx, pdf_obj *field, int spare)
{
	char *res = NULL;
	pdf_obj *parent = pdf_dict_get(ctx, field, PDF_NAME(Parent));
	const char *lname = pdf_dict_get_text_string(ctx, field, PDF_NAME(T));
	int llen = (int)strlen(lname);

	/*
	 * If we found a name at this point in the field hierarchy
	 * then we'll need extra space for it and a dot
	 */
	if (llen)
		spare += llen+1;

	if (parent)
	{
		res = get_field_name(ctx, parent, spare);
	}
	else
	{
		res = fz_malloc(ctx, spare+1);
		res[0] = 0;
	}

	if (llen)
	{
		if (res[0])
			strcat(res, ".");

		strcat(res, lname);
	}

	return res;
}