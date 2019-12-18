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
 int /*<<< orphan*/  Kids ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_field (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strlen (char const*) ; 

pdf_obj *pdf_lookup_field(fz_context *ctx, pdf_obj *form, const char *name)
{
	const char *dot;
	const char *namep;
	pdf_obj *dict = NULL;
	int len;

	/* Process the fully qualified field name which has
	* the partial names delimited by '.'. Pretend there
	* was a preceding '.' to simplify the loop */
	dot = name - 1;

	while (dot && form)
	{
		namep = dot + 1;
		dot = strchr(namep, '.');
		len = dot ? dot - namep : (int)strlen(namep);
		dict = find_field(ctx, form, namep, len);
		if (dot)
			form = pdf_dict_get(ctx, dict, PDF_NAME(Kids));
	}

	return dict;
}