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
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  F ; 
 int /*<<< orphan*/  FirstPage ; 
 int /*<<< orphan*/  GoTo ; 
 int /*<<< orphan*/  GoToR ; 
 int /*<<< orphan*/  LastPage ; 
 int /*<<< orphan*/  Launch ; 
 int /*<<< orphan*/  N ; 
 int /*<<< orphan*/  Named ; 
 int /*<<< orphan*/  NextPage ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrevPage ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  URI ; 
 char* fz_asprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fz_is_external_link (int /*<<< orphan*/ *,char const*) ; 
 char* fz_malloc (int /*<<< orphan*/ *,scalar_t__) ; 
 char* fz_strdup (int /*<<< orphan*/ *,char const*) ; 
 int pdf_count_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* pdf_dict_get_text_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_getp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* pdf_parse_file_spec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* pdf_parse_link_dest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* pdf_to_text_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

char *
pdf_parse_link_action(fz_context *ctx, pdf_document *doc, pdf_obj *action, int pagenum)
{
	pdf_obj *obj, *dest, *file_spec;

	if (!action)
		return NULL;

	obj = pdf_dict_get(ctx, action, PDF_NAME(S));
	if (pdf_name_eq(ctx, PDF_NAME(GoTo), obj))
	{
		dest = pdf_dict_get(ctx, action, PDF_NAME(D));
		return pdf_parse_link_dest(ctx, doc, dest);
	}
	else if (pdf_name_eq(ctx, PDF_NAME(URI), obj))
	{
		/* URI entries are ASCII strings */
		const char *uri = pdf_dict_get_text_string(ctx, action, PDF_NAME(URI));
		if (!fz_is_external_link(ctx, uri))
		{
			pdf_obj *uri_base_obj = pdf_dict_getp(ctx, pdf_trailer(ctx, doc), "Root/URI/Base");
			const char *uri_base = uri_base_obj ? pdf_to_text_string(ctx, uri_base_obj) : "file://";
			char *new_uri = fz_malloc(ctx, strlen(uri_base) + strlen(uri) + 1);
			strcpy(new_uri, uri_base);
			strcat(new_uri, uri);
			return new_uri;
		}
		return fz_strdup(ctx, uri);
	}
	else if (pdf_name_eq(ctx, PDF_NAME(Launch), obj))
	{
		file_spec = pdf_dict_get(ctx, action, PDF_NAME(F));
		return pdf_parse_file_spec(ctx, doc, file_spec, NULL);
	}
	else if (pdf_name_eq(ctx, PDF_NAME(GoToR), obj))
	{
		dest = pdf_dict_get(ctx, action, PDF_NAME(D));
		file_spec = pdf_dict_get(ctx, action, PDF_NAME(F));
		return pdf_parse_file_spec(ctx, doc, file_spec, dest);
	}
	else if (pdf_name_eq(ctx, PDF_NAME(Named), obj))
	{
		dest = pdf_dict_get(ctx, action, PDF_NAME(N));

		if (pdf_name_eq(ctx, PDF_NAME(FirstPage), dest))
			pagenum = 0;
		else if (pdf_name_eq(ctx, PDF_NAME(LastPage), dest))
			pagenum = pdf_count_pages(ctx, doc) - 1;
		else if (pdf_name_eq(ctx, PDF_NAME(PrevPage), dest) && pagenum >= 0)
		{
			if (pagenum > 0)
				pagenum--;
		}
		else if (pdf_name_eq(ctx, PDF_NAME(NextPage), dest) && pagenum >= 0)
		{
			if (pagenum < pdf_count_pages(ctx, doc) - 1)
				pagenum++;
		}
		else
			return NULL;

		return fz_asprintf(ctx, "#%d", pagenum + 1);
	}

	return NULL;
}