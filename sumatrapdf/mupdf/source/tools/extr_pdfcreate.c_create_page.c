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
typedef  int /*<<< orphan*/  fz_stream ;
struct TYPE_3__ {int member_2; int member_3; void* y1; void* x1; void* y0; void* x0; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ fz_rect ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  add_cjkfont_res (int /*<<< orphan*/ *,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  add_font_res (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  add_image_res (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  doc ; 
 int /*<<< orphan*/  fz_append_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  fz_append_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 void* fz_atoi (char*) ; 
 int /*<<< orphan*/  fz_drop_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_new_buffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * fz_open_file (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fz_read_line (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 char* fz_strsep (char**,char*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * pdf_add_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_insert_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_new_dict (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void create_page(char *input)
{
	fz_rect mediabox = { 0, 0, 595, 842 };
	int rotate = 0;

	char line[4096];
	char *s, *p;
	fz_stream *stm;

	fz_buffer *contents;
	pdf_obj *resources;
	pdf_obj *page;

	resources = pdf_new_dict(ctx, doc, 2);
	contents = fz_new_buffer(ctx, 1024);

	stm = fz_open_file(ctx, input);
	while (fz_read_line(ctx, stm, line, sizeof line))
	{
		if (line[0] == '%' && line[1] == '%')
		{
			p = line;
			s = fz_strsep(&p, " ");
			if (!strcmp(s, "%%MediaBox"))
			{
				mediabox.x0 = fz_atoi(fz_strsep(&p, " "));
				mediabox.y0 = fz_atoi(fz_strsep(&p, " "));
				mediabox.x1 = fz_atoi(fz_strsep(&p, " "));
				mediabox.y1 = fz_atoi(fz_strsep(&p, " "));
			}
			else if (!strcmp(s, "%%Rotate"))
			{
				rotate = fz_atoi(fz_strsep(&p, " "));
			}
			else if (!strcmp(s, "%%Font"))
			{
				char *name = fz_strsep(&p, " ");
				char *path = fz_strsep(&p, " ");
				char *enc = fz_strsep(&p, " ");
				if (!name || !path)
					fz_throw(ctx, FZ_ERROR_GENERIC, "Font directive missing arguments");
				add_font_res(resources, name, path, enc);
			}
			else if (!strcmp(s, "%%CJKFont"))
			{
				char *name = fz_strsep(&p, " ");
				char *lang = fz_strsep(&p, " ");
				char *wmode = fz_strsep(&p, " ");
				char *style = fz_strsep(&p, " ");
				if (!name || !lang)
					fz_throw(ctx, FZ_ERROR_GENERIC, "CJKFont directive missing arguments");
				add_cjkfont_res(resources, name, lang, wmode, style);
			}
			else if (!strcmp(s, "%%Image"))
			{
				char *name = fz_strsep(&p, " ");
				char *path = fz_strsep(&p, " ");
				if (!name || !path)
					fz_throw(ctx, FZ_ERROR_GENERIC, "Image directive missing arguments");
				add_image_res(resources, name, path);
			}
		}
		else
		{
			fz_append_string(ctx, contents, line);
			fz_append_byte(ctx, contents, '\n');
		}
	}
	fz_drop_stream(ctx, stm);

	page = pdf_add_page(ctx, doc, mediabox, rotate, resources, contents);
	pdf_insert_page(ctx, doc, -1, page);
	pdf_drop_obj(ctx, page);

	fz_drop_buffer(ctx, contents);
	pdf_drop_obj(ctx, resources);
}