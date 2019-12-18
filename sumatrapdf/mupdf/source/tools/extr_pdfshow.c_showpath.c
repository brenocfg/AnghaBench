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

/* Variables and functions */
 int /*<<< orphan*/  SEP ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  fz_strlcpy (char*,char*,int) ; 
 char* fz_strsep (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isnumber (char*) ; 
 int /*<<< orphan*/  out ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get_val (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_dict_gets (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int pdf_dict_len (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_dict (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_indirect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_print_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  showobject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  tight ; 

__attribute__((used)) static void showpath(char *path, pdf_obj *obj)
{
	if (path && path[0])
	{
		char *part = fz_strsep(&path, SEP);
		if (part && part[0])
		{
			if (!strcmp(part, "*"))
			{
				int i, n;
				char buf[1000];
				if (pdf_is_array(ctx, obj))
				{
					n = pdf_array_len(ctx, obj);
					for (i = 0; i < n; ++i)
					{
						if (path)
						{
							fz_strlcpy(buf, path, sizeof buf);
							showpath(buf, pdf_array_get(ctx, obj, i));
						}
						else
							showpath(NULL, pdf_array_get(ctx, obj, i));
					}
				}
				else if (pdf_is_dict(ctx, obj))
				{
					n = pdf_dict_len(ctx, obj);
					for (i = 0; i < n; ++i)
					{
						if (path)
						{
							fz_strlcpy(buf, path, sizeof buf);
							showpath(buf, pdf_dict_get_val(ctx, obj, i));
						}
						else
							showpath(NULL, pdf_dict_get_val(ctx, obj, i));
					}
				}
				else
				{
					fz_write_string(ctx, out, "null\n");
				}
			}
			else if (isnumber(part) && pdf_is_array(ctx, obj))
				showpath(path, pdf_array_get(ctx, obj, atoi(part)-1));
			else
				showpath(path, pdf_dict_gets(ctx, obj, part));
		}
		else
			fz_write_string(ctx, out, "null\n");
	}
	else
	{
		if (pdf_is_indirect(ctx, obj))
			showobject(obj);
		else
		{
			pdf_print_obj(ctx, out, obj, tight, 0);
			fz_write_string(ctx, out, "\n");
		}
	}
}