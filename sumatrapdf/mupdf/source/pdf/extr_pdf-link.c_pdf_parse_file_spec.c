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
 int /*<<< orphan*/  DOS ; 
 int /*<<< orphan*/  F ; 
 int /*<<< orphan*/  FS ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UF ; 
 int /*<<< orphan*/  URL ; 
 int /*<<< orphan*/  Unix ; 
 char* fz_asprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pdf_array_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_geta (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_to_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_to_str_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* pdf_to_text_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

char *
pdf_parse_file_spec(fz_context *ctx, pdf_document *doc, pdf_obj *file_spec, pdf_obj *dest)
{
	pdf_obj *filename = NULL;
	const char *path;
	char *uri;
	char frag[256];

	if (pdf_is_string(ctx, file_spec))
		filename = file_spec;

	if (pdf_is_dict(ctx, file_spec)) {
#ifdef _WIN32
		filename = pdf_dict_get(ctx, file_spec, PDF_NAME(DOS));
#else
		filename = pdf_dict_get(ctx, file_spec, PDF_NAME(Unix));
#endif
		if (!filename)
			filename = pdf_dict_geta(ctx, file_spec, PDF_NAME(UF), PDF_NAME(F));
	}

	if (!pdf_is_string(ctx, filename))
	{
		fz_warn(ctx, "cannot parse file specification");
		return NULL;
	}

	if (pdf_is_array(ctx, dest))
		fz_snprintf(frag, sizeof frag, "#page=%d", pdf_array_get_int(ctx, dest, 0) + 1);
	else if (pdf_is_name(ctx, dest))
		fz_snprintf(frag, sizeof frag, "#%s", pdf_to_name(ctx, dest));
	else if (pdf_is_string(ctx, dest))
		fz_snprintf(frag, sizeof frag, "#%s", pdf_to_str_buf(ctx, dest));
	else
		frag[0] = 0;

	path = pdf_to_text_string(ctx, filename);
	uri = NULL;
#ifdef _WIN32
	if (!pdf_name_eq(ctx, pdf_dict_get(ctx, file_spec, PDF_NAME(FS)), PDF_NAME(URL)))
	{
		/* Fix up the drive letter (change "/C/Documents/Foo" to "C:/Documents/Foo") */
		if (path[0] == '/' && (('A' <= path[1] && path[1] <= 'Z') || ('a' <= path[1] && path[1] <= 'z')) && path[2] == '/')
			uri = fz_asprintf(ctx, "file://%c:%s%s", path[1], path+2, frag);
	}
#endif
	if (!uri)
		uri = fz_asprintf(ctx, "file://%s%s", path, frag);

	return uri;
}