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
 int /*<<< orphan*/  T ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,int) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* pdf_dict_get_text_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static pdf_obj *find_field(fz_context *ctx, pdf_obj *dict, const char *name, int len)
{
	int i, n = pdf_array_len(ctx, dict);
	for (i = 0; i < n; i++)
	{
		pdf_obj *field = pdf_array_get(ctx, dict, i);
		const char *part = pdf_dict_get_text_string(ctx, field, PDF_NAME(T));
		if (strlen(part) == (size_t)len && !memcmp(part, name, len))
			return field;
	}
	return NULL;
}